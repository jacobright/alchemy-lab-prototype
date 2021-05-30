#ifndef ITEM_H
#define ITEM_H

#include "ingredients.h"

class Item {
    private:
        Ingredient ingredientItem;
        int amount;

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

        void decrementAmount(int amt = 1) {
            amount -= amt;
        }

        int getAmount() {
            return amount;
        }

        void incrementAge(int days = 1) {
            this->ingredientItem.age += days;
        }

        void addModifierToItem(Modifier newModifier) {
            ingredientItem.modifiers.push_back(newModifier);
        }

        void removeModifierFromItem(Modifier oldModifier) {
            for (int i = 0; i < ingredientItem.modifiers.size(); i++) {
                if (ingredientItem.modifiers[i] == oldModifier)
                    ingredientItem.modifiers.erase(ingredientItem.modifiers.begin()+i);
            }
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