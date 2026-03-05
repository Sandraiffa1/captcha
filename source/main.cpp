#include <SFML/Graphics.hpp>
#include <array>
#include <cstdlib>
#include <ctime>
#include "FontManager.hpp"

void generate_captcha(std::array<sf::Text, 5> &captcha, sf::View &view)
{
    auto size = view.getSize();
    float spacing = size.x / 6;
    for (int i = 0; i < 5; ++i)
    {
        char c = 65 + rand() % 26;
        captcha[i].setString(sf::String(c));
        captcha[i].setCharacterSize(40 + rand() % 30);
        captcha[i].setFillColor({static_cast<uint8_t>(rand() % 256),
                                 static_cast<uint8_t>(rand() % 256),
                                 static_cast<uint8_t>(rand() % 256)});
        auto bounds = captcha[i].getLocalBounds();
        captcha[i].setOrigin(bounds.size / 2.0f);
        captcha[i].setPosition({spacing * (i + 1), size.y / 2});
        captcha[i].setRotation(sf::degrees(-30 + rand() % 61));
    }
}

bool compare(const sf::Text &user_input, const std::array<sf::Text, 5> &captcha)
{
    auto s = user_input.getString();
    if (s.getSize() != 5){
        return false;
    }
    for (int i = 0; i < 5; ++i) {
        if (s[i] != captcha[i].getString()[0]) {
            return false;
        }
    }
    return true;
}

void reset(sf::Text &user_input, std::array<sf::Text, 5> &captcha, sf::View &view)
{
    user_input.setString("");
    generate_captcha(captcha, view);
}

int main()
{
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode({400u, 300u}), "Captcha");
    sf::View view = window.getDefaultView();
    sf::Text user_input(FontManager::Instance(), "", 30);
    user_input.setFillColor(sf::Color::Red);
    user_input.setPosition({10, 10});
    std::array<sf::Text, 5> captcha{
        sf::Text(FontManager::Instance()), sf::Text(FontManager::Instance()),
        sf::Text(FontManager::Instance()), sf::Text(FontManager::Instance()),
        sf::Text(FontManager::Instance())};
    reset(user_input, captcha, view);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || event->is<sf::Event::Resized>())
            {
                if (event->is<sf::Event::Resized>()) {
                    view = sf::View(
                        sf::FloatRect({0, 0}, {static_cast<float>(window.getSize().x),
                                               static_cast<float>(window.getSize().y)}));
                }
                reset(user_input, captcha, view);
            }
            if (auto *text = event->getIf<sf::Event::TextEntered>())
            {
                uint32_t c = text->unicode;
                if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
                    user_input.setString(user_input.getString() + sf::String(static_cast<char>(std::toupper(c))));
                }                   
            }
            if (auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Backspace)
                {
                    auto s = user_input.getString();
                    if (!s.isEmpty())
                    {
                        s.erase(s.getSize() - 1);
                        user_input.setString(s);
                    }
                }
                if (key->code == sf::Keyboard::Key::Enter)
                {
                    if (compare(user_input, captcha)){
                        window.close();
                    }
                    else {
                        reset(user_input, captcha, view);
                    }
                }
            }
        }
        window.clear();
        window.setView(view);
        window.draw(user_input);
        for (auto &t : captcha) {
            window.draw(t);
        }
        window.display();
    }
}
