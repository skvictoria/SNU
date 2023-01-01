#pragma once
#ifndef EE205_COOK_HPP
#define EE205_COOK_HPP

#include "Dish.hpp"
#include "Order.hpp"
#include "SupplyRunner.hpp"
#include "Kitchen.hpp"

#include <queue>
#include <stack>

// Here, we use alias to make reading the code a bit easier.
using Ingredient = std::string;
using IngredientMap = std::map<Ingredient, unsigned>;
using RecipeBook = std::map<std::string, std::map<Ingredient, unsigned>>;

/**
 * @brief The map of recipe names to numbers of ingredients required to cook the
 * recipe.
 *
 * This is used in order to lookup how many ingredients of each type you need to
 * prepare a certain Dish.
 */
extern RecipeBook recipes;

/**
 * @brief Prepares dishes using a SupplyRunner and a Kitchen.
 *
 * @note Uses dependency injection with the constructor.
 */
class Cook {
private:
    /**
     * @brief The SupplyRunner that the cook will use to fetch ingredients
     * for prepartion.
     *
     * @note The SupplyRunner is not required to return items in the same
     * order you ask for them.
     */
    SupplyRunner& runner;

    /**
     * @brief The kitchen that will be used to prepare the Dish items that
     * will be put onto the output queue.
     *
     * @note Kitchen's prepare_dish() member function returns different
     * types of Dishes depending on how many ingredients you give it and
     * what types you give it.

     */
    Kitchen& kitchen;
public:
    /**
     * @brief Constructs a Cook with references to a SupplyRunner and a
     * Kitchen, which it must use in the process of cooking.
     */
    Cook(SupplyRunner& runner_, Kitchen& kitchen_);

    /**
     * @brief Prepares Dishes from a single order.
     *
     * - Take an Order from the stack.
     * - For each order item in the Order,
     *      - Lookup its required ingredients in the RecipeBook.
     *      - Then, ask the SupplyRunner to get the correct amount of
     *      ingredients.
     *      - Put the vector of ingredients into an IngredientMap.
     *      - Send the IngredientMap to the Kitchen to have it turned into a
     *      dish.
     *      - Put the finished Dish onto the queue, embedding it in a pair
     *      that also contains the Customer ID of origin.
     */
    void prepare_dish(
        std::stack<Order>& orders,
        std::queue<std::pair<std::size_t, Dish>>& finished_dishes);
};


#endif // EE205_COOK_HPP
