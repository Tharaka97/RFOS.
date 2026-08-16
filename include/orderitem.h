#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "menuitem.h"

class OrderItem {
private:
    MenuItem menuItem;
    int quantity;

public:
    OrderItem(const MenuItem& item, int quantity);

    const MenuItem& getMenuItem() const;
    int getQuantity() const;
    double getLineTotal() const;
    bool updateQuantity(int newQuantity);
};

#endif
