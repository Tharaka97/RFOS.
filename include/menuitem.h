#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>

class MenuItem {
private:
    int itemId;
    std::string name;
    double price;
    std::string category;

public:
    MenuItem();
    MenuItem(int id, const std::string& name, double price, const std::string& category);

    int getId() const;
    const std::string& getName() const;
    double getPrice() const;
    const std::string& getCategory() const;
    std::string getDetails() const;
};

#endif
