// hello
#include "config.h"
#include "App.h"
#include <SFML/Graphics.hpp>
#include <iostream>
// #define CPATH "~/.config/picky/config.lua"
const char *CPATH = "config.lua";

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "picky",
            sf::Style::None);

    config_t *config = load(argc, argv, CPATH);
    App app(*config);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            app.pos = sf::Mouse::getPosition(window);
            app.handle(event);
        }
        if (app.quitting) break; // do you wish to save, cleanup, etc

        window.clear();
        app.draw_palette(&window);
        app.draw_img(&window); ///
        app.draw_outline(&window);
        window.display();
    }

    return 0;
}
