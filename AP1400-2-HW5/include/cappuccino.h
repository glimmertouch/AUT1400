#ifndef CAPPUCCINO
#define CAPPUCCINO

class Cappuccino: public EspressoBased
{
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
	~Cappuccino();
    void operator=(const Cappuccino& cap);

    double price() override;

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items();

private:
    std::vector<Ingredient*> side_items;

};

#endif // CAPPUCCINO