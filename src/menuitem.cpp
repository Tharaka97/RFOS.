#include "menuitem.h"

#include <iomanip>
#include <sstream>

MenuItem::MenuItem() : itemId(0), price(0.0) {}

MenuItem::MenuItem(int id, const std::string& itemName, double itemPrice,
                   const std::string& itemCategory)
    : itemId(id), name(itemName), price(itemPrice), category(itemCategory) {}

int MenuItem::getId() const {
    return itemId;
}

const std::string& MenuItem::getName() const {
    return name;
}

double MenuItem::getPrice() const {
    return price;
}

const std::string& MenuItem::getCategory() const {
    return category;
}

std::string MenuItem::getDetails() const {
    std::ostringstream out;
    out << itemId << ". " << name << " - $" << std::fixed << std::setprecision(2) << price;
    return out.str();
}
