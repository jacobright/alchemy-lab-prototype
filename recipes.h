#ifndef RECIPES_H
#define RECIPES_H

#define NUM_RECIPES 0
#define NUM_TRANSFORMATIONS 2

// #include <vector>
#include "ingredients.h"

enum Action {
    COMBINE, // adding two or more ingredients together
    HEAT, // adding heat to an ingredient
    CHILL, // removing heat from an ingredient
    SEPARATE, // separate an ingredient into it's base parts
    BREW, // a liquid base, with ingredients, heated (FOR POTIONS / FINAL PRODUCTS)
};

struct Recipe {
    std::vector<Ingredients> inIngredients;
    std::vector<std::vector<Modifier>> inModifiers;
    std::vector<Ingredients> outIngredients;
    Action action;
};

const Recipe RecipeTable[] {
    {{HONEY, FAIRY_DUST}, {}, {FAIRY_HONEY}, COMBINE},
    {{ROSE}, {}, {ROSE_PETALS, ROSE_THORNS}, SEPARATE},
    {{HONEY, FRESH_WATER}, {{FERMENTED}}, {MEAD}, COMBINE},
};

struct Transformation {
    Ingredients inIngredientType;
    Ingredients outIngredientType;
    Category category;
    std::vector<Modifier> modifiers;
};

const Transformation TransformationTable[] {
    {FRESH_WATER, SALT_WATER, WATERS, {SALTED}},
    {HOLY_WATER, SALT_WATER, WATERS, {SALTED}},
    {FRESH_WATER, HOLY_WATER, WATERS, {BLESSED}},
    {HONEY, CRYSTALLIZED_HONEY, NULL_CATEGORY, {COOLED}},
    {HONEY, CRYSTALLIZED_HONEY, NULL_CATEGORY, {COLD}},
    {IRON, RUST, METALS, {RUSTED}},
    {NULL_INGREDIENT, ASH, PLANTS, {BURNT}},
};

// returns an integer which corresponds to the output ingredient in the transformation
// returns -1 if no match
int ingredientMatchesTransformation(Ingredient ingredient, Transformation transform) {
    bool nameMatches = ingredient == IngredientsTable[transform.inIngredientType] || transform.inIngredientType == NULL_INGREDIENT;
    bool categoryMatches = ingredient.category == transform.category || transform.category == NULL_CATEGORY;
    bool modifiersMatch = true;

    for (Modifier m : transform.modifiers) {
        if (!ingredient.hasModifier(m))
            modifiersMatch = false;
        
        if (m == NULL_MODIFIER) {
            modifiersMatch = true;
            break;
        }
    }

    return (nameMatches && categoryMatches && modifiersMatch) ? (int)transform.outIngredientType : -1;
}

bool doAllIngredientsMatch(std::vector<Ingredient> i1, std::vector<Ingredient> i2) {
    // check both to make sure they contain ALL of eachother's ingredients
    for (Ingredient i : i1) {
        if(std::find(i2.begin(), i2.end(), i) == i2.end()) {
            return false;
        }
    }
    for (Ingredient i : i2) {
        if(std::find(i1.begin(), i1.end(), i) == i1.end()) {
            return false;
        }
    }

    return true;
}

// returns the output ingredients vector from the matching recipe
std::vector<Ingredients> getMatchingRecipe(std::vector<Ingredient> ingredients, Action action) {
    bool inIngredientsMatch = false;
    bool inModifiersMatch = false;
    bool actionMatches = false;


    for (Recipe r : RecipeTable) { // for every recipe
        // convert to Ingredient vector instead of Ingredients vector
        std::vector<Ingredient> recipeIngredients;
        for (Ingredients i : r.inIngredients) {
            recipeIngredients.push_back(IngredientsTable[i]);
        }

        if (r.action == action) { // check if action matches
            if (doAllIngredientsMatch(recipeIngredients, ingredients)) { // check if ingredient types match
                // check if modifiers exist in the  match
            }
        }
    }

    return (inIngredientsMatch && inModifiersMatch && actionMatches) ? RecipeTable[0].outIngredients : std::vector<Ingredients>{NULL_INGREDIENT};
}




#endif