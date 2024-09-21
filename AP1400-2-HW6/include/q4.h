#ifndef Q4_H
#define Q4_H

#include <ranges>

namespace q4 {


struct Vector2D
{
    double x{};
    double y{}; 
};

struct Sensor
{
	Vector2D pos;
	double accuracy;    
};

inline Vector2D kalman_filter(std::vector<Sensor> sensors) {
    Vector2D v;
    double weight = 0;
    auto func = [&](Sensor& s) {
        v.x += s.pos.x * s.accuracy;
        v.y += s.pos.y * s.accuracy;
        weight += s.accuracy; 
    };

    std::ranges::for_each(sensors,func);

    if (weight) {
        v.x /= weight;
        v.y /= weight;
    }
    return v;

}

}
#endif //Q4_H