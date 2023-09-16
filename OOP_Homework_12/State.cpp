#include <iostream>
#include <string>
using namespace std;

class VendingMachineState
{
public:
    virtual void insertCurrency(int amount) = 0;
    virtual void selectProduct(string product) = 0;
    virtual void dispenseProduct() = 0;
    virtual void returnChange() = 0;
};

class VendingDepositState : public VendingMachineState 
{
public:
    VendingDepositState() : depositedAmount(0) {}

    void insertCurrency(int amount) override {
        depositedAmount += amount;
        cout << "Deposited: " << depositedAmount << " dollars." << endl;
    }
    void selectProduct(string product) override {
        cout << "Selected: " << product << ". Processing..." << endl;
    }
    void dispenseProduct() override {
        cout << "Dispensing the product." << endl;
    }
    void returnChange() override {
        cout << "Returning " << depositedAmount << " dollars." << endl;
        depositedAmount = 0;
    }
private:
    int depositedAmount;
};

class VendingStockState : public VendingMachineState
{
public:
    void insertCurrency(int amount) override {
        cout << "You've already inserted money. Make a product selection." << endl;
    }
    void selectProduct(string product) override {
        cout << "You've selected " << product << ". Dispensing the product." << endl;
    }
    void dispenseProduct() override {
        cout << "Product dispensed." << endl;
    }
    void returnChange() override {
        cout << "No money to return." << endl;
    }
};

class VendingMachine 
{
public:
    VendingMachine() {
        currentState = new VendingDepositState();
    }
    void setCurrentState(VendingMachineState* state) {
        delete currentState;
        currentState = state;
    }
    void insertCurrency(int amount) {
        currentState->insertCurrency(amount);
    }
    void selectProduct(string product) {
        currentState->selectProduct(product);
    }
    void dispenseProduct() {
        currentState->dispenseProduct();
        setCurrentState(new VendingStockState());
    }
    void returnChange() {
        currentState->returnChange();
    }
private:
    VendingMachineState* currentState;
};

int main()
{
    VendingMachine vendingMachine;

    vendingMachine.insertCurrency(3);
    vendingMachine.selectProduct("Chips");
    vendingMachine.dispenseProduct();
    vendingMachine.returnChange();

    system("pause");

    return 0;
}
