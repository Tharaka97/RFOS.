#include "bill.h"
#include "consoleui.h"
#include "inputhandler.h"
#include "menu.h"
#include "order.h"

#include <iostream>

namespace {
void seedMenu(Menu& menu) {
    // Seed data is based on examples shown in the SDS console wireframes.
    menu.addItem("Garlic Bread", 6.50, "STARTER");
    menu.addItem("Caesar Salad", 12.00, "STARTER");
    menu.addItem("Soup of the Day", 9.50, "STARTER");
    menu.addItem("Grilled Salmon", 28.00, "MAIN");
    menu.addItem("Ribeye Steak", 34.00, "MAIN");
    menu.addItem("Mushroom Risotto", 22.00, "MAIN");
    menu.addItem("Lemonade", 5.00, "BEVERAGE");
    menu.addItem("Coffee", 4.50, "BEVERAGE");
}
}

int main() {
    Menu menu;
    Order order;
    Bill bill;
    InputHandler input;

    seedMenu(menu);

    ConsoleUI ui(menu, order, bill, input);
    ui.run();

    return 0;
}
