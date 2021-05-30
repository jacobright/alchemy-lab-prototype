#ifndef RECIPES_H
#define RECIPES_H

#define NUM_RECIPES 0
#define NUM_TRANSFORMATIONS 2

// #include <vector>
#include "ingredients.h"

enum Action {
    COMBINE, // adding two or more ingredients together
    SEPARATE, // separate an ingredient into it's base parts
    HEAT, // adding heat to an ingredient
    CHILL, // removing heat from an ingredient
    BREW, // a liquid base, with ingredients, heated (FOR POTIONS / FINAL PRODUCTS)
};


struct Transformation {
    Ingredients inIngredientType;
    Ingredients outIngredientType;
    std::vector<Modifier> modifiers;
    std::vector<Modifier> outModifiers;
    Category category;
    int age;
};

struct Recipe {
    std::vector<Ingredients> inIngredients;
    std::vector<std::vector<Modifier>> inModifiers;
    std::vector<Ingredients> outIngredients;
    std::vector<std::vector<Modifier>> outModifiers;
    Action action;
};

const Transformation TransformationTable[] {
    {FRESH_WATER, SALT_WATER, {SALTED}, {}, WATERS, -1},
    {FRESH_WATER, HOLY_WATER, {BLESSED}, {}, WATERS, -1},
    {FRESH_WATER, MEAD, {HONEYED, FERMENTED}, {}, WATERS, -1},
    {HOLY_WATER, SALT_WATER, {SALTED}, {}, WATERS, -1},

    {HONEY, CRYSTALLIZED_HONEY, {COOLED}, {}, NULL_CATEGORY, -1},
    {HONEY, CRYSTALLIZED_HONEY, {COLD}, {}, NULL_CATEGORY, -1},
    {CRYSTALLIZED_HONEY, HONEY, {HEATED}, {}, NULL_CATEGORY, -1},

    {IRON, IRON, {WET}, {TARNISHED}, METALS, -1},
    {IRON, RUST, {RUSTED}, {}, METALS, -1},
    {COPPER, COPPER, {WET}, {TARNISHED}, METALS, -1},

    {NULL_INGREDIENT, ASH, {BURNT}, {}, PLANTS, -1},

    {GRAPES, GRAPE_JUICE, {CRUSHED}, {}, PLANTS, -1},
    {GRAPE_JUICE, WINE, {}, {}, PLANTS, 21},
    {GRAPE_JUICE, WINE, {FERMENTED}, {}, PLANTS, -1},
};

const Recipe RecipeTable[] {
    {{HONEY, FAIRY_DUST}, {}, 
     {FAIRY_HONEY}, {},
     COMBINE},
    
    {{ROSE, FRESH_WATER}, {}, 
     {ROSE_WATER}, {}, 
     COMBINE},
    
    {{ROSE_PETALS, FRESH_WATER}, {}, 
     {ROSE_WATER}, {}, 
     COMBINE},
    
    {{ROCK_SALT, FRESH_WATER}, {{POWDERED},{}}, 
     {SALT_WATER}, {}, 
     COMBINE},
    
    {{FRESH_WATER, HONEY}, {}, 
     {FRESH_WATER}, {{HONEYED}},
     COMBINE},

    {{ROSE}, {}, 
     {ROSE_PETALS, ROSE_THORNS}, {},
     SEPARATE},
    
};


// returns an integer which corresponds to the output ingredient in the transformation
// returns -1 if no match
int ingredientMatchesTransformation(Ingredient ingredient, Transformation transform) {
    bool nameMatches = ingredient == IngredientsTable[transform.inIngredientType] || transform.inIngredientType == NULL_INGREDIENT;
    bool categoryMatches = ingredient.category == transform.category || transform.category == NULL_CATEGORY;
    bool modifiersMatch = true;
    bool ageMatches = false;

    for (Modifier m : transform.modifiers) {
        if (!ingredient.hasModifier(m))
            modifiersMatch = false;
        
        if (m == NULL_MODIFIER) {
            modifiersMatch = true;
            break;
        }
    }

    if (transform.age == -1 || ingredient.age >= transform.age)
        ageMatches = true;

    return (nameMatches && categoryMatches && modifiersMatch && ageMatches) ? (int)transform.outIngredientType : -1;
}

bool ingredientsContainModifiers(std::vector<Ingredients> recipeInput, std::vector<std::vector<Modifier>> modifiers, std::vector<Ingredient> ingredients) {
    if (modifiers.size() == 0)
        return true;

    for (int i = 0; i < recipeInput.size(); i++) {
        std::vector<Ingredient>::iterator foundIngredient = std::find(ingredients.begin(), ingredients.end(), IngredientsTable[recipeInput[i]]);

        if (foundIngredient != ingredients.end()) {
            for (Modifier m : modifiers[i]) {
                if (!(*foundIngredient).hasModifier(m)) {
                    // std::cout << (*foundIngredient).name << " does not have correct modifier: " << PrefixTable[m] << "\n";
                    return false;
                }
            }
        }
    }

    return true;
}

bool doAllIngredientsMatch(std::vector<Ingredient> i1, std::vector<Ingredient> i2) {
    // check both to make sure they contain ALL of eachother's ingredients
    // std::cout << "recipe ingredients: ";
    for (Ingredient i : i1) {
        // std::cout << i.name << " ";
        if(std::find(i2.begin(), i2.end(), i) == i2.end()) {
            // std::cout << "\n";
            return false;
        }
    }
    // std::cout << "\ninput ingredients: ";
    for (Ingredient i : i2) {
        // std::cout << i.name << " ";
        if(std::find(i1.begin(), i1.end(), i) == i1.end()) {
            // std::cout << "\n";
            return false;
        }
    }
    // std::cout << "\n";

    return true;
}

// returns the output ingredients vector from the matching recipe
std::vector<Ingredients> getMatchingRecipe(std::vector<Ingredient> ingredients, Action action) {

    for (Recipe r : RecipeTable) { // for every recipe
        // convert to Ingredient vector instead of Ingredients vector
        std::vector<Ingredient> recipeIngredients;
        for (Ingredients i : r.inIngredients) {
            recipeIngredients.push_back(IngredientsTable[i]);
        }

        if (r.action == action) { // check if action matches
        // std::cout << "ACTION MATCH\n";
            if (doAllIngredientsMatch(recipeIngredients, ingredients)) { // check if ingredient types match
                // std::cout << "INGREDIENT MATCH\n";
                // check if modifiers exist in the  match
                if (ingredientsContainModifiers(r.inIngredients, r.inModifiers, ingredients)) {
                    // std::cout << "MODIFIER MATCH\n";
                    return r.outIngredients;
                }
            }
        }
    }

    return std::vector<Ingredients>{};
}




#endif