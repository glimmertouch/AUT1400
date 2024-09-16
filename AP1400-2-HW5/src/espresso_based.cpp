#include <iostream>
#include <vector>
#include "ingredient.h"
#include "espresso_based.h"

std::string EspressoBased::get_name()
{
    return name;
}

double EspressoBased::price()
{
    double p = 0.0;
    for(const auto& i : ingredients) {
        p += i->get_units() * i->get_price_unit();
        //std::cout << i->get_name() << ": " << i->get_units() << 
        //            " * "<< i->get_price_unit() << std::endl;
    }
    return p;
}

void EspressoBased::brew()
{
    for(const auto& i : ingredients) {
        std::cout << i->get_name() << ": " << i->get_units() << std::endl;
    }
}

std::vector<Ingredient *> &EspressoBased::get_ingredients()
{
    return ingredients;
}

EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients) {
        delete i;
    }
    ingredients.clear();
}

EspressoBased::EspressoBased(const EspressoBased &esp): name(esp.name)
{
    for(auto const& i : esp.ingredients) {
        ingredients.push_back(i->clone());
    } 
}

void EspressoBased::operator=(const EspressoBased &esp)
{
    if (this != &esp) {
        for(const auto& i : ingredients) {
            delete i;
        }
        ingredients.clear();
        for(auto const& i : esp.ingredients) {
            ingredients.push_back(i->clone());
        }     
        name = esp.name;    
    }
}

