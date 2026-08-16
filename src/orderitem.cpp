#include "orderitem.h"

OrderItem::OrderItem(const MenuItem& item, int itemQuantity)
    : menuItem(item), quantity(itemQuantity) {}

const MenuItem& OrderItem::getMenuItem() const {
    return menuItem;
}

int OrderItem::getQuantity() const {
    return quantity;
}

double OrderItem::getLineTotal() const {
    return menuItem.getPrice() * quantity;
}

bool OrderItem::updateQuantity(int newQuantity) {
    if (newQuantity < 1) {
        return false;
    }

    quantity = newQuantity;
    return true;
}
