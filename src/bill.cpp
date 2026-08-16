#include "bill.h"

#include <iomanip>
#include <iostream>
#include <sstream>

Bill::Bill() : subtotal(0.0), gst(0.0), total(0.0) {}

bool Bill::createBill(const Order& order) {
    if (order.isEmpty()) {
        subtotal = gst = total = 0.0;
        receiptLines.clear();
        return false;
    }

    subtotal = order.getSubtotal();
    gst = subtotal * GST_RATE;
    total = subtotal + gst;
    receiptLines.clear();

    for (const auto& orderItem : order.getItems()) {
        std::ostringstream line;
        line << std::left << std::setw(28) << orderItem.getMenuItem().getName()
             << " x" << std::setw(3) << orderItem.getQuantity()
             << "$" << std::right << std::setw(8) << std::fixed
             << std::setprecision(2) << orderItem.getLineTotal();
        receiptLines.push_back(line.str());
    }

    return true;
}

void Bill::generateReceipt() const {
    std::cout << "\n============================================================\n";
    std::cout << "RFOS | RECEIPT\n";
    std::cout << "============================================================\n";
    for (const auto& line : receiptLines) {
        std::cout << line << '\n';
    }
    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left << std::setw(40) << "SUBTOTAL"
              << "$" << std::right << std::setw(8) << std::fixed
              << std::setprecision(2) << subtotal << '\n';
    std::cout << std::left << std::setw(40) << "GST (10%)"
              << "$" << std::right << std::setw(8) << gst << '\n';
    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left << std::setw(40) << "TOTAL"
              << "$" << std::right << std::setw(8) << total << '\n';
    std::cout << "============================================================\n";
}

double Bill::getSubtotal() const {
    return subtotal;
}

double Bill::getGST() const {
    return gst;
}

double Bill::getTotal() const {
    return total;
}

const std::vector<std::string>& Bill::getReceiptLines() const {
    return receiptLines;
}
