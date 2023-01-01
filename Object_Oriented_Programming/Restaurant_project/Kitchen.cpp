#include "Kitchen.hpp"

Dish Kitchen::prepare_dish(IngredientMap&& ingredients) {
    std::cout << "Got ingredients: " << ingredients << std::endl;
    if (ingredients == IngredientMap{
            {"Potato", 1},
            {"CanolaOil", 1}
        }) {
        std::cout << "Kitchen: Prepared Fries" << std::endl;
        return Dish::FRIES;
    }
    else if (ingredients == IngredientMap{
            {"WheatBun", 2},
            {"BeefPatty", 1},
            {"Cheese", 1},
            {"Lettuce", 1},
            {"Tomato", 1}
        }) {
        std::cout << "Kitchen: Prepared Burger" << std::endl;
        return Dish::BURGER;
    }
    else if (ingredients == IngredientMap{
            {"WheatBun", 3},
            {"BeefPatty", 2},
            {"Cheese", 2},
            {"Lettuce", 3},
            {"Tomato", 1}
        }) {
        std::cout << "Kitchen: Prepared DoubleBurger" << std::endl;
        return Dish::DOUBLE_BURGER;
    }
    else if (ingredients == IngredientMap{
            {"SugarCone", 1},
            {"VanillaCream", 1}
        }) {
        std::cout << "Kitchen: Prepared IceCreamCone" << std::endl;
        return Dish::ICE_CREAM_CONE;
    }
    else if (ingredients == IngredientMap{
            {"SmallCup", 1}
        }) {
        std::cout << "Kitchen: Prepared SmallDrink" << std::endl;
        return Dish::SMALL_DRINK;
    }
    else if (ingredients == IngredientMap{
            {"MediumCup", 1}
        }) {
        std::cout << "Kitchen: Prepared MediumDrink" << std::endl;
        return Dish::MEDIUM_DRINK;
    }
    else if (ingredients == IngredientMap{
            {"LargeCup", 1}
        }) {
        std::cout << "Kitchen: Prepared LargeDrink" << std::endl;
        return Dish::LARGE_DRINK;
    }
    else if (ingredients == IngredientMap{
            {"Lettuce", 1},
            {"Tomato", 1},
            {"SaladDressing", 1},
            {"Fork", 1}
        }) {
        std::cout << "Kitchen: Prepared Salad" << std::endl;
        return Dish::SALAD;
    }
    else if (ingredients == IngredientMap{
            {"MediumCup", 1},
            {"Potato", 1},
            {"CanolaOil", 1},
            {"WheatBun", 2},
            {"BeefPatty", 1},
            {"Cheese", 1},
            {"Lettuce", 1},
            {"Tomato", 1}
        }) {
        std::cout << "Kitchen: Prepared #1" << std::endl;
        return Dish::NO_1;
    }
    else if (ingredients == IngredientMap{
            {"MediumCup", 1},
            {"Potato", 1},
            {"CanolaOil", 1},
            {"WheatBun", 3},
            {"BeefPatty", 2},
            {"Cheese", 2},
            {"Lettuce", 3},
            {"Tomato", 1}
        }) {
        std::cout << "Kitchen: Prepared #2" << std::endl;
        return Dish::NO_2;
    }

    else if (ingredients == IngredientMap{
            {"MediumCup", 1},
            {"Potato", 1},
            {"CanolaOil", 1},
            {"WheatBun", 4},
            {"BeefPatty", 2},
            {"Cheese", 2},
            {"Lettuce", 2},
            {"Tomato", 2}
        }) {
        std::cout << "Kitchen: Prepared #3" << std::endl;
        return Dish::NO_3;
    }
    else {
        std::cout << "Kitchen: Prepared something inedible..." << std::endl;
        return Dish::INEDIBLE;
    }
}
