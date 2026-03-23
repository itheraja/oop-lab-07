#include <iostream>
using namespace std;


class Currency {
protected:
    double amount;
    string currencyCode;
    string currencySymbol;
    double exchangeRate; // relative to base currency (e.g., USD as base)

public:
    Currency(double amt, string code, string symbol, double rate)
        : amount(amt), currencyCode(code), currencySymbol(symbol), exchangeRate(rate) {}

    // Convert to base currency
    virtual double convertToBase() {
        return amount * exchangeRate;
    }

    // Convert to another currency
    double convertTo(Currency &target) {
        double baseAmount = convertToBase();
        return baseAmount / target.exchangeRate;
    }

    // Display function
    virtual void displayCurrency() {
        cout << currencySymbol << amount << " (" << currencyCode << ")" << endl;
    }

    virtual ~Currency() {}
};

// Dollar Class (Base Currency)
class Dollar : public Currency {
public:
    Dollar(double amt)
        : Currency(amt, "USD", "$", 1.0) {}

    double convertToBase() override {
        return amount; // already base
    }

    void displayCurrency() override {
        cout << "Dollar: $" << amount << endl;
    }
};

// Euro Class
class Euro : public Currency {
public:
    Euro(double amt)
        : Currency(amt, "EUR", "€", 1.1) {} // Example: 1 EUR = 1.1 USD

    double convertToBase() override {
        return amount * exchangeRate;
    }

    void displayCurrency() override {
        cout << "Euro: €" << amount << endl;
    }
};

// Rupee Class
class Rupee : public Currency {
public:
    Rupee(double amt)
        : Currency(amt, "PKR", "Rs", 0.0036) {} // Example: 1 PKR = 0.0036 USD

    double convertToBase() override {
        return amount * exchangeRate;
    }

    void displayCurrency() override {
        cout << "Rupee: Rs " << amount << endl;
    }
};

int main() {
    Dollar usd(100);   // $100
    Euro eur(50);      // €50
    Rupee pkr(10000);  // Rs 10000

    usd.displayCurrency();
    eur.displayCurrency();
    pkr.displayCurrency();


    // Convert Euro to Dollar
    cout << "Euro to Dollar: $" << eur.convertTo(usd) << endl;

    // Convert Rupee to Dollar
    cout << "Rupee to Dollar: $" << pkr.convertTo(usd) << endl;

    // Convert Dollar to Euro
    cout << "Dollar to Euro: €" << usd.convertTo(eur) << endl;

    // Convert Rupee to Euro
    cout << "Rupee to Euro: €" << pkr.convertTo(eur) << endl;

    return 0;
}
