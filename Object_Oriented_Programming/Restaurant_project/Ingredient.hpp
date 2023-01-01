#pragma once
#ifndef EE205_INGREDIENT_HPP
#define EE205_INGREDIENT_HPP

#include <map>
#include <string>
#include <iostream>

// Ingredient becomes another name for std::string.
// // This is pretty much a C++-version of typedef.
using Ingredient = std::string;

// IngredientMap becomes another name for std::map<Ingredient, unsigned>
// and represents a set of ingredients and how many of each ingredient type
// there are.
using IngredientMap = std::map<Ingredient, unsigned>;

// A helper function to help print out the Ingredients in a map.
std::ostream& operator<<(
    std::ostream& lhs,
    const std::map<std::string, unsigned>& rhs);

#endif // EE205_INGREDIENT_HPP
