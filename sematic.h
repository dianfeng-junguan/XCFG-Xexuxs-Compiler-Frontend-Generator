#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using sematic_symbol_id_t = std::size_t;
using sematic_init_set_t = std::unordered_set<sematic_symbol_id_t>;

enum class sematic_access_mode_t {
    read,
    write,
    address
};

struct sematic_conditional_init_t {
    sematic_init_set_t incoming;
    sematic_init_set_t fallthrough;
    std::vector<sematic_init_set_t> exits;
};

class sematic_context_t{
public:
    std::size_t stage = 0;

    // Resolution actions should map identifier or AST addresses to stable IDs.
    std::unordered_map<const void*, sematic_symbol_id_t> resolved_symbols;
    sematic_symbol_id_t next_symbol_id = 0;

    sematic_init_set_t initialized;
    std::vector<sematic_access_mode_t> access_modes{sematic_access_mode_t::read};
    std::vector<sematic_conditional_init_t> conditional_init_stack;
    std::vector<sematic_init_set_t> optional_init_stack;
    std::vector<sematic_init_set_t> loop_init_stack;
    std::vector<sematic_init_set_t> function_init_stack;
    std::vector<std::string> diagnostics;

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

    void begin_pass(std::size_t pass) {
        stage = pass;
        access_modes.assign(1, sematic_access_mode_t::read);
        conditional_init_stack.clear();
        optional_init_stack.clear();
        loop_init_stack.clear();
        function_init_stack.clear();
    }

    sematic_access_mode_t access_mode() const {
        return access_modes.back();
    }

    void push_access_mode(sematic_access_mode_t mode) {
        access_modes.push_back(mode);
    }

    bool pop_access_mode() {
        if (access_modes.size() <= 1) {
            return false;
        }
        access_modes.pop_back();
        return true;
    }

    void begin_conditional_init() {
        conditional_init_stack.push_back({initialized, initialized, {}});
    }

    bool begin_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        initialized = conditional_init_stack.back().fallthrough;
        return true;
    }

    bool save_init_condition_fallthrough() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        conditional_init_stack.back().fallthrough = initialized;
        return true;
    }

    bool end_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        auto &frame = conditional_init_stack.back();
        frame.exits.push_back(initialized);
        initialized = frame.fallthrough;
        return true;
    }

    bool record_implicit_init_branch() {
        if (conditional_init_stack.empty()) {
            return false;
        }
        auto &frame = conditional_init_stack.back();
        frame.exits.push_back(frame.fallthrough);
        return true;
    }

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

    void begin_optional_init() {
        optional_init_stack.push_back(initialized);
    }

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

    void begin_loop_init() {
        loop_init_stack.push_back(initialized);
    }

    bool end_loop_init() {
        if (loop_init_stack.empty()) {
            return false;
        }
        initialized = std::move(loop_init_stack.back());
        loop_init_stack.pop_back();
        return true;
    }

    void begin_definite_function() {
        function_init_stack.push_back(initialized);
    }

    bool end_definite_function() {
        if (function_init_stack.empty()) {
            return false;
        }
        initialized = std::move(function_init_stack.back());
        function_init_stack.pop_back();
        return true;
    }
};
