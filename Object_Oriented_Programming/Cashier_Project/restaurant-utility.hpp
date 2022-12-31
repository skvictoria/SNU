#pragma once
#ifndef EE205_RESTAURANT_UTILITY_HPP
#define EE205_RESTAURANT_UTILITY_HPP

#include <string>
#include <sstream>
#include <vector>

/**
 * @brief Calculates the order cost from the vector of passed order item
 * strings.
 *
 * @note See the lab manual for the appropriate costs.
 */
double calculate_order_cost(const std::vector<std::string>& items);

/**
 * @brief Splits a single string into a vector of strings with a single
 * character acting as a "splitter" or delimiter.
 */
std::vector<std::string> split(const std::string& s, char delimiter);

#endif // EE205_RESTAURANT_UTILITY_HPP
