#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#define NUM_INGREDIENTS 39
#define NUM_CATEGORIES 9
#define NUM_MODIFIERS 29

#include <string>
#include "colorconstants.h"

// list of ingredients, for ease of accesibility
enum Ingredients {
    NULL_INGREDIENT,
    FRESH_WATER,
    SALT_WATER,
    HOLY_WATER,
    ROSE_WATER,

    ROCK_SALT,
    SEA_SALT,
    SUGAR,
    PEPPERCORN,

    AMETHYST,
    DIAMOND,
    AMBER,
    QUARTZ,
    
    GARLIC,
    ROSE,
    ROSE_PETALS,
    ROSE_THORNS,
    LAVENDER,
    BLACKTHORN,
    GRAPES,
    GRAPE_JUICE,
    ASH,

    HONEY,
    CRYSTALLIZED_HONEY,
    WINE,
    MEAD,
    FAIRY_MEAD,
    
    QUICKSILVER,
    GOLD,
    SILVER,
    IRON,
    LEAD,
    COPPER,
    STEEL,
    RUST,
    
    DRAGON_FIRE,
    FAIRY_DUST,
    FAIRY_HONEY,
    FIRE_SALT,
};

// general categories for each ingredient
enum Category {
    NULL_CATEGORY,
    MINERALS,
    METALS,
    ANIMALS,
    ANIMALS_MYTHICAL,
    PLANTS,
    WATERS,
    ARCANE,
    SPICES
};

// specific modifiers for each ingredient
enum Modifier {
    NULL_MODIFIER,
    LIQUID,
    GAS,
    CRUSHED,
    POWDERED,
    DRIED,
    WARMED,
    HEATED,
    BURNT,
    COOLED,
    COLD,
    FROZEN,
    CURSED,
    BLESSED,
    AGED,
    SPOILED,
    FERMENTED,
    SALTED,
    SWEETENED,
    HONEYED,
    SPICY, // potentially unnecessary
    DIRTY,
    POISONED, // potentially unnecessary
    TARNISHED,
    RUSTED,
    WET,
    DRACONIC, // potentially unnecessary
    FAIRY, // potentially unnecessary
    MANMADE, // potentially unnecessary
};

const std::string PrefixTable[] {
    "Null ",
    "Liquid ",
    "Gaseous ",
    "Crushed ",
    "Powdered ",
    "Dried ",
    "Warm",
    "Hot ",
    "Burnt ",
    "Cool ",
    "Cold ",
    "Frozen ",
    "Cursed ",
    "Blessed ",
    "Aged ",
    "Spoiled ",
    "Fermented ",
    "Salted ",
    "Sweetened ",
    "Honeyed ",
    "Spicy ",
    "Dirty ",
    "Poisonous ",
    "Tarnished ",
    "Rusted ",
    "Wet ",
    "Draconic ",
    "Faerie ",
    "Man-Made "
};

// contains all information that such an item would contain
struct Ingredient {
    std::string name;
    std::string desc;
    std::string color;
    Category category;
    std::vector<Modifier> modifiers;
    int age;

    bool operator==(const Ingredient &i) const {
        return i.name == name;
    }

    // checks to see if the ingredient has the modifier
    bool hasModifier(Modifier m) {
        return std::find(modifiers.begin(), modifiers.end(), m) != modifiers.end();
    }

    // stronger than operator==, returns true if ALL aspects of the ingredient are the same, not just the type
    bool matchesExactly(Ingredient i) {
        bool nameMatches = (name == i.name);
        bool categoryMatches = (category == i.category);
        bool modifiersMatch = true;
        
        for(Modifier m : i.modifiers) {
            if (!hasModifier(m))
                modifiersMatch = false;
        }
        for(Modifier m : modifiers) {
            if (!i.hasModifier(m))
                modifiersMatch = false;
        }

        return nameMatches && categoryMatches && modifiersMatch;
    }
};

// the table of ingredients and their definitions
const Ingredient IngredientsTable[] = {
    [NULL_INGREDIENT] = {
        .name = "Null",
        .desc = "Null ingredient",
        .color = TEXT_WHITE,
        .category = NULL_CATEGORY,
        .modifiers = {NULL_MODIFIER},
        .age = 0,
    },

    [FRESH_WATER] =
    {
        .name = "Fresh Water",
        .desc = "Fresh, drinkable water",
        .color = TEXT_BLUE_BRIGHT,
        .category = WATERS,
        .modifiers = {LIQUID},
        .age = 0,
    },
    
    [SALT_WATER] =
    {
        .name = "Salt Water",
        .desc = "Salty water, like from the sea",
        .color = TEXT_BLUE_BRIGHT,
        .category = WATERS,
        .modifiers = {LIQUID, SALTED},
        .age = 0,
    },
    
    [HOLY_WATER] =
    {
        .name = "Holy Water",
        .desc = "Water that has been blessed",
        .color = TEXT_BLUE_BRIGHT,
        .category = WATERS,
        .modifiers = {LIQUID, BLESSED},
        .age = 0,
    },
    
    [ROSE_WATER] =
    {
        .name = "Rose Water",
        .desc = "Rose petals steeped in water",
        .color = TEXT_MAGENTA,
        .category = WATERS,
        .modifiers = {LIQUID},
        .age = 0,
    },

    [ROCK_SALT] = 
    {
        .name = "Rock Salt",
        .desc = "A salt crystal",
        .color = TEXT_WHITE_BRIGHT,
        .category = MINERALS,
        .modifiers = {SALTED},
        .age = 0,
    },

    [SEA_SALT] = 
    {
        .name = "Sea Salt",
        .desc = "Salt from the sea",
        .color = TEXT_WHITE_BRIGHT,
        .category = MINERALS,
        .modifiers = {SALTED, CRUSHED},
        .age = 0,
    },

    [SUGAR] = 
    {
        .name = "Sugar",
        .desc = "As sweet as can be",
        .color = TEXT_WHITE_BRIGHT,
        .category = SPICES,
        .modifiers = {SWEETENED, POWDERED},
        .age = 0,
    },

    [PEPPERCORN] = 
    {
        .name = "Peppercorn",
        .desc = "A somewhat spicy peppercorn",
        .color = TEXT_GREEN,
        .category = SPICES,
        .modifiers = {SPICY},
        .age = 0,
    },

    [AMETHYST] = 
    {
        .name = "Amethyst",
        .desc = "A shiny, purple gemstone",
        .color = TEXT_MAGENTA_BRIGHT,
        .category = MINERALS,
        .modifiers = {},
        .age = 0,
    },

    [DIAMOND] = 
    {
        .name = "Diamond",
        .desc = "A rare, tough gemstone",
        .color = TEXT_CYAN_BRIGHT,
        .category = MINERALS,
        .modifiers = {},
        .age = 0,
    },

    [AMBER] = 
    {
        .name = "Amber",
        .desc = "Ancient, hardened tree sap",
        .color = TEXT_YELLOW_BRIGHT,
        .category = MINERALS,
        .modifiers = {},
        .age = 0,
    },

    [QUARTZ] = 
    {
        .name = "Quartz",
        .desc = "A common gemstone",
        .color = TEXT_WHITE_BRIGHT,
        .category = MINERALS,
        .modifiers = {},
        .age = 0,
    },

    [GARLIC] = 
    {
        .name = "Garlic",
        .desc = "Pungent, yet delicious",
        .color = TEXT_GREEN,
        .category = PLANTS,
        .modifiers = {SPICY},
        .age = 0,
    },

    [ROSE] = 
    {
        .name = "Rose",
        .desc = "A rose",
        .color = TEXT_RED_BRIGHT,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [ROSE_PETALS] = 
    {
        .name = "Rose Petals",
        .desc = "Delicate and aromatic",
        .color = TEXT_RED_BRIGHT,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [ROSE_THORNS] = 
    {
        .name = "Rose Thorns",
        .desc = "Small sharp thorns from a rose",
        .color = TEXT_RED_BRIGHT,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [LAVENDER] = 
    {
        .name = "Lavender",
        .desc = "Has a strong, soothing fragrance",
        .color = TEXT_MAGENTA_BRIGHT,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [BLACKTHORN] = 
    {
        .name = "Blackthorn",
        .desc = "A rough, thorny branch",
        .color = TEXT_YELLOW,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [GRAPES] = 
    {
        .name = "Grapes",
        .desc = "A cluster of grapes",
        .color = TEXT_RED,
        .category = PLANTS,
        .modifiers = {},
        .age = 0,
    },

    [GRAPE_JUICE] = 
    {
        .name = "Grape Juice",
        .desc = "Sweet, purple grape juice",
        .color = TEXT_RED,
        .category = PLANTS,
        .modifiers = {LIQUID},
        .age = 0,
    },

    [ASH] = 
    {
        .name = "Ash",
        .desc = "The remains of what once was",
        .color = TEXT_BLACK_BRIGHT,
        .category = PLANTS,
        .modifiers = {POWDERED},
        .age = 0,
    },

    [HONEY] = 
    {
        .name = "Honey",
        .desc = "Sweet and sticky",
        .color = TEXT_YELLOW_BRIGHT,
        .category = ANIMALS,
        .modifiers = {LIQUID, SWEETENED, HONEYED},
        .age = 0,
    },

    [CRYSTALLIZED_HONEY] = 
    {
        .name = "Crystallized Honey",
        .desc = "Hardened honey",
        .color = TEXT_YELLOW_BRIGHT,
        .category = ANIMALS,
        .modifiers = {SWEETENED, HONEYED},
        .age = 0,
    },

    [WINE] = 
    {
        .name = "Wine",
        .desc = "A deep red drink",
        .color = TEXT_RED,
        .category = PLANTS,
        .modifiers = {LIQUID, FERMENTED},
        .age = 0,
    },

    [MEAD] = 
    {
        .name = "Mead",
        .desc = "A sweet, golden drink",
        .color = TEXT_YELLOW_BRIGHT,
        .category = WATERS,
        .modifiers = {LIQUID, FERMENTED, SWEETENED},
        .age = 0,
    },

    [FAIRY_MEAD] = 
    {
        .name = "Faerie Mead",
        .desc = "A saccharine blue drink",
        .color = TEXT_CYAN_BRIGHT,
        .category = ANIMALS_MYTHICAL,
        .modifiers = {FAIRY, LIQUID, SWEETENED, FERMENTED},
        .age = 0,
    },

    [QUICKSILVER] = 
    {
        .name = "Quicksilver",
        .desc = "A mysterious flowing metal",
        .color = TEXT_WHITE_BRIGHT,
        .category = METALS,
        .modifiers = {LIQUID, POISONED},
        .age = 0,
    },

    [GOLD] = 
    {
        .name = "Gold",
        .desc = "A valuable metal that will never tarnish",
        .color = TEXT_YELLOW_BRIGHT,
        .category = METALS,
        .modifiers = {},
        .age = 0,
    },

    [SILVER] = 
    {
        .name = "Silver",
        .desc = "A valuable, lustrous metal",
        .color = TEXT_WHITE_BRIGHT,
        .category = METALS,
        .modifiers = {},
        .age = 0,
    },

    [IRON] = 
    {
        .name = "Iron",
        .desc = "A tough metal feared by faeries",
        .color = TEXT_BLACK_BRIGHT,
        .category = METALS,
        .modifiers = {},
        .age = 0,
    },

    [LEAD] = 
    {
        .name = "Lead",
        .desc = "A heavy metal which tastes sweet",
        .color = TEXT_WHITE,
        .category = METALS,
        .modifiers = {SWEETENED, POISONED},
        .age = 0,
    },

    [COPPER] = 
    {
        .name = "Copper",
        .desc = "A shining orange metal",
        .color = TEXT_YELLOW,
        .category = METALS,
        .modifiers = {},
        .age = 0,
    },

    [STEEL] = 
    {
        .name = "Steel",
        .desc = "A sturdy iron alloy",
        .color = TEXT_WHITE,
        .category = METALS,
        .modifiers = {MANMADE},
        .age = 0,
    },

    [RUST] = 
    {
        .name = "Rust",
        .desc = "Iron tarnished beyond repair",
        .color = TEXT_RED,
        .category = METALS,
        .modifiers = {RUSTED},
        .age = 0,
    },

    [DRAGON_FIRE] = 
    {
        .name = "Dragon's Fire",
        .desc = "A mystical flame that never dies out",
        .color = TEXT_RED_BRIGHT,
        .category = ARCANE,
        .modifiers = {DRACONIC, HEATED},
        .age = 0,
    },

    [FAIRY_DUST] = 
    {
        .name = "Faerie Dust",
        .desc = "Discarded scales from faerie wings",
        .color = TEXT_CYAN_BRIGHT,
        .category = ANIMALS_MYTHICAL,
        .modifiers = {FAIRY, POWDERED},
        .age = 0,
    },

    [FAIRY_HONEY] = 
    {
        .name = "Faerie Honey",
        .desc = "A glowing blue honey, almost too sweet to eat",
        .color = TEXT_CYAN_BRIGHT,
        .category = ANIMALS_MYTHICAL,
        .modifiers = {FAIRY, SWEETENED, LIQUID, HONEYED},
        .age = 0,
    },

    [FIRE_SALT] = 
    {
        .name = "Fire Salt",
        .desc = "An extraordinarily hot and spicy red salt",
        .color = TEXT_RED_BRIGHT,
        .category = MINERALS,
        .modifiers = {SALTED, SPICY, CRUSHED, HEATED},
        .age = 0,
    },
};

// prints the ingredient name using the color, as well as the description
void printIngredientInfo(Ingredients i) {
    std::cout << IngredientsTable[i].color << IngredientsTable[i].name << TEXT_RESET << ": ";
    std::cout << IngredientsTable[i].desc;
}
void printIngredientInfo(Ingredient i) {
    std::cout << i.color << i.name << TEXT_RESET << ": ";
    std::cout << i.desc;
}

// prints the full ingredient name, in color, and with unique (non-default) prefix descriptors
void printIngredientName(Ingredient i) {

    Ingredient tableIngredient;

    for (int j = 0; j < NUM_INGREDIENTS; j++) {
        if (IngredientsTable[(Ingredients)j] == i) {
            tableIngredient = IngredientsTable[(Ingredients)j];
        }
    }

    for (Modifier m : i.modifiers) {
        if (!tableIngredient.hasModifier(m))
            std::cout << PrefixTable[m];
    }

    std::cout << i.color << i.name << TEXT_RESET;
}


#endif