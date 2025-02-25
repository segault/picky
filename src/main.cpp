// hello
#include <SFML/Graphics.hpp>
#include <iostream>

#define BORDER 1
#define PALETTE 3
#define SCALE 20
#define XRES 32
#define YRES 32

#define LEFTBAR (100)
#define PICSTARTX (LEFTBAR)
#define PICSTARTY (0)
#define PICWIDTH (SCALE*XRES)
#define PICHEIGHT (SCALE*YRES)
#define XCOORD(x) (PICSTARTX+(x*SCALE))
#define YCOORD(y) (PICSTARTY+(y*SCALE))

#define WIDTH (PICWIDTH + LEFTBAR)
#define HEIGHT (PICHEIGHT)

void handle_event(sf::Event e);
void draw_outline();
void draw_squares();

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "picky", sf::Style::None);
sf::Cursor arrow, cross;

int grid[XRES][YRES] = {};
sf::Vector2i gindex;
sf::Color palette[PALETTE] = {
    sf::Color::Black,
    sf::Color::White,
    sf::Color::Red,
};

int main(void) {
    if (!arrow.loadFromSystem(sf::Cursor::Arrow)) {
        fprintf(stderr, "Picky: error loading arrow cursor\n");
        exit(1);
    }

    if (!cross.loadFromSystem(sf::Cursor::Cross)) {
        fprintf(stderr, "Picky: error loading cross cursor\n");
        exit(1);
    }

    sf::Vector2i pos;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            pos = sf::Mouse::getPosition(window);
            gindex = sf::Vector2i((pos.x-PICSTARTX)/SCALE, (pos.y-PICSTARTY)/SCALE);

            handle_event(event);
        }

        window.clear();
        // pic edge
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(PICSTARTX, PICSTARTY)),
            sf::Vertex(sf::Vector2f(PICSTARTX, PICHEIGHT)),
        };
        window.draw(line, 2, sf::Lines);

        draw_squares();
        draw_outline();
        window.display();
    }

    return 0;
}

void handle_event(sf::Event e) {
    switch (e.type) {
        case sf::Event::Closed:
        {
            window.close();
        }
        break;
        case sf::Event::MouseButtonPressed:
        {
            if (grid[gindex.x][gindex.y] >= PALETTE-1)
                grid[gindex.x][gindex.y] = 0;
            else
                grid[gindex.x][gindex.y]++;
        }
        break;
        default:
            break;
    }
}

void draw_outline() {
    int x = gindex.x;
    int y = gindex.y;

    window.setMouseCursor(arrow);

    if (XCOORD(x) >= (PICSTARTX+PICWIDTH)) return;
    if (YCOORD(y) >= (PICSTARTY+PICHEIGHT)) return;
    if (XCOORD(x) < PICSTARTX) return;
    if (YCOORD(y) < PICSTARTY) return;

    window.setMouseCursor(cross);

    sf::RectangleShape rect(sf::Vector2f(SCALE, SCALE));
    rect.setPosition(XCOORD(x), YCOORD(y));
    rect.setFillColor(sf::Color::White);
    window.draw(rect);

    rect.setSize(sf::Vector2f(SCALE-(BORDER*2), SCALE-(BORDER*2)));
    rect.setPosition(XCOORD(x)+BORDER, YCOORD(y)+BORDER);
    rect.setFillColor(palette[grid[x][y]]);
    window.draw(rect);
}

void draw_squares() {
    for (int x = 0; x < XRES; x++) {
        for (int y = 0; y < YRES; y++) {
            if (grid[x][y] > 0) {
                sf::RectangleShape rect(sf::Vector2f(SCALE, SCALE));
                rect.setPosition(XCOORD(x), YCOORD(y));
                rect.setFillColor(palette[grid[x][y]]);
                window.draw(rect);
            }
        }
    }
}
