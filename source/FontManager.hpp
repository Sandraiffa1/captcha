#pragma once
#include <SFML/Graphics/Font.hpp>

class FontManager
{
public:
    static const sf::Font &Instance()
    {
        static FontManager instance;
        return instance.font_;
    }
    FontManager(const FontManager &) = delete;
    FontManager &operator=(const FontManager &) = delete;

private:
    FontManager() {
        bool tmp = font_.openFromFile("assets/arial.ttf");
    }
    
    sf::Font font_;
};
