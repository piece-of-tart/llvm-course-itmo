#include <SFML/Graphics.hpp>

#include "Graphics.hpp"
#include "defs.h"

sf::RenderWindow graphics_window(sf::VideoMode({WIDTH_IN_PIXEL, HEIGHT_IN_PIXEL}), "Game of Life");

void Graphics_put_pixel(int x, int y, int r, unsigned argb) {
  sf::RectangleShape shape;
  shape.setSize(sf::Vector2f(r, r));
  shape.setPosition({1.0f * x * r, 1.0f * y * r});
  shape.setFillColor(sf::Color(argb));
  graphics_window.draw(shape);
}

void Graphics_flush() {
  graphics_window.display();
  graphics_window.clear();
}
