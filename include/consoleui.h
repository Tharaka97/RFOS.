#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "bill.h"
#include "inputhandler.h"
#include "menu.h"
#include "order.h"

class ConsoleUI {
private:
    Menu& menu;
    Order& order;
    Bill& bill;
    InputHandler& input;
    bool running;

    void displayMainMenu() const;
    void handleViewMenu();
    void handlePlaceOrder();
    void handleModifyOrder();
    void handleViewCurrentOrder();
    void handleCheckout();
    void handleCancelOrder();
    void handleManageMenu();

    void displayCurrentOrder() const;
    int readExistingMenuItemId(const std::string& prompt, bool allowBack = true);
    int readExistingOrderItemId(const std::string& prompt, bool allowBack = true);

public:
    ConsoleUI(Menu& menu, Order& order, Bill& bill, InputHandler& input);
    void run();
};

#endif
