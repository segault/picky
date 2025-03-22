// hello
#pragma once

#include "config.h"
#include <SFML/Graphics.hpp>

class App {
private:
    config_t config;

    sf::Cursor arrow;
    sf::Cursor cross;

    int *img;
    sf::Color palette[PALETTE];
    int selected;
    int holding; // drag to draw

    void gen_palette(void);
    int check_palette(void);
public:
    sf::Vector2i pos;
    int quitting;

    App(config_t c);
    void handle(sf::Event e);
    void draw_palette(sf::RenderWindow *window);
    void draw_img(sf::RenderWindow *window);
    void draw_outline(sf::RenderWindow *window);
};
