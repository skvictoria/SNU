#pragma once
#ifndef EE205_KITCHEN_HPP
#define EE205_KITCHEN_HPP

#include <map>
#include <string>
#include <iostream>

#include "Ingredient.hpp"
#include "Dish.hpp"

/**
 * @brief A Kitchen that can be used to prepare Dish objects by providing them a
 * moved-map of ingredients.
 */
class Kitchen {
public:
    /**
     * @brief Consumes the map of ingredients (std::string) and returns the
     * corresponding Dish.
     *
     * @note This will return Dish::INEDIBLE if a map of ingredients that
     * dosn't correspond to a proper dish is given.
     *
     * @note You must noticably MOVE the ingredients in or give it a map
     * literal.
     *
     * @see Ingredient.hpp
     *
     * @note Look at the lab manual for more information about the item costs.
     */
    Dish prepare_dish(IngredientMap&& ingredients);
};

#endif // EE205_KITCHEN_HPP
