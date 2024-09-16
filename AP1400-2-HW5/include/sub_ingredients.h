#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#define DEFCLASS(Ingredient_name, Ingredient_units) \
class Ingredient_name: public Ingredient { \
public: \
    Ingredient_name(size_t units): Ingredient{Ingredient_units, units} { \
        name = #Ingredient_name; \
    } \
    std::string get_name() override { \
        return name; \
    } \
    Ingredient* clone() override { \
        return new Ingredient_name(units); \
    } \
}; 

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);


#endif // SUB_INGREDIENTS_H