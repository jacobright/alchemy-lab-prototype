#include <iostream>
#include <sstream>
#include <vector>
#include <string>
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

std::vector<Ingredient> getIngredientSelection() {
    inventory.printInventory();
    std::cout << "Select bag slots: ";
    std::string selection;
    getline(std::cin, selection);
    std::vector<std::string> stringSelection = tokenize(selection);
    std::vector<Ingredient> bagSelection;

    for (std::string stringSel : stringSelection) {
        bagSelection.push_back(IngredientsTable[stoi(stringSel)]);
    }

    return bagSelection;
}

int brewHandler() {
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
            std::cout << "TECHNICAL COMMANDS: help, back, bag\n";
        }
        else if (brewCmd[0] == "bag") { 
            inventory.printInventory();
        }

    }

    std::cout << "Exiting Brewing...\n";
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
        std::cout << "COMMANDS:\nTERMINAL: exit, info, help \nINVENTORY: bag, give, mod, move\nPOTIONS: brew\n";
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

    // brew
    else if (command[0] == "brew") {
        std::cout << "Entering Brewing Mode\n";
        brewHandler();
    }
        
    // separate
    else if (command[0] == "separate") {
        std::vector<Ingredient> sel = getIngredientSelection();
        getMatchingRecipe(sel, SEPARATE);
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
                        inventory.addItemToSlot((Ingredients)transformationResult, i, inventory.getItem(i)->getAmount()); 
                    }
                }

                // clears the item if amount is 0 (or less)
                if (inventory.getItem(i)->getAmount() <= 0) {
                    inventory.removeItem(i);
                }
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