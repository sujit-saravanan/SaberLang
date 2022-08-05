#pragma once

template<typename T>
inline bool is_either(T a, T b) {
    return a == b;
}

template<typename T, typename... Ts>
inline bool is_either(T a, T b, Ts... args) {
    return is_either(a, b) || is_either(a, args...);
}

int foo(int x, int y, int z) {
    return is_either(x, y, z);
}
