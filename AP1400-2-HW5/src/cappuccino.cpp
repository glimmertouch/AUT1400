#include <vector>
#include <iostream>
#include "ingredient.h"
#include "sub_ingredients.h"
#include "espresso_based.h"
#include "cappuccino.h"

Cappuccino::Cappuccino() {
    name = "Cappuccino";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino &cap) : EspressoBased(cap) {
    for (auto const& i : cap.side_items) {
        side_items.push_back(i->clone());
    }
}

Cappuccino::~Cappuccino() {
    for(const auto& i : side_items) {
        delete i;
    }
    side_items.clear();    
}

void Cappuccino::operator=(const Cappuccino &cap) {
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

double Cappuccino::price()
{
    double p = EspressoBased::price();
    for (const auto& i : side_items) {
        p += i->get_units() * i->get_price_unit();
        //std::cout << i->get_name() << ": " << i->get_units() << 
        //    " * "<< i->get_price_unit() << std::endl;
    }
    return p;
}

void Cappuccino::add_side_item(Ingredient *side)
{
    side_items.push_back(side);
}

std::vector<Ingredient *> &Cappuccino::get_side_items()
{
    return side_items;
}
