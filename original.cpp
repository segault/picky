// hello
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define BORDER 1
#define XPADDING 10
#define YPADDING 5
#define PALETTE 16
#define BG_COLOR 1

#define PALWIDTH (LEFTBAR-(XPADDING*2))
#define PALHEIGHT (SCALE)

#define SCALE 20
#define XRES 32
#define YRES 32

#define LEFTBAR (100)
#define TOPBAR (25)
#define PICSTARTX (LEFTBAR)
#define PICSTARTY (TOPBAR)
#define PICWIDTH (SCALE*XRES)
#define PICHEIGHT (SCALE*YRES)
#define XCOORD(x) (PICSTARTX+(x*SCALE))
#define YCOORD(y) (PICSTARTY+(y*SCALE))

#define WIDTH (PICWIDTH + LEFTBAR)
#define HEIGHT (PICHEIGHT)

void handle_event(sf::Event e);
void draw_outline();
void draw_squares();
void draw_palette();
int check_palette();

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "picky",
        sf::Style::None);
sf::Cursor arrow, cross;

sf::Color palette[PALETTE] = {
    sf::Color::Black,
    sf::Color::White,
};
int selected = 0;

int grid[XRES][YRES] = {};
sf::Vector2i pos;
sf::Vector2i gindex;

int holding = 0;


void gen_palette() {
    int r, g, b;
    for (int i = 2; i < PALETTE; i++) {
        r = rand()%255;
        g = rand()%255;
        b = rand()%255;
        palette[i] = sf::Color(r, g, b);
    }
}

void init() {
    if (!arrow.loadFromSystem(sf::Cursor::Arrow)) {
        fprintf(stderr, "Picky: error loading arrow cursor\n");
        exit(1);
    }

    if (!cross.loadFromSystem(sf::Cursor::Cross)) {
        fprintf(stderr, "Picky: error loading cross cursor\n");
        exit(1);
    }

    srand(time(NULL));
    gen_palette();

    for (int i = 0; i < XRES; i++)
        for (int j = 0; j < YRES; j++)
            grid[i][j] = BG_COLOR;
}

int main(void) {
    init();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            pos = sf::Mouse::getPosition(window);
            gindex = sf::Vector2i((pos.x-PICSTARTX)/SCALE, (pos.y-PICSTARTY)/SCALE);

            handle_event(event);
        }

        window.clear();
        draw_palette();
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
            holding = 1;
            if ((pos.x > PICSTARTX && pos.y > PICSTARTY) && holding)
                grid[gindex.x][gindex.y] = selected;
            else
            {
                int id = check_palette(); // checks pos vs palette
                if (id >= 0) {
                    selected = id;
                } else {
                    break;
                }
            }
        }
        break;
        case sf::Event::MouseButtonReleased:
            holding = 0;
        break;
        case sf::Event::MouseMoved:
            if (holding)
                grid[gindex.x][gindex.y] = selected;
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

int check_palette() {
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

void draw_palette() {
    int x = XPADDING;
    int y = TOPBAR;

    for (int i = 0; i < PALETTE; i++) {
        if (i == selected) {
            sf::RectangleShape rect(sf::Vector2f(XPADDING, PALHEIGHT));
            rect.setPosition(0, y);
            rect.setFillColor(sf::Color::White);
            window.draw(rect);
        }

        sf::RectangleShape rect(sf::Vector2f(PALWIDTH, PALHEIGHT));
        rect.setPosition(x, y);
        rect.setFillColor(palette[i]);
        window.draw(rect);

        y += (PALHEIGHT + YPADDING);
    }
}

void draw_outline() {
    int x = gindex.x;
    int y = gindex.y;

    window.setMouseCursor(arrow);

    if (pos.x >= (PICSTARTX+PICWIDTH)) return;
    if (pos.y >= (PICSTARTY+PICHEIGHT)) return;
    if (pos.x < PICSTARTX) return;
    if (pos.y < PICSTARTY) return;

    window.setMouseCursor(cross);

    sf::RectangleShape rect(sf::Vector2f(SCALE, SCALE));
    rect.setPosition(XCOORD(x), YCOORD(y));
    rect.setFillColor(palette[selected]);
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
