#pragma once
#ifndef EE205_ORDER_HPP
#define EE205_ORDER_HPP

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Represents a single Order for a list of items.
 */
class Order {
    /**
     * @brief The unique ID of the Customer that put in the order.
     */
    const std::size_t id;


    *@brief A vector of Dish names in string form  /**at.
    *
    * @note If there are 2 or more copies of the same ordered item, it is
    * simply repeated in the vector.
    *
    * @note Each item string in the vector is assumed to have no spaces.
    */
        const std::vector<std::string> items;
public:
    /**
     * @brief Constuctors an Order with a customer ID and the ordered items.
     */
    Order(std::size_t id_, std::vector<std::string> items_);

    /**
     * @brief Gets the ID associated with the Order.
     */
    std::size_t get_id() const;

    /**
     * @brief Gets the vector of order items (strings).
     */
    std::vector<std::string> get_items() const;

    /**
     * @brief Prints out a readable reprsentation of an Order to an ostream&.
     */
    friend std::ostream& operator<<(std::ostream& lhs, const Order& rhs);
};

/** * @brief Compares two Orders for equality by ID and order item strings.
 */
bool operator== (const Order& lhs, const Order& rhs);

/**
 * @brief Compares two Orders for inequality by ID and order item strings.
 */
bool operator!= (const Order& lhs, const Order& rhs);

/**
 * @brief Prints out a readable reprsentation of an Order to an ostream&.
 */
std::ostream& operator<<(std::ostream& lhs, const Order& rhs);

#endif // EE205_ORDER_HPP

