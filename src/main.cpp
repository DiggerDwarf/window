#include <iostream>

#define Vector_io
#include <Vector.hpp>

#include <Window.hpp>

int main(int argc, char const *argv[])
{
    Window window(1080, 720);
    

    Event event;
    bool running = true;
    while (running)
    {
        while (window.getEvent(&event))
        {
            switch (event.type)
            {
                case Event::EventType::WINDOW_CLOSED:
                    running = false;
                    break;
                
                default:
                    break;
            }
        }
    }

    return 0;
}
