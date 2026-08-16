#include "order.h"

Order::Order() : orderStatus("ACTIVE") {}

bool Order::addItem(const MenuItem& item, int quantity) {
    if (quantity < 1) {
        return false;
    }

    if (auto* existing = findItem(item.getId())) {
        return existing->updateQuantity(existing->getQuantity() + quantity);
    }

    items.emplace_back(item, quantity);
    orderStatus = "ACTIVE";
    return true;
}

bool Order::addItem(const OrderItem& orderItem) {
    return addItem(orderItem.getMenuItem(), orderItem.getQuantity());
}

bool Order::removeItem(int menuItemId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getMenuItem().getId() == menuItemId) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

bool Order::updateQuantity(int menuItemId, int quantity) {
    auto* item = findItem(menuItemId);
    return item != nullptr && item->updateQuantity(quantity);
}

OrderItem* Order::findItem(int menuItemId) {
    for (auto& item : items) {
        if (item.getMenuItem().getId() == menuItemId) {
            return &item;
        }
    }
    return nullptr;
}

const OrderItem* Order::findItem(int menuItemId) const {
    for (const auto& item : items) {
        if (item.getMenuItem().getId() == menuItemId) {
            return &item;
        }
    }
    return nullptr;
}

double Order::getSubtotal() const {
    double subtotal = 0.0;
    for (const auto& item : items) {
        subtotal += item.getLineTotal();
    }
    return subtotal;
}

const std::vector<OrderItem>& Order::getItems() const {
    return items;
}

void Order::cancelOrder() {
    items.clear();
    orderStatus = "CANCELLED";
}

void Order::completeOrder() {
    items.clear();
    orderStatus = "COMPLETE";
}

bool Order::isEmpty() const {
    return items.empty();
}

const std::string& Order::getStatus() const {
    return orderStatus;
}
