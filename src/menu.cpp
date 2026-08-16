#include "menu.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

Menu::Menu() : nextItemId(1) {}

bool Menu::addItem(const MenuItem& item) {
    if (item.getId() <= 0 || item.getPrice() <= 0.0 || item.getName().empty() ||
        item.getCategory().empty() || getItem(item.getId()) != nullptr) {
        return false;
    }

    items.push_back(item);
    nextItemId = std::max(nextItemId, item.getId() + 1);
    return true;
}

int Menu::addItem(const std::string& name, double price, const std::string& category) {
    if (name.empty() || category.empty() || price <= 0.0) {
        return -1;
    }

    const int assignedId = nextItemId++;
    items.emplace_back(assignedId, name, price, category);
    return assignedId;
}

bool Menu::removeItem(int id) {
    const auto it = std::find_if(items.begin(), items.end(),
                                 [id](const MenuItem& item) { return item.getId() == id; });
    if (it == items.end()) {
        return false;
    }

    items.erase(it);
    return true;
}

MenuItem* Menu::getItem(int id) {
    const auto it = std::find_if(items.begin(), items.end(),
                                 [id](const MenuItem& item) { return item.getId() == id; });
    return it == items.end() ? nullptr : &(*it);
}

const MenuItem* Menu::getItem(int id) const {
    const auto it = std::find_if(items.begin(), items.end(),
                                 [id](const MenuItem& item) { return item.getId() == id; });
    return it == items.end() ? nullptr : &(*it);
}

void Menu::displayMenu() const {
    std::cout << "\n============================================================\n";
    std::cout << "RFOS | VIEW MENU | Session Active\n";
    std::cout << "============================================================\n";

    if (items.empty()) {
        std::cout << "No menu items are currently available.\n";
        return;
    }

    const std::vector<std::string> preferredOrder = {"STARTER", "MAIN", "BEVERAGE"};
    std::set<std::string> printed;

    auto printCategory = [&](const std::string& category) {
        bool hasItems = false;
        for (const auto& item : items) {
            if (item.getCategory() == category) {
                if (!hasItems) {
                    std::cout << "\n" << category << "S\n";
                    std::cout << "------------------------------------------------------------\n";
                    hasItems = true;
                }
                std::cout << std::left << std::setw(5) << item.getId()
                          << std::setw(36) << item.getName()
                          << "$" << std::right << std::setw(7) << std::fixed
                          << std::setprecision(2) << item.getPrice() << '\n';
            }
        }
        if (hasItems) {
            printed.insert(category);
        }
    };

    for (const auto& category : preferredOrder) {
        printCategory(category);
    }

    for (const auto& item : items) {
        if (printed.find(item.getCategory()) == printed.end()) {
            printCategory(item.getCategory());
        }
    }

    std::cout << "============================================================\n";
}

bool Menu::isEmpty() const {
    return items.empty();
}

const std::vector<MenuItem>& Menu::getItems() const {
    return items;
}
