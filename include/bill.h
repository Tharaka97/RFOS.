#ifndef BILL_H
#define BILL_H

#include "order.h"

#include <string>
#include <vector>

class Bill {
private:
    double subtotal;
    double gst;
    double total;
    std::vector<std::string> receiptLines;

public:
    static constexpr double GST_RATE = 0.10;

    Bill();

    bool createBill(const Order& order);
    void generateReceipt() const;

    double getSubtotal() const;
    double getGST() const;
    double getTotal() const;
    const std::vector<std::string>& getReceiptLines() const;
};

#endif
