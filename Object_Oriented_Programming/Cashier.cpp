#include "Cashier.hpp"
#include "Customer.hpp"
#include "Order.hpp"

Cashier::Cashier(double money_) {

    this->uid_count = 0;
    this->money = money_;
}

double Cashier::get_money() const {

    return this->money;
}



/**
    * Serves a customer by taking them off the queue, and possibly
    * putting an order, if valid, onto the order stack.
    *
    * - Retrieves the customer from the queue, popping them off.
    *
    * - Receives the customer's desired order items in string format:
    *
    *
    *      <number-of-items> <name-of-item-with-no-spaces>
    *
    *      - Multiple items are separated simply by a space
    *
    * - If the Cashier detects an order for an invalid item that is not on
    *   the menu, it must expel() the customer.
    *
    * - Must calculate the cost of all the items ordered, and charge the
    *   customer.
    *
    *      - It the customer does not have enough money to pay, do not
    *      charge the customer, but instead, expel() them.
    *
    * - Once paid for, the order items must be consolidated into an Order,
    *   which is tagged with the unique customer ID generated at the
    *   beginning of this function, and then push it onto the stack.
    *
    */
void Cashier::serve_customer(
    std::queue<Customer>& line,
    std::stack<Order>& orders) {

    Customer customer = line.front();
    std::string txt = customer.take_order();
    std::vector<std::string> product = split(txt, ' ');
    int i = 0;

    std::vector<std::string> productarr;
    while (i < product.size()) {
        int len = std::stoi(product[i++]);
        while (len--) productarr.push_back(product[i]);
        i++;
    }

    double dollar;
    try {
        dollar = calculate_order_cost(productarr);
    }
    catch (std::string Exception) {
        std::cout << Exception << std::endl;
        customer.expel();
        line.pop();
        return;
    }
    customer.charge_money(dollar);
    if (customer.charge_money(dollar) != dollar)
    {
        customer.refund_money(dollar);
        customer.expel();
        line.pop();
        return;
    }
    this->money += dollar;
    
    std::cout << this->money << “, ” << dollar << std::endl;
    // check if increase as expected
    std::size_t id_ = uid_count++;
    Order order(id_, productarr);
    line.pop();
    orders.push(order);
}
