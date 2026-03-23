#include <iostream>
#include <vector>
using namespace std;


class Account {
protected:
    int accountNumber;
    double balance;
    string accountHolderName;
    string accountType;

public:
    Account(int accNo, string name, double bal, string type = "Generic")
        : accountNumber(accNo), accountHolderName(name), balance(bal), accountType(type) {}

    // Deposit function
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    // Withdraw function
    virtual void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    // Virtual interest calculation
    virtual void calculateInterest() {
        cout << "No interest for base account.\n";
    }

    // Print statement
    virtual void printStatement() {
        cout << "\n--- Account Statement ---\n";
        cout << "Account No: " << accountNumber << endl;
        cout << "Name: " << accountHolderName << endl;
        cout << "Type: " << accountType << endl;
        cout << "Balance: " << balance << endl;
    }

    // Get account info
    void getAccountInfo() {
        cout << "Account [" << accountNumber << "] - " << accountHolderName
             << " | Type: " << accountType << endl;
    }

    virtual ~Account() {}
};

// Savings Account
class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(int accNo, string name, double bal, double rate, double minBal)
        : Account(accNo, name, bal, "Savings"),
          interestRate(rate), minimumBalance(minBal) {}

    void calculateInterest() override {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Savings Interest Added: " << interest << endl;
    }

    void withdraw(double amount) override {
        if (balance - amount >= minimumBalance) {
            balance -= amount;
            cout << "Withdrawn (Savings): " << amount << endl;
        } else {
            cout << "Cannot withdraw! Minimum balance must be maintained.\n";
        }
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Interest Rate: " << interestRate << "%\n";
        cout << "Minimum Balance: " << minimumBalance << endl;
    }
};

// Checking Account
class CheckingAccount : public Account {
private:
    double transactionFee;

public:
    CheckingAccount(int accNo, string name, double bal, double fee)
        : Account(accNo, name, bal, "Checking"),
          transactionFee(fee) {}

    void withdraw(double amount) override {
        double total = amount + transactionFee;
        if (total <= balance) {
            balance -= total;
            cout << "Withdrawn (Checking): " << amount
                 << " | Fee: " << transactionFee << endl;
        } else {
            cout << "Insufficient balance including transaction fee!\n";
        }
    }

    void calculateInterest() override {
        cout << "Checking accounts typically have no interest.\n";
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Transaction Fee: " << transactionFee << endl;
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public Account {
private:
    int maturityYears;
    double fixedInterestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int years, double rate)
        : Account(accNo, name, bal, "Fixed Deposit"),
          maturityYears(years), fixedInterestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * fixedInterestRate * maturityYears / 100;
        cout << "Fixed Deposit Interest after " << maturityYears
             << " years: " << interest << endl;
    }

    void withdraw(double amount) override {
        cout << "Withdrawal not allowed before maturity!\n";
    }

    void printStatement() override {
        Account::printStatement();
        cout << "Maturity Years: " << maturityYears << endl;
        cout << "Fixed Interest Rate: " << fixedInterestRate << "%\n";
    }
};


int main() {
    vector<Account*> accounts;

    accounts.push_back(new SavingsAccount(101, "Ali", 5000, 5.0, 1000));
    accounts.push_back(new CheckingAccount(102, "Sara", 3000, 50));
    accounts.push_back(new FixedDepositAccount(103, "Ahmed", 10000, 5, 7.5));

    for (Account* acc : accounts) {
        acc->getAccountInfo();
        acc->deposit(500);
        acc->withdraw(700);
        acc->calculateInterest();
        acc->printStatement();
    }

    // Cleanup
    for (Account* acc : accounts) {
        delete acc;
    }

    return 0;
}
