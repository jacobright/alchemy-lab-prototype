#ifndef BAG_H
#define BAG_H

#define NUM_INVENTORY_SLOTS 10

#include <string>
#include "item.h"
#include "ingredients.h"

class Bag {
    private:
        Item items[NUM_INVENTORY_SLOTS];

    public:
        Bag() 
        {
            for(int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                items[i] = Item(NULL_INGREDIENT, 0);
            }
        }
        
        // returns the item at the slot at index
        Item* getItem(int index) {
            if (index >= NUM_INVENTORY_SLOTS || index < 0)
                return nullptr;
            
            return &items[index];
        }

        // puts an item in a specific slot, replacing whatever was there 
        void addItemToSlot(Ingredients itemType, int index, int amount = 1) {
            if (index >= NUM_INVENTORY_SLOTS || index < 0)
                return;
            
            items[index] = Item(itemType, amount);
        }

        void moveItem(int fromSlot, int toSlot) {
            if (fromSlot >= NUM_INVENTORY_SLOTS || fromSlot < 0 || toSlot >= NUM_INVENTORY_SLOTS || toSlot < 0)
                return;

            Item tempItem = items[toSlot];

            if (items[toSlot].getIngredient().matchesExactly(items[fromSlot].getIngredient())) {
                items[toSlot].setAmount(items[toSlot].getAmount() + items[fromSlot].getAmount());
                removeItem(fromSlot);
                return;
            }

            items[toSlot] = items[fromSlot];
            items[fromSlot] = tempItem;
        }

        void moveItem(int fromSlot, int toSlot, int amt) {
            if (fromSlot >= NUM_INVENTORY_SLOTS || fromSlot < 0 || toSlot >= NUM_INVENTORY_SLOTS || toSlot < 0 || amt <= 0 || amt > items[fromSlot].getAmount())
                return;

            if (items[toSlot].getIngredient().matchesExactly(items[fromSlot].getIngredient())) {
                items[toSlot].setAmount(amt+items[fromSlot].getAmount());
                items[fromSlot].setAmount(items[fromSlot].getAmount()-amt);
                return;
            }

            if (!(items[toSlot].getIngredient() == IngredientsTable[NULL_INGREDIENT]))
                return;

            items[toSlot] = items[fromSlot];

            items[toSlot].setAmount(amt);
            items[fromSlot].setAmount(items[fromSlot].getAmount()-amt);
        }


        // gives an amount of items in the first available slot of the bag
        void giveItem(Ingredients itemType, int amount = 1) {
            for(int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                if (items[i].getIngredient() == IngredientsTable[itemType]) {
                    items[i].setAmount(amount + items[i].getAmount());
                    return;
                }
            }
            for (int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                if (items[i].getIngredient() == IngredientsTable[NULL_INGREDIENT]) {
                    items[i] = Item(itemType, amount);
                    return;
                }
            }
            std::cout << TEXT_YELLOW_BRIGHT << "No open space in inventory" << TEXT_RESET << "\n";
        }

        // removes an item from the slot at index
        void removeItem(int index) {
            if (index >= NUM_INVENTORY_SLOTS || index < 0)
                return;
            
            items[index] = Item(NULL_INGREDIENT, 0);
        }

        // prints out the inventory as a list
        void printInventory() {
            std::cout << "Inventory:\n";
            for (int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                Item* tempItem = getItem(i);

                if (tempItem->getIngredient() == IngredientsTable[NULL_INGREDIENT]) {
                    std::cout << i << ".\n";
                }
                else {
                    std::cout << i << ". ";
                    printIngredientName(tempItem->getIngredient());
                    std::cout << " [x" << tempItem->getAmount() << "]";
                    std::cout << "\n";
                }
            }
            std::cout << "\n";
        }

};

#endif