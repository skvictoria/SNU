#include "Cook.hpp"
#include "Ingredient.hpp"
#include "Storeroom.hpp"
#include "SupplyRunner.hpp"

RecipeBook recipes = { {“a”,{{“b”.1}}},{“b”,{{“b”,1}}},{“c”,{{“b”,1}}} };

void main(void)
{
    Storeroom imap = { {“hello”,1},{“there”,2} };
    SupplyRunner srun(imap);
    Kitchen kt;
    Cook cook(srun, kt);
}
