#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <limits>

int getRandom () {
    return std::rand();
}

template <typename T>
float magnitude (sf::Vector2<T> vec) {
    return (vec.x * vec.x) + (vec.y + vec.y);
}