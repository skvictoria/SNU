#pragma once
#ifndef EE205_SUPPLY_RUNNER_HPP
#define EE205_SUPPLY_RUNNER_HPP

#include "Storeroom.hpp"
#include "Ingredient.hpp"

#include <string>
#include <vector>
#include <map>

/**
 * @brief Gets Ingredients from the Storeroom.
 */
class SupplyRunner {
    /**
     * @brief The Storeroom associated with the SupplyRunner.
     */
    Storeroom& storeroom;
public:
    /**
     * @brief Constructs a SupplyRunner with the Storeroom it gets its
     * Ingredients from.
     */
    SupplyRunner(Storeroom& storeroom_);

    /**
     * @brief Gets ingredients from the Storeroom, if they exist, as a vector.
     *
     * @note Will remove ingredients from the storeroom if all the ingredeints
     * asked for are all found in sufficient numbers.
     *
     * @throws const char* if there are not enough ingredients in the Storeroom.
     *
     * @note Upon not finding enough ingredients to return, the SupplyRunner
     * will not modify the Storeroom in any way, including removing Ingredients
     * from the Storeroom (decreasing the Ingredient count on the map).
     */
    std::vector<Ingredient> get_ingredients(IngredientMap ingredients);
};

#endif // EE205_SUPPLY_RUNNER_HPP
