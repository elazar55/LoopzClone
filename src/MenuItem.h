// =============================================================================
//                                   Headers
// =============================================================================
#if !defined(MENUITEM_H)
#define MENUITEM_H

#include <SFML/Graphics.hpp>

using namespace sf;

// =============================================================================
//                               Class MenuItem
// =============================================================================
class MenuItem
{
    public:
        MenuItem();
        void setColor(Color color);
        void setFont(String fontName);
        void setPos(Vector2f pos);
        void setSize(int size);
        void setString(String text);
        void Select();
        void DeSelect();
        void Draw(RenderWindow& window);

    private:
        Text  text_;
        Font  font_;
        bool  selected_;
        Color selectedColor_;
        Color defaultColor_;
};

#endif // MENUITEM_H
