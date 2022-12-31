#include "restaurant-utility.hpp"

double calculate_order_cost(const std::vector<std::string>& items) {
    double cost = 0;
    for (unsigned i = 0; i < items.size(); ++i) {
        if (items[i] == "SmallDrink") {
            cost += 1.25;
        }
        else if (items[i] == "MediumDrink") {
            cost += 1.50;
        }
        else if (items[i] == "LargeDrink") {
            cost += 2.00;
        }
        else if (items[i] == "Burger") {
            cost += 2.39;
        }
        else if (items[i] == "DoubleBurger") {
            cost += 3.99;
        }
        else if (items[i] == "Fries") {
            cost += 1.20;
        }
        else if (items[i] == "Salad") {
            cost += 2.99;
        }
        else if (items[i] == "IceCreamCone") {
            cost += 1.59;
        }
        else if (items[i] == "#1") {
            cost += 6.99;
        }
        else if (items[i] == "#2") {
            cost += 7.39;
        }
        else if (items[i] == "#3") {
            cost += 5.99;
        }
        else {
            throw "No order.";
        }
    }
    return cost;
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
