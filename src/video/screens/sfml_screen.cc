#include "sfml_screen.h"

#include "../../util/log.h"

SFMLScreen::SFMLScreen() :
    window(sf::VideoMode(GAMEBOY_WIDTH, GAMEBOY_HEIGHT), "Emulator")
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
}

SFMLScreen::~SFMLScreen() {
}

void SFMLScreen::draw(const FrameBuffer& buffer) {
    window.clear(sf::Color::Black);

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    sf::Image image;
    image.create(GAMEBOY_WIDTH, GAMEBOY_HEIGHT);
    set_pixels(image, buffer);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    window.draw(sprite);

    window.display();
}

void SFMLScreen::set_pixels(sf::Image& image, const FrameBuffer& buffer) {
    for (unsigned x = 0; x < GAMEBOY_WIDTH; x++) {
        for (unsigned y = 0; y < GAMEBOY_HEIGHT; y++) {
            image.setPixel(x, y, get_color(buffer.get_pixel(x, y)));
        }
    }
}

sf::Color SFMLScreen::get_color(Color color) {
    switch (color) {
        case Color::Color0: return sf::Color(255, 255, 255);
        case Color::Color1: return sf::Color(170, 170, 170);
        case Color::Color2: return sf::Color( 85,  85,  85);
        case Color::Color3: return sf::Color(  0,   0,   0);
    }
}

bool SFMLScreen::is_open() {
    return window.isOpen();
}
