#include "Customer.hpp"

std::size_t expelled_count = 0;

Customer::Customer(double money_, std::string order_str_) :
    money(money_),
    order_str(order_str_),
    expelled(false) {
}

double Customer::get_money() const {
    std::cout << "Customer: The customer has " << money << std::endl;
    return this->money;
}

bool Customer::is_expelled() const { return this->expelled; }

std::string Customer::take_order() {
    std::cout << "Customer: A customer gives their order: " << order_str << std::endl;
    return this->order_str;
}

double Customer::charge_money(double amount) {
    std::cout << "Customer: The customer is charged " << amount << std::endl;
    if (money - amount < 0) {
        double temp = money;
        money = 0;
        std::cout << "Customer: The customer can pay only " << temp << std::endl;
        return temp;
    }
    else {
        money -= amount;
        std::cout << "Customer: The customer pays " << amount << std::endl;
        return amount;
    }
}

void Customer::refund_money(double amount) {
    std::cout << "Customer: The customer is refunded " << amount << std::endl;
    money += amount;
}

std::string Customer::get_order() const {
    std::cout << "Customer: A customer gives their order" << std::endl;
    return order_str;
}

void Customer::expel() {
    std::cout << "Customer: The customer was expelled" << std::endl;
    this->expelled = true;
    expelled_count++;
}

std::ostream& operator<<(std::ostream& lhs, const Customer& rhs) {
    lhs << "Customer(" << rhs.money
        << "|\"" << rhs.order_str << "\""
        << "|" << rhs.expelled << ")";
    return lhs;
}
