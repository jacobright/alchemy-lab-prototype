#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include "ingredients.h"
#include "recipes.h"
#include "colorconstants.h"
#include "bag.h"

Bag inventory;

// returns the input as a vector of strings
std::vector<std::string> tokenize(std::string input) {
    std::vector<std::string> tokens;
    std::stringstream stream(input);
    std::string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// prints out the proper usage of a command after improper usage
void printCommandError(std::string cmd, std::string properCmd) {
    std::cout << TEXT_YELLOW_BRIGHT << "Improper Usage of Command: " << cmd << "\nProper Usage: " << properCmd << TEXT_RESET << "\n";
}

std::vector<int> getIngredientSelection() {
    inventory.printInventory();
    std::cout << "Select bag slots: ";
    std::string selection;
    getline(std::cin, selection);
    std::vector<std::string> stringSelection = tokenize(selection);
    std::vector<int> bagSelection;

    for (std::string stringSel : stringSelection) {
        // bagSelection.push_back(inventory.getItem(stoi(stringSel))->getIngredient());
        bagSelection.push_back(stoi(stringSel));
    }

    return bagSelection;
}

bool doCraft(Action action, std::string actionDescriptor) {
    
    // TURN THIS INTO ACTION FUNCTION
    std::vector<int> indexSel = getIngredientSelection();
    std::vector<Ingredient> sel;

    for (int val : indexSel) {
        sel.push_back(inventory.getItem(val)->getIngredient());
    }

    std::vector<Ingredients> ingredientsToGive = getMatchingRecipe(sel, action);

    // give the result if found valid recipe
    if (ingredientsToGive.size() > 0) {
        std::cout << TEXT_GREEN_BRIGHT << actionDescriptor << " " << TEXT_RESET;

        int amtResult = INT_MAX;
        for (int i : indexSel) {
            printIngredientName(inventory.getItem(i)->getIngredient());
            std::cout << " [x" << inventory.getItem(i)->getAmount() << "] ";

            amtResult = std::min(amtResult, inventory.getItem(i)->getAmount());
            inventory.getItem(i)->decrementAmount();
            if (inventory.getItem(i)->getAmount() <= 0)
                inventory.removeItem(i);
        }

        std::cout << TEXT_GREEN_BRIGHT << "into:\n" << TEXT_RESET;

        for (Ingredients i : ingredientsToGive) {
            printIngredientName(IngredientsTable[i]);
            std::cout << "\n";
            inventory.giveItem(i, amtResult);
        }
        std::cout << "\n";
    }
    else {
        std::cout << TEXT_RED_BRIGHT << actionDescriptor << " FAILED: " << TEXT_RESET;
        for (Ingredient i : sel) {
            printIngredientName(i);
            std::cout << " ";
        }
        std::cout << "\n";
        return false;
    }

    return true;
}

int craftHandler() {
    std::string brewInput;
    while(true) {
        // the command input loop
        std::cout << "~ ";
        getline(std::cin, brewInput);
        std::vector<std::string> brewCmd = tokenize(brewInput);

        if (brewCmd.size() == 0)
            continue;

        if (brewCmd[0] == "back" || brewCmd[0] == "exit" || brewCmd[0] == "x")
            break;
        else if (brewCmd[0] == "help") {
            std::cout << "TECHNICAL COMMANDS: help, back, bag\nCRAFTING COMMANDS: separate, combine\n";
        }
        else if (brewCmd[0] == "bag") { 
            inventory.printInventory();
        }
        
        // separate
        else if (brewCmd[0] == "separate") {
            doCraft(SEPARATE, "SEPARATED");
        }

        // combine
        else if (brewCmd[0] == "combine") {
            doCraft(COMBINE, "COMBINED");
        }

        // heat
        // else if (brewCmd[0] == "heat") {
        //     doCraft(HEAT, "HEATED");
        // }

    }

    std::cout << "Exiting Crafting...\n";
    return 0;
}

// returns a command code
int commandHandler(std::string rawInput) {
    if (rawInput.empty())
        return 0;

    std::vector<std::string> command = tokenize(rawInput);

    // exit
    if (command[0] == "exit" || command[0] == "x") { // exit
        return -1;
    }

    // help
    else if (command[0] == "help") {
        std::cout << "COMMANDS:\nTERMINAL: exit, info, help \nINVENTORY: bag, give, mod, move\nCRAFTING & BREWING: craft, brew\n";
    }
    
    // info {item/mod/all}
    else if (command[0] == "info") {
        if (command.size() != 2) {
            printCommandError(rawInput, "info {item/mod/all}");
        }
        else {
            // print all item types
            if (command[1] == "item" || command[1] == "all") {
                std::cout << "ITEM LIST:\n";
                for (int i = 1; i < NUM_INGREDIENTS; i++) {    
                    std::cout << "[" << i << "] ";
                    printIngredientInfo((Ingredients)i);
                    std::cout << "\n";
                }
                std::cout << "\n";
            }
            // print all modification types
            if (command[1] == "mod" || command[1] == "all") {
                std::cout << "MODIFIER LIST:\n";
                for (int i = 1; i < NUM_MODIFIERS; i++) {
                    std::cout << "[" << i << "] " << PrefixTable[(Modifier)i] << "\n";
                }
                std::cout << "\n";
            }

        }
    }
    
    // bag
    else if (command[0] == "bag") { 
        inventory.printInventory();
    }

    // give [ID] [AMOUNT]
    else if (command[0] == "give") {
        if (command.size() != 3) {
            printCommandError(rawInput, "give [ID] [AMT]");
        }
        else {
            inventory.giveItem((Ingredients)std::stoi(command[1]),std::stoi(command[2])); // TODO: type checking on command inputs
        }
    }

    // mod [SLOT] [MODIFIER] 
    else if (command[0] == "mod") { 
        if (command.size() != 3) {
            printCommandError(rawInput, "mod [SLOT] [MODIFIER]");
        }
        else {
            inventory.getItem(std::stoi(command[1]))->addModifierToItem((Modifier)std::stoi(command[2]));
        }
    }

    // move [FROM SLOT] [TO SLOT]
    else if (command[0] == "move") { 
        if (command.size() < 3) {
            printCommandError(rawInput, "move [FROM SLOT] [TO SLOT]");
        }
        else if (command.size() > 4) {
            printCommandError(rawInput, "move [FROM SLOT] [TO SLOT] [AMT]");
        }
        else {
            if (command.size() == 3)
                inventory.moveItem(std::stoi(command[1]), std::stoi(command[2])); // TODO: type checking on command inputs
            else
                inventory.moveItem(std::stoi(command[1]), std::stoi(command[2]), std::stoi(command[3])); // TODO: type checking on command inputs
        }
    }

    // craft
    else if (command[0] == "craft") {
        std::cout << "Entering Crafting Mode\n";
        craftHandler();
    }

    // brew (this is specifically for potions)
    else if (command[0] == "brew") {
        std::cout << "Feature incomplete\n";
    }

    // BELOW ARE THE ACTUAL MODIFICATION COMMANDS (wait, crush, heat, cool, curse, bless, )
    // SALTING, SWEETENING, HONEYING, and WETTENING will all happen in crafting (COMBINE) 
    // wait
    else if (command[0] == "wait") {
        if (command.size() == 1 || command[1] == "1") {
            std::cout << "- Waiting 1 Day -\n";
            for(int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                inventory.getItem(i)->incrementAge();
            }
        }
        else if (command.size() == 2) {
            std::cout << "- Waiting " << command[1] << " Days -\n";
            for(int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
                inventory.getItem(i)->incrementAge(std::stoi(command[1]));
            }
        }
        else
            printCommandError(rawInput, "wait [DAYS]");
    }
    // crush
    else if (command[0] == "crush") {
        if (command.size() != 2) {
            printCommandError(rawInput, "crush [SLOT]");
        }
        else {
            Item* item = inventory.getItem(std::stoi(command[1]));

            if (!item->getIngredient().hasModifier(LIQUID) && 
                !item->getIngredient().hasModifier(POWDERED)) {

                std::cout << "Crushing "; printIngredientName(item->getIngredient()); std::cout << "\n";
                if (item->getIngredient().hasModifier(CRUSHED)) {
                    item->removeModifierFromItem(CRUSHED);
                    item->addModifierToItem(POWDERED);
                }
                else {
                    item->addModifierToItem(CRUSHED);
                }
            }
            else {
                std::cout << TEXT_RED_BRIGHT << "You can't crush that." << TEXT_RESET << "\n";
            }
        }
    }

    // error
    else if (command.size() > 0) {
        std::cout << TEXT_YELLOW_BRIGHT << "Invalid Command: " << rawInput << TEXT_RESET << "\n";
    }

    return 0;
}

int main () {
    std::cout << "---------------------\nAlchemy Lab Prototype\n---------------------\n\n";

    inventory.addItemToSlot(FRESH_WATER, 0, 3); // adds 3 fresh water items to slot 0
    inventory.addItemToSlot(HOLY_WATER, 5, 1); // adds 1 holy water item to slot 5
    inventory.addItemToSlot(FRESH_WATER, 1, 1); // adds 1 fresh water item to slot 1
    inventory.getItem(1)->addModifierToItem(SALTED); // modifies the fresh water item to be salted, so it turns into salt water
    inventory.giveItem(HONEY,1); // gives 1 honey in first open slot
    inventory.addItemToSlot(FRESH_WATER, 3, 1); // gives 1 honey in first open slot
    inventory.giveItem(ROSE,2);

    std::string commandInput;
    while(true) {
        
        // the item transformation loop
        for (int i = 0; i < NUM_INVENTORY_SLOTS; i++) {
            if (!(inventory.getItem(i)->getIngredient() == IngredientsTable[NULL_INGREDIENT])) {
                
                // check the transformations to see if this item should undergo one
                for(Transformation t : TransformationTable) {
                    int transformationResult = ingredientMatchesTransformation(inventory.getItem(i)->getIngredient(), t);
                    if (transformationResult >= 0) { // if a successful transformation is found
                        // update item i to the output item from the transformation
                        if (transformationResult > 0)
                            inventory.addItemToSlot((Ingredients)transformationResult, i, inventory.getItem(i)->getAmount());

                        for (Modifier m : t.outModifiers) {
                            inventory.getItem(i)->addModifierToItem(m);
                        }
                    }
                }

                // clears the item if amount is 0 (or less)
                if (inventory.getItem(i)->getAmount() <= 0) {
                    inventory.removeItem(i);
                }

                // if (inventory.getItem(i)->getIngredient().age)
            }
        }
        
        // the command input loop
        std::cout << "> ";
        getline(std::cin, commandInput);
        int cmdResult = commandHandler(commandInput);

        if (cmdResult == -1) {
            break;
        }
    }
    std::cout << "Exiting Alchemy Lab...\n";
}