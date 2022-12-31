#define CATCH_CONFIG_MAIN
//#include "catch.hpp"

//#include "Customer.hpp"
#include "Cashier.hpp"

#include <queue>

TEST_CASE("Single Item", "[Cashier]") {
    expelled_count = 0;
    Cashier cashier(100);
    // Given: a line of Customers, each with money and a set of items to order
    std::queue<Customer> line({
        {10, "1 Burger"}
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line
    cashier.serve_customer(line, orders);
    // Then: the line should be empty.
    REQUIRE(line.empty());
    // Then: the amount charged should be 2.39, the cost of 1 Burger
    REQUIRE(cashier.get_money() == 100 + 2.39);
    // Then: there should be 1 Order on the stack.
    REQUIRE(orders.size() == 1);
    // Then: the order on the stack should have an ID of 0 and a
    // single order of 1 Burger in the vector.
    REQUIRE(orders.top() == Order(0, { "Burger" }));
}

TEST_CASE("Double Item", "[Cashier]") {
    expelled_count = 0;
    Cashier cashier(100);
    // Given: a Customer in line who wants to order 2 Burger
    std::queue<Customer> line({
        {10, "2 Burger"}
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line
    cashier.serve_customer(line, orders);
    // Then: the line should be empty.
    REQUIRE(line.empty());
    // Then: the amount charged should be 2.39*2, the cost of 2 Burger
    REQUIRE(cashier.get_money() == 100 + 2 * 2.39);
    // Then: there should be 1 Order on the stack.
    REQUIRE(orders.size() == 1);
    // Then: the orders should look like this:
    REQUIRE(orders.top() == Order(0, { "Burger", "Burger" }));
}

TEST_CASE("Multi Item", "[Cashier]") {
    expelled_count = 0;
    Cashier cashier(100);
    // Given: a Customer in line who wants to order 2 Burger
    std::queue<Customer> line({
        {15, "1 Burger 1 #1 2 LargeDrink"}
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line
    cashier.serve_customer(line, orders);
    // Then: the line should be empty.
    REQUIRE(line.empty());
    // Then: the amount charged should be 2.39*2, the cost of 2 Burger
    REQUIRE(cashier.get_money() == 100 + 1 * 2.39 + 1 * 6.99 + 2 * 2.00);
    // Then: there should be 1 Order on the stack.
    REQUIRE(orders.size() == 1);
    // Then: the orders should look like this:
    REQUIRE(orders.top() == Order(0, { "Burger", "#1", "LargeDrink", "LargeDrink" }));
}

TEST_CASE("Multi Customer", "[Cashier]") {
    expelled_count = 0;
    Cashier cashier(100);

    // Given: a queue with 2 Customers
    std::queue<Customer> line({
        {15, "1 Burger 1 #1 2 LargeDrink"},
        {10, "4 Fries"}
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line twice
    cashier.serve_customer(line, orders);
    cashier.serve_customer(line, orders);

    // Then: the line should be empty.
    REQUIRE(line.empty());
    // Then: the amount charged should be the right one.
    REQUIRE(cashier.get_money() == 100 + 1 * 2.39 + 1 * 6.99 + 2 * 2.00 + 4 * 1.20);
    // Then: there should be 2 Order on the stack.
    REQUIRE(orders.size() == 2);
    // Then: the orders should look like this:
    REQUIRE(orders.top() == Order(1, { "Fries","Fries","Fries","Fries" }));
    orders.pop();
    REQUIRE(orders.top() == Order(0, { "Burger", "#1", "LargeDrink", "LargeDrink" }));
}

TEST_CASE("No Money? Expel", "[Cashier]") {
    Cashier cashier(100);

    // Given: the customer has no money.
    std::queue<Customer> line({
        {0, "1 Burger 1 #1 2 LargeDrink"},
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line
    cashier.serve_customer(line, orders);
    // Then: the line should be empty
    REQUIRE(line.empty());
    // Then: there should be no orders on the stack
    REQUIRE(orders.empty());
    // Then: the amount charged should be 0
    REQUIRE(cashier.get_money() == 100);
    // Then: the number of expel should be 1
    REQUIRE(expelled_count == 1);
}

TEST_CASE("Invalid Item? Expel", "[Cashier]") {
    expelled_count = 0;
    Cashier cashier(100);

    // Given: the customer has no money.
    std::queue<Customer> line({
        {0, "1 BigBadBurger"},
        });
    // Given: a stack of Orders to put new orders onto
    std::stack<Order> orders;
    // When: you serve the customer in line
    cashier.serve_customer(line, orders);
    // Then: the line should be empty
    REQUIRE(line.empty());
    // Then: there should be no orders on the stack
    REQUIRE(orders.empty());
    // Then: the amount charged should be 0
    REQUIRE(cashier.get_money() == 100);
    // Then: the number of expel should be 1
    REQUIRE(expelled_count == 1);
}


size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}
