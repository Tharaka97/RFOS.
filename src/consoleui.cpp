#include "consoleui.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

ConsoleUI::ConsoleUI(Menu& menuRef, Order& orderRef, Bill& billRef, InputHandler& inputRef)
    : menu(menuRef), order(orderRef), bill(billRef), input(inputRef), running(true) {}

void ConsoleUI::displayMainMenu() const {
    std::cout << "\n============================================================\n";
    std::cout << "RESTAURANT FOOD ORDERING SYSTEM (RFOS)\n";
    std::cout << "V1.0 | Session Active\n";
    std::cout << "============================================================\n";
    std::cout << "[1] View Menu\n";
    std::cout << "[2] Place Order\n";
    std::cout << "[3] Modify Order\n";
    std::cout << "[4] View Current Order\n";
    std::cout << "[5] Calculate Bill and Checkout\n";
    std::cout << "[6] Cancel Order\n";
    std::cout << "[7] Manage Menu Items [Staff Only]\n";
    std::cout << "[0] Exit\n";
    std::cout << "============================================================\n";
}

void ConsoleUI::run() {
    while (running) {
        try {
            displayMainMenu();
            const int choice = input.getIntInRange(0, 7);

            switch (choice) {
                case 1: handleViewMenu(); break;
                case 2: handlePlaceOrder(); break;
                case 3: handleModifyOrder(); break;
                case 4: handleViewCurrentOrder(); break;
                case 5: handleCheckout(); break;
                case 6: handleCancelOrder(); break;
                case 7: handleManageMenu(); break;
                case 0:
                    running = false;
                    std::cout << "RFOS closed. Goodbye.\n";
                    break;
            }
        } catch (const std::runtime_error&) {
            std::cout << "\n>> ERROR: Input stream failure. RFOS will exit safely.\n";
            running = false;
        }
    }
}

void ConsoleUI::handleViewMenu() {
    menu.displayMenu();
}

int ConsoleUI::readExistingMenuItemId(const std::string& prompt, bool allowBack) {
    if (menu.isEmpty()) {
        return 0;
    }

    int highestId = 0;
    for (const auto& item : menu.getItems()) {
        highestId = std::max(highestId, item.getId());
    }

    while (true) {
        const int id = input.getIntInRange(allowBack ? 0 : 1, highestId, prompt);
        if (allowBack && id == 0) {
            return 0;
        }
        if (menu.getItem(id) != nullptr) {
            return id;
        }
        std::cout << ">> ERROR: Item not found. Please enter an available item ID.\n";
    }
}

int ConsoleUI::readExistingOrderItemId(const std::string& prompt, bool allowBack) {
    if (order.isEmpty()) {
        return 0;
    }

    int highestId = 0;
    for (const auto& orderItem : order.getItems()) {
        highestId = std::max(highestId, orderItem.getMenuItem().getId());
    }

    while (true) {
        const int id = input.getIntInRange(allowBack ? 0 : 1, highestId, prompt);
        if (allowBack && id == 0) {
            return 0;
        }
        if (order.findItem(id) != nullptr) {
            return id;
        }
        std::cout << ">> ERROR: The selected item is not in the current order.\n";
    }
}

void ConsoleUI::handlePlaceOrder() {
    if (menu.isEmpty()) {
        std::cout << ">> ERROR: No menu items are currently available.\n";
        return;
    }

    bool addAnother = true;
    while (addAnother) {
        menu.displayMenu();
        const int id = readExistingMenuItemId("Enter item ID (or 0 to finish): ");
        if (id == 0) {
            break;
        }

        const int quantity = input.getIntInRange(
            1, 100, "Enter quantity: ");

        const MenuItem* selected = menu.getItem(id);
        if (selected != nullptr && order.addItem(*selected, quantity)) {
            std::cout << ">> SUCCESS: Added " << selected->getName()
                      << " x" << quantity << " to order.\n";
        }

        addAnother = input.getConfirmation("Add another item? (Y/N): ");
    }
}

void ConsoleUI::displayCurrentOrder() const {
    std::cout << "\n============================================================\n";
    std::cout << "RFOS | CURRENT ORDER | " << order.getStatus() << '\n';
    std::cout << "============================================================\n";

    if (order.isEmpty()) {
        std::cout << "No items in current order.\n";
        std::cout << "============================================================\n";
        return;
    }

    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(28) << "Item"
              << std::right << std::setw(8) << "Qty"
              << std::setw(13) << "Total" << '\n';
    std::cout << "------------------------------------------------------------\n";

    for (const auto& item : order.getItems()) {
        std::cout << std::left << std::setw(5) << item.getMenuItem().getId()
                  << std::setw(28) << item.getMenuItem().getName()
                  << std::right << std::setw(8) << item.getQuantity()
                  << "   $" << std::setw(8) << std::fixed << std::setprecision(2)
                  << item.getLineTotal() << '\n';
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left << std::setw(43) << "SUBTOTAL"
              << "$" << std::right << std::setw(8) << std::fixed
              << std::setprecision(2) << order.getSubtotal() << '\n';
    std::cout << "============================================================\n";
}

void ConsoleUI::handleViewCurrentOrder() {
    displayCurrentOrder();
}

void ConsoleUI::handleModifyOrder() {
    if (order.isEmpty()) {
        std::cout << ">> ERROR: No items in the current order.\n";
        return;
    }

    displayCurrentOrder();
    std::cout << "[1] Update quantity\n";
    std::cout << "[2] Remove item\n";
    std::cout << "[0] Back to Main Menu\n";

    const int choice = input.getIntInRange(0, 2, "Select action: ");
    if (choice == 0) return;

    const int id = readExistingOrderItemId("Enter menu item ID (or 0 to go back): ");
    if (id == 0) return;

    if (choice == 1) {
        const int quantity = input.getIntInRange(1, 100, "Enter new quantity: ");
        if (order.updateQuantity(id, quantity)) {
            std::cout << ">> SUCCESS: Quantity updated.\n";
        }
    } else {
        if (input.getConfirmation(">> WARNING: Remove this item? (Y/N): ")) {
            if (order.removeItem(id)) {
                std::cout << ">> SUCCESS: Item removed from order.\n";
            }
        }
    }
}

void ConsoleUI::handleCheckout() {
    if (order.isEmpty()) {
        std::cout << ">> ERROR: No items in the current order.\n";
        std::cout << ">> Please add items before checking out.\n";
        return;
    }

    displayCurrentOrder();
    if (!input.getConfirmation("Confirm checkout? (Y/N): ")) {
        std::cout << "Checkout cancelled. Current order preserved.\n";
        return;
    }

    if (!bill.createBill(order)) {
        std::cout << ">> ERROR: Unable to create a bill for an empty order.\n";
        return;
    }

    bill.generateReceipt();
    order.completeOrder();
    std::cout << ">> SUCCESS: Order marked COMPLETE.\n";
}

void ConsoleUI::handleCancelOrder() {
    if (order.isEmpty()) {
        std::cout << ">> ERROR: No items in the current order.\n";
        return;
    }

    if (input.getConfirmation(">> WARNING: Cancel the current order? (Y/N): ")) {
        order.cancelOrder();
        std::cout << ">> SUCCESS: Current order cancelled and cleared.\n";
    } else {
        std::cout << "Cancellation aborted. Current order preserved.\n";
    }
}

void ConsoleUI::handleManageMenu() {
    std::cout << "\n============================================================\n";
    std::cout << "RFOS | MANAGE MENU ITEMS | Staff Only\n";
    std::cout << "============================================================\n";
    std::cout << "[1] Add menu item\n";
    std::cout << "[2] Remove menu item\n";
    std::cout << "[0] Back to Main Menu\n";

    const int choice = input.getIntInRange(0, 2, "Select action: ");
    if (choice == 0) return;

    if (choice == 1) {
        const std::string name = input.getString("Enter item name: ");
        const double price = input.getPositiveDouble("Enter item price: $");

        std::cout << "[1] STARTER\n";
        std::cout << "[2] MAIN\n";
        std::cout << "[3] BEVERAGE\n";
        const int categoryChoice = input.getIntInRange(1, 3, "Select category: ");

        const std::string category =
            categoryChoice == 1 ? "STARTER" :
            categoryChoice == 2 ? "MAIN" : "BEVERAGE";

        const int id = menu.addItem(name, price, category);
        if (id > 0) {
            std::cout << ">> SUCCESS: Menu item added with ID " << id << ".\n";
        } else {
            std::cout << ">> ERROR: Menu item could not be added.\n";
        }
        return;
    }

    if (menu.isEmpty()) {
        std::cout << ">> ERROR: No menu items are currently available.\n";
        return;
    }

    menu.displayMenu();
    const int id = readExistingMenuItemId("Enter item ID to remove (or 0 to go back): ");
    if (id == 0) return;

    if (input.getConfirmation(">> WARNING: Remove this menu item? (Y/N): ")) {
        if (menu.removeItem(id)) {
            std::cout << ">> SUCCESS: Menu item removed.\n";
        }
    }
}
