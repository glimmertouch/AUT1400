#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

class EspressoBased
{
public:
    std::string get_name();
    virtual double price();

    void brew();
    std::vector<Ingredient*>& get_ingredients();

    virtual ~EspressoBased();

protected:
    EspressoBased() {}
    EspressoBased(const EspressoBased& esp);

    void operator=(const EspressoBased& esp);
    std::vector<Ingredient*> ingredients;
    std::string name;


};
#endif // ESPRESSO_BASED_H