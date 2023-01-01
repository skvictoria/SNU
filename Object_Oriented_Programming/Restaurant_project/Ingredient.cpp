#include "Ingredient.hpp"

std::ostream& operator<<(
    std::ostream& lhs,
    const std::map<std::string, unsigned>& rhs) {
    std::size_t count = 1;
    lhs << "Ingredients(\n";
    for (const auto& it : rhs) {
        lhs << "\t{" << it.first << " | " << it.second << "}\n";
        ++count;
    }
    lhs << ")";
    return lhs;
}
