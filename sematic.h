#pragma once
#include <cstddef>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "parser.h"

using sematic_symbol_id_t = std::size_t;
// The set of symbols that are definitely initialized on the current path.
using sematic_init_set_t = std::unordered_set<sematic_symbol_id_t>;

// Describes how the current expression uses an lvalue.
enum class sematic_access_mode_t {
    // The stored value is read, so the object must already be initialized.
    read,
    // The object is only used as an assignment destination.
    write,
    // Only the object's address is needed; its stored value is not read.
    address
};

// State collected while analyzing one if / else-if / else chain.
struct sematic_conditional_init_t {
    // Initialization state before the first condition is evaluated.
    sematic_init_set_t incoming;
    // State on the path where every condition seen so far evaluated to false.
    sematic_init_set_t fallthrough;
    // Initialization state at the end of every completed branch.
    std::vector<sematic_init_set_t> exits;
};
enum class symbol_type_t {
    variable,
    function,
    struct_type
};
class symbol_t{
public:
    std::string name;
    sematic_symbol_id_t id;
    symbol_type_t symbol_type;
};
class symbol_table_t{
public:
    symbol_table_t* parent=nullptr;
    ast_node_t *owner;
    std::vector<symbol_t> symbols;
    symbol_table_t(ast_node_t *owner,symbol_table_t *parent):owner(owner),parent(parent){}
    // Add a new symbol to the table.
    // Returns the ID of the new symbol, or an existing symbol with the same name.
    sematic_symbol_id_t add_symbol(const std::string& name, symbol_type_t type) {
        for (const auto& sym : symbols) {
            if (sym.name == name && sym.symbol_type == type) {
                return sym.id;
            }
        }
        sematic_symbol_id_t new_id = symbols.size();
        symbols.push_back({name, new_id, type});
        return new_id;
    }
    // Look up a symbol by name.
    // Returns the ID of the symbol, or an invalid ID if not found.
    sematic_symbol_id_t lookup_symbol(const std::string& name) const {
        for (const auto& sym : symbols) {
            if (sym.name == name) {
                return sym.id;
            }
        }
        return static_cast<sematic_symbol_id_t>(-1); // Invalid ID
    }
    // Get the symbol by ID.
    const symbol_t& get_symbol(sematic_symbol_id_t id) const {
        if (id < symbols.size()) {
            return symbols[id];
        }
        throw std::out_of_range("Invalid symbol ID");
    }
};
class sematic_context_t{
public:
    // symbol tables.
    std::vector<symbol_table_t> symbol_tables;
    // Index of the semantic pass currently executed by visit().
    std::size_t stage = 0;

    // Resolution actions should map identifier or AST addresses to stable IDs.
    std::unordered_map<const void*, sematic_symbol_id_t> resolved_symbols;
    // ID assigned to the next symbol created by a resolution action.
    sematic_symbol_id_t next_symbol_id = 0;

    // Symbols initialized on every path reaching the current AST node.
    sematic_init_set_t initialized;
    // Nested read/write/address modes. The top entry is the active mode.
    std::vector<sematic_access_mode_t> access_modes{sematic_access_mode_t::read};
    // Nested conditional expressions currently being analyzed.
    std::vector<sematic_conditional_init_t> conditional_init_stack;
    // Saved states for expressions that may not execute, such as && and || RHS.
    std::vector<sematic_init_set_t> optional_init_stack;
    // States saved before entering loops that may execute zero times.
    std::vector<sematic_init_set_t> loop_init_stack;
    // Outer states saved while independently analyzing function bodies.
    std::vector<sematic_init_set_t> function_init_stack;
    // Human-readable errors and warnings produced by semantic actions.
    std::vector<std::string> diagnostics;

    // Start a completely new semantic analysis.
    // This removes persistent symbol bindings, initialization facts and diagnostics.
    void reset_analysis() {
        stage = 0;
        resolved_symbols.clear();
        next_symbol_id = 0;
        initialized.clear();
        diagnostics.clear();
        access_modes.assign(1, sematic_access_mode_t::read);
        conditional_init_stack.clear();
        optional_init_stack.clear();
        loop_init_stack.clear();
        function_init_stack.clear();
    }

    // Prepare temporary traversal state for one pass.
    // Persistent results such as symbol bindings and diagnostics are preserved so
    // later passes can use information produced by earlier passes.
    void begin_pass(std::size_t pass) {
        stage = pass;
        access_modes.assign(1, sematic_access_mode_t::read);
        conditional_init_stack.clear();
        optional_init_stack.clear();
        loop_init_stack.clear();
        function_init_stack.clear();
    }

    // Return the active way in which an expression is being accessed.
    sematic_access_mode_t access_mode() const {
        return access_modes.back();
    }

    // Temporarily override the access mode for a nested expression.
    // Every call must be paired with pop_access_mode().
    void push_access_mode(sematic_access_mode_t mode) {
        access_modes.push_back(mode);
    }

    // Restore the previous access mode.
    // Returns false when no matching push exists; the base read mode is retained.
    bool pop_access_mode() {
        if (access_modes.size() <= 1) {
            return false;
        }
        access_modes.pop_back();
        return true;
    }

    // Begin collecting definite-initialization results for an if chain.
    // Both incoming and fallthrough initially contain the current state.
    void begin_conditional_init() {
        conditional_init_stack.push_back({initialized, initialized, {}});
    }

    // Begin one then/else-if/else branch from the current false-condition path.
    // Returns false if no conditional frame is active.
    bool begin_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        initialized = conditional_init_stack.back().fallthrough;
        return true;
    }

    // Save the state after evaluating an else-if condition. This becomes the
    // starting state of its body and of the following branch when it is false.
    // Returns false if no conditional frame is active.
    bool save_init_condition_fallthrough() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        conditional_init_stack.back().fallthrough = initialized;
        return true;
    }

    // Record the current branch's exit state, then restore the state from which
    // the next branch must start. Returns false outside a conditional frame.
    bool end_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        auto &frame = conditional_init_stack.back();
        frame.exits.push_back(initialized);
        initialized = frame.fallthrough;
        return true;
    }

    // Record the path where no branch is taken, used by an if chain without a
    // final else. Returns false outside a conditional frame.
    bool record_implicit_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        auto &frame = conditional_init_stack.back();
        frame.exits.push_back(frame.fallthrough);
        return true;
    }

    // Finish an if chain and keep only symbols initialized in every possible
    // exit. This set intersection implements definite, not possible,
    // initialization. Returns false if no conditional frame is active.
    bool end_conditional_init() {
        if (conditional_init_stack.empty()) {
            return false;
        }

        auto frame = std::move(conditional_init_stack.back());
        conditional_init_stack.pop_back();
        if (frame.exits.empty()) {
            initialized = std::move(frame.fallthrough);
            return true;
        }

        sematic_init_set_t merged = frame.exits.front();
        for (std::size_t i = 1; i < frame.exits.size(); ++i) {
            for (auto symbol = merged.begin(); symbol != merged.end();) {
                if (frame.exits[i].find(*symbol) == frame.exits[i].end()) {
                    symbol = merged.erase(symbol);
                } else {
                    ++symbol;
                }
            }
        }
        initialized = std::move(merged);
        return true;
    }

    // Save the state before entering code that may be skipped, such as the
    // right-hand side of a short-circuit && or || expression.
    void begin_optional_init() {
        optional_init_stack.push_back(initialized);
    }

    // Merge a possibly skipped expression by keeping only facts that were true
    // both before and after it. Returns false if there is no saved state.
    bool end_optional_init() {
        if (optional_init_stack.empty()) {
            return false;
        }
        auto mandatory = std::move(optional_init_stack.back());
        optional_init_stack.pop_back();
        for (auto symbol = initialized.begin(); symbol != initialized.end();) {
            if (mandatory.find(*symbol) == mandatory.end()) {
                symbol = initialized.erase(symbol);
            } else {
                ++symbol;
            }
        }
        return true;
    }

    // Save the state before a loop body. A while body may execute zero times.
    void begin_loop_init() {
        loop_init_stack.push_back(initialized);
    }

    // Restore the state from before the loop so assignments performed only in
    // the body are not considered definite after the loop.
    // Returns false if there is no matching begin_loop_init().
    bool end_loop_init() {
        if (loop_init_stack.empty()) {
            return false;
        }
        initialized = std::move(loop_init_stack.back());
        loop_init_stack.pop_back();
        return true;
    }

    // Save the outer initialization state before analyzing a function body.
    // Parameters should be marked initialized after this call.
    void begin_definite_function() {
        function_init_stack.push_back(initialized);
    }

    // Finish a function body and restore the outer state, preventing local
    // initialization facts from leaking into the next function.
    // Returns false if there is no matching begin_definite_function().
    bool end_definite_function() {
        if (function_init_stack.empty()) {
            return false;
        }
        initialized = std::move(function_init_stack.back());
        function_init_stack.pop_back();
        return true;
    }

    void push_symbol_table(ast_node_t *owner) {
        symbol_tables.emplace_back(owner, symbol_tables.empty() ? nullptr : &symbol_tables.back());
    }
};
