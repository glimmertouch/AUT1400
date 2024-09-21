#ifndef Q1_H
#define Q1_H

namespace q1 {

template<typename T = double, typename Func>
T gradient_descent(T initial, T step, Func&& func) {
    T _old = initial;
    T _new = initial + step;
    const T tolerance = static_cast<T>(1e-9);

    auto derivative = [&](T x) -> T {
        const T h = static_cast<T>(1e-6);
        return (func(x + h) - func(x)) / h;
    };

    while (std::abs(func(_old) - func(_new)) > tolerance) {
        _old = _new;
        T grad = derivative(_old);
        _new = _old - grad * step;
    }

    return _new;
}

template<typename T = double, typename Func>
T gradient_descent(T initial, T step) {
    return gradient_descent(initial, step, Func());
}


}

#endif //Q1_H