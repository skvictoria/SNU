#pragma once
#ifndef EE205_CUSTOMER_HPP
#define EE205_CUSTOMER_HPP

#include <iostream>
#include <string>

/**
 * @brief A counter used to count how many times all Customer have been
 * expelled, unless reset manually.
 *
 * @todo Refactor this part from the program so that the global variable is not
 * exposed.
 */
extern std::size_t expelled_count;

/**
 * @brief A class to represent restaurant customers.
 */


class Customer {
private:
    /**
     * @brief Represents the amount of money that a Customer currently has.
     */
    double money;

    /**
     * @brief The string that the Customer gives as their "order."
     */
    std::string order_str;

    /**
     * @brief Whether or not the Customer was expelled from the restaurant.
     */
    bool expelled;

public:
    /**
     * @brief Constructs a Customer with a set amount of money and a string to
     * emit upon have its order taken as a string.
     */
    Customer(double money_, std::string order_str_);

    /**
     * @brief Gets the current amount of money on the Customer.
     */
    double get_money() const;
    /**
     * @brief Returns whether the Customer was expelled.
     */
    bool is_expelled() const;

    /**
     * @brief Returns the order_str on the Customer.
     */
    std::string take_order();

    /**
     * @brief Attempt to charge the amount of money from the Customer.
     *
     * @note If the Customer doesn't have enough money, it will simply return
     * its current money amount and drain its money to 0.
     */
    double charge_money(double amount);
    /**
     * @brief Refunds money back to the customer.
     *
     * @note There are no bounds checking on this code, so you can refund
     * negative money to charge money as well. Please do not do this; this is
     * not how this member function is supposed to be used.
     */
    void refund_money(double amount);

    /**
     * @brief Returns the order string.
     *
     * @see take_order()
     */
    std::string get_order() const;

    /**
     * @brief Expels the Customer from the restaurant.
     *
     * @note For the purposes of testing, this is attached to the `extern
     * std::size_t expelled_count` variable.
     *
     * @todo Revise the design of expellation and the unit test cases so
     * expellation can be unit tested without this global variable counter hack.
     */
    void expel();

    /**
     * @brief Prints out a string representation of the Customer's fields.
     */
    friend std::ostream& operator<<(std::ostream& lhs, const Customer& rhs);
};

/**
 * @brief Prints out a string representation of the Customer's fields.
 */
std::ostream& operator<<(std::ostream& lhs, const Customer& rhs);


#endif // EE205_CUSTOMER_HPP
