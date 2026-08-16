#include "bill.h"
#include "menu.h"
#include "order.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace {
bool nearlyEqual(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}
}

int main() {
    Menu menu;
    const int salmonId = menu.addItem("Grilled Salmon", 28.00, "MAIN");
    const int lemonadeId = menu.addItem("Lemonade", 5.00, "BEVERAGE");

    assert(salmonId == 1);
    assert(lemonadeId == 2);
    assert(menu.getItem(99) == nullptr);

    Order order;
    assert(order.isEmpty());

    assert(order.addItem(*menu.getItem(salmonId), 2));
    assert(order.addItem(*menu.getItem(lemonadeId), 3));
    assert(nearlyEqual(order.getSubtotal(), 71.00));

    // Adding the same menu item merges into its existing order line.
    assert(order.addItem(*menu.getItem(lemonadeId), 1));
    assert(order.findItem(lemonadeId)->getQuantity() == 4);
    assert(nearlyEqual(order.getSubtotal(), 76.00));

    assert(order.updateQuantity(lemonadeId, 2));
    assert(nearlyEqual(order.getSubtotal(), 66.00));

    Bill bill;
    assert(bill.createBill(order));
    assert(nearlyEqual(bill.getSubtotal(), 66.00));
    assert(nearlyEqual(bill.getGST(), 6.60));
    assert(nearlyEqual(bill.getTotal(), 72.60));

    assert(order.removeItem(lemonadeId));
    assert(!order.removeItem(999));

    order.cancelOrder();
    assert(order.isEmpty());
    assert(order.getStatus() == "CANCELLED");

    std::cout << "All RFOS tests passed.\n";
    return 0;
}
