// hello
#include "config.h"
#include "App.h"
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

App::App(config_t c): config(c) {
    holding = 0;
    selected = 0;
    quitting = 0;

    if (!arrow.loadFromSystem(sf::Cursor::Arrow)) {
        fprintf(stderr, "Picky: error loading arrow cursor\n");
        exit(1);
    }

    if (!cross.loadFromSystem(sf::Cursor::Cross)) {
        fprintf(stderr, "Picky: error loading cross cursor\n");
        exit(1);
    }

    // take that, rustaceans
    img = (int *) calloc((config.xres*config.yres), sizeof(int));

    gen_palette();
}

void App::gen_palette(void) {
    srand(time(NULL));
    int r, g, b;
    for (int i = 2; i < PALETTE; i++) {
        r = rand()%255;
        g = rand()%255;
        b = rand()%255;
        palette[i] = sf::Color(r, g, b);
    }
}

void App::handle(sf::Event e) {
    switch (e.type) {
        case sf::Event::Closed:
        {
            quitting = 1;
        }
        break;

        case sf::Event::MouseButtonPressed:
        {

            holding = 1;
            if ((pos.x > PICSTARTX && pos.y > PICSTARTY))
            {
                int snapx = (pos.x-PICSTARTX)/config.scale;
                int snapy = (pos.y-PICSTARTY)/config.scale;
                img[config.xres * snapy + snapx] = selected;
                break;
            }

            int id = check_palette(); // checks pos vs palette
            if (id >= 0) {
                selected = id;
            }
        }
        break;

        case sf::Event::MouseButtonReleased:
            holding = 0;
        break;

        case sf::Event::MouseMoved:
        {
            int snapx = (pos.x-PICSTARTX)/config.scale;
            int snapy = (pos.y-PICSTARTY)/config.scale;
            if (holding) {
                img[config.xres * snapy + snapx] = selected;
            }
        }
        break;

        case sf::Event::KeyPressed:
        {
            switch (e.key.code) {
                case sf::Keyboard::R:
                    gen_palette();
                break;
                case sf::Keyboard::Num1:
                    selected = 0;
                break;
                case sf::Keyboard::Num2:
                    selected = 1;
                break;
                case sf::Keyboard::Num3:
                    selected = 2;
                break;
                case sf::Keyboard::Num4:
                    selected = 3;
                break;
                case sf::Keyboard::Num5:
                    selected = 4;
                break;
                default:
                break;
            }
        }
        default:
            break;
    }
}

int App::check_palette(void) {
    for (int i = 0; i < PALETTE; i++) {
        if ((pos.x > XPADDING && pos.x < (XPADDING+PALWIDTH)) &&
                (pos.y > (TOPBAR+(i*(PALHEIGHT+YPADDING))) &&
                 pos.y < (TOPBAR+(i*(PALHEIGHT+YPADDING))+PALHEIGHT))
            )
        {
            return i;
        }
    }

    return -1;
}

void App::draw_palette(sf::RenderWindow *window) {
    int x = XPADDING;
    int y = TOPBAR;

    for (int i = 0; i < PALETTE; i++) {
        if (i == selected) {
            sf::RectangleShape rect(sf::Vector2f(XPADDING, PALHEIGHT));
            rect.setPosition(0, y);
            rect.setFillColor(sf::Color::White);
            window->draw(rect);
        }

        sf::RectangleShape rect(sf::Vector2f(PALWIDTH, PALHEIGHT));
        rect.setPosition(x, y);
        rect.setFillColor(palette[i]);
        window->draw(rect);

        y += (PALHEIGHT + YPADDING);
    }
}

void App::draw_outline(sf::RenderWindow *window) {
    int snapx = (pos.x-PICSTARTX)/config.scale;
    int snapy = (pos.y-PICSTARTY)/config.scale;

    window->setMouseCursor(arrow);

    if (pos.x >= (PICSTARTX+PICWIDTH)) return;
    if (pos.y >= (PICSTARTY+PICHEIGHT)) return;
    if (pos.x < PICSTARTX) return;
    if (pos.y < PICSTARTY) return;

    window->setMouseCursor(cross);

    sf::RectangleShape rect(sf::Vector2f(SCALE, SCALE));
    rect.setPosition(XCOORD(snapx), YCOORD(snapy));
    rect.setFillColor(palette[selected]);
    window->draw(rect);

    rect.setSize(sf::Vector2f(SCALE-(BORDER*2), SCALE-(BORDER*2)));
    rect.setPosition(XCOORD(snapx)+BORDER, YCOORD(snapy)+BORDER);
    rect.setFillColor(palette[img[config.xres * snapy + snapx]]);
    window->draw(rect);
}

void App::draw_img(sf::RenderWindow *window) {
    for (int x = 0; x < config.xres; x++) {
        for (int y = 0; y < config.yres; y++) {
            if (img[config.xres * y + x] > 0) {
                sf::RectangleShape rect(sf::Vector2f(SCALE, SCALE));
                rect.setPosition(XCOORD(x), YCOORD(y));
                rect.setFillColor(palette[img[config.xres * y +x]]);
                window->draw(rect);
            }
        }
    }
}
