/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef MENU_H
#define MENU_H

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
        bool SetFont(string font);
        void Draw(RenderWindow& window);
        void SetPosition(Vector2f position);

    private:
        Text new_game_text_;
        Font font_;
};

#endif // MENU_H
