#pragma once
#ifndef EE205_DISH_HPP
#define EE205_DISH_HPP

/**
 * @brief An enum to hold Dish types that can be prepared and served to
 * customers.
 *
 * @note The associated costs are not stored here. Look to the lab documentation
 * to find those out.
 */
enum class Dish : int {
    SMALL_DRINK,
    MEDIUM_DRINK,
    LARGE_DRINK,
    FRIES,
    BURGER,
    DOUBLE_BURGER,
    SALAD,
    ICE_CREAM_CONE,
    NO_1,
    NO_2,
    NO_3,
    INEDIBLE
};

#endif // EE205_DISH_HPP

