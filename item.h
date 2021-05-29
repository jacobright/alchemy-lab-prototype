#ifndef ITEM_H
#define ITEM_H

#include "ingredients.h"

class Item {
    private:
        Ingredient ingredientItem;
        int amount;
        int age;
        int temperature;

    public:
        Item() {}

        Item(Ingredient ingredientItem, int amount)
        {
            this->ingredientItem = ingredientItem;
            this->amount = amount;
        }

        Item(Ingredients itemType, int amount)
        {
            this->ingredientItem = IngredientsTable[itemType];
            this->amount = amount;
        }

        void setAmount(int newAmt) {
            amount = newAmt;
        }

        int getAmount() {
            return amount;
        }

        int getAge() {
            return age;
        }

        void incrementAge() {
            ++age;
        }

        void addModifierToItem(Modifier newModifier) {
            ingredientItem.modifiers.push_back(newModifier);
        }

        Ingredient getIngredient() {
            return ingredientItem;
        }

        // checks if this item has a standardized item to match it
        bool matchesStandardItem() {
            for (int i = 0; i < NUM_INGREDIENTS; i++) {
                if (ingredientItem.matchesExactly(IngredientsTable[(Ingredients)i])) {
                    return true;
                }
            }
            return false;
        }
};

#endif