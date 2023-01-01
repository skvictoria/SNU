#include <map>
#include <iostream>
#include <vector>
#include "SupplyRunner.hpp"
/**
 * @brief Gets Ingredients from the Storeroom.
 */
 /**
  * @brief The Storeroom associated with the SupplyRunner.
  */
using namespace std;
SupplyRunner::SupplyRunner(Storeroom& storeroom_) :storeroom(storeroom_) {}
std::vector<Ingredient> SupplyRunner::get_ingredients(IngredientMap ingredients) {
    int check = 1;
    auto it_ing = ingredients.begin();
    auto it_stor = storeroom.begin();

    //Checks there's enough ingredients b4 taking
    for (int i = 0; (ingredients.size() > i); i++) {
        if (storeroom.count(it_ing->first)) {
            if (storeroom.at(it_ing->first) >= (it_ing->second)) {
                //check = 1;
            }
            else {
                throw "Not enough ingredients";
                check = 0;
            }
        }
        else {
            throw "Ingredient not in the storeroom";
            check = 0;
        }
        it_ing++;
    }

    std::vector<Ingredient> arr;

    //If enuf ingredients, will now remove them
    if (check) {
        //Removes items from storeroom by creating a new element to map and
        //erasing the old one
        it_ing = ingredients.begin();
        for (int c = 0; ingredients.size() > c; c++) {
            int temp_val = (storeroom.at(it_ing->first));
            cout << "Temp_Val B4 = " << temp_val << endl;
            temp_val = temp_val - (it_ing->second);

            cout << "Temp_val after = " << temp_val << endl;

            (storeroom.at(it_ing->first)) = temp_val;
            //Adds ingredients to vector
            for (int i = 0; i < it_ing->second; i++) {
                arr.push_back(it_ing->first);
            }
            it_ing++;

        }

        return arr;
    }
    else {
        //return nothing;
    }
}
