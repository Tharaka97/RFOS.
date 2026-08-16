#ifndef MENU_H
#define MENU_H

#include "menuitem.h"

#include <vector>

class Menu {
private:
    std::vector<MenuItem> items;
    int nextItemId;

public:
    Menu();

    bool addItem(const MenuItem& item);
    int addItem(const std::string& name, double price, const std::string& category);
    bool removeItem(int id);
    MenuItem* getItem(int id);
    const MenuItem* getItem(int id) const;
    void displayMenu() const;
    bool isEmpty() const;
    const std::vector<MenuItem>& getItems() const;
};

#endif
