/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

// =============================================================================
//                                 Class Menu
// =============================================================================
class Menu
{
    public:
        Menu();
        ~Menu();
        void Input(Event& event);
        void Draw(RenderWindow& window);
        void AddMenuItem(String key);

    private:
        map<String, MenuItem> menuItems_;
};

#endif // MENU_H
