#ifndef MOCHA_H
#define MOCHA_H


class Mocha: public EspressoBased
{
public:
    Mocha();
    Mocha(const Mocha& cap);
	~Mocha();
    void operator=(const Mocha& cap);

    double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;

};



#endif // MOCHA_H