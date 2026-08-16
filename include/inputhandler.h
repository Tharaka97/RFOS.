#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>

class InputHandler {
public:
    int getIntInRange(int min, int max, const std::string& prompt = "Enter choice: ") const;
    double getPositiveDouble(const std::string& prompt) const;
    bool getConfirmation(const std::string& prompt = "Confirm? (Y/N): ") const;
    std::string getString(const std::string& prompt = "Enter value: ") const;

private:
    static std::string trim(const std::string& value);
};

#endif
