#include "Menu.h"

Menu::Menu()
{
    //
}

Menu::~Menu() {}

void Menu::Input(Event& event)
{
    //
}

bool Menu::SetFont(string font)
{
    if (!font_.loadFromFile(font)) return false;
    new_game_text_.setFont(font_);
    return true;
}

void Menu::Draw(RenderWindow& window)
{
    window.draw(new_game_text_);
}
