/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SFML/Graphics.hpp>
using namespace sf;
// -----------------------------------------------------------------------------
//                             Class InputHandler
// -----------------------------------------------------------------------------
class EventHandler
{
    private:
        Event   event_;
        Window& window_;

    public:
        EventHandler() = delete;
        EventHandler(RenderWindow& window);
};
#endif // EVENT_HANDLER_H
