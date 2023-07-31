// =============================================================================
//                                   Headers
// =============================================================================
#include "Menu.h"

// =============================================================================
//                                 Constructor
// =============================================================================
Menu::Menu()
{
    //
}

// =============================================================================
//                                 Destructor
// =============================================================================
Menu::~Menu()
{
    //
}

// =============================================================================
//                                    Input
// =============================================================================
void Menu::Input(Event& event)
{
    //
}

// =============================================================================
//                                    Draw
// =============================================================================
void Menu::Draw(RenderWindow& window)
{
    for (auto&& i : menuItems_)
    {
        i.second.Draw(window);
    }
}

// =============================================================================
//                                 Add Menu Item
// =============================================================================
void Menu::AddMenuItem(String key)
{
    menuItems_.emplace(key, MenuItem());
}
