#ifndef ORDER_H
#define ORDER_H

#include "orderitem.h"

#include <string>
#include <vector>

class Order {
private:
    std::vector<OrderItem> items;
    std::string orderStatus;

public:
    Order();

    bool addItem(const MenuItem& item, int quantity);
    bool addItem(const OrderItem& orderItem);
    bool removeItem(int menuItemId);
    bool updateQuantity(int menuItemId, int quantity);
    OrderItem* findItem(int menuItemId);
    const OrderItem* findItem(int menuItemId) const;

    double getSubtotal() const;
    const std::vector<OrderItem>& getItems() const;
    void cancelOrder();
    void completeOrder();
    bool isEmpty() const;
    const std::string& getStatus() const;
};

#endif
