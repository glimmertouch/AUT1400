#include <vector>
#include <iostream>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "mocha.h"

Mocha::Mocha() {
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha &cap) : EspressoBased(cap) {
    for (auto const& i : cap.side_items) {
        side_items.push_back(i->clone());
    }
}

Mocha::~Mocha() {
    for(const auto& i : side_items)
        delete i;
    side_items.clear();    
}

void Mocha::operator=(const Mocha &cap) {
    if (this != &cap) {
        for(const auto& i : side_items) {
            delete i;
        }
        side_items.clear(); 
        EspressoBased::operator=(cap);
        for (auto const& i : cap.side_items) {
            side_items.push_back(i->clone());
        }
    }
}

double Mocha::price()
{
    double p = EspressoBased::price();
    for (const auto& i : side_items) {
        p += i->get_units() * i->get_price_unit();
    }
    return p;
}

void Mocha::add_side_item(Ingredient *side)
{
    side_items.push_back(side);
}

std::vector<Ingredient *> &Mocha::get_side_items()
{
    return side_items;
}
