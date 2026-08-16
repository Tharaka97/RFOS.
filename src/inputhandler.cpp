#include "inputhandler.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

std::string InputHandler::trim(const std::string& value) {
    auto begin = std::find_if_not(value.begin(), value.end(),
                                  [](unsigned char c) { return std::isspace(c); });
    auto end = std::find_if_not(value.rbegin(), value.rend(),
                                [](unsigned char c) { return std::isspace(c); }).base();

    if (begin >= end) {
        return "";
    }
    return std::string(begin, end);
}

int InputHandler::getIntInRange(int min, int max, const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("Input stream failure.");
        }

        input = trim(input);

        try {
            size_t pos = 0;
            const int value = std::stoi(input, &pos);
            if (pos != input.size()) {
                throw std::invalid_argument("trailing characters");
            }
            if (value < min || value > max) {
                std::cout << ">> ERROR: Value must be between " << min
                          << " and " << max << ". Please try again.\n";
                continue;
            }
            return value;
        } catch (const std::exception&) {
            std::cout << ">> ERROR: Please enter a valid whole number.\n";
        }
    }
}

double InputHandler::getPositiveDouble(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("Input stream failure.");
        }

        input = trim(input);

        try {
            size_t pos = 0;
            const double value = std::stod(input, &pos);
            if (pos != input.size()) {
                throw std::invalid_argument("trailing characters");
            }
            if (value <= 0.0) {
                std::cout << ">> ERROR: Price must be greater than $0.00.\n";
                continue;
            }
            return value;
        } catch (const std::exception&) {
            std::cout << ">> ERROR: Please enter a valid numeric price.\n";
        }
    }
}

bool InputHandler::getConfirmation(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("Input stream failure.");
        }

        input = trim(input);
        if (input.size() == 1) {
            const char value = static_cast<char>(std::tolower(
                static_cast<unsigned char>(input.front())));
            if (value == 'y') return true;
            if (value == 'n') return false;
        }

        std::cout << ">> ERROR: Please enter Y or N.\n";
    }
}

std::string InputHandler::getString(const std::string& prompt) const {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("Input stream failure.");
        }

        input = trim(input);
        if (!input.empty()) {
            return input;
        }

        std::cout << ">> ERROR: Value cannot be blank. Please try again.\n";
    }
}
