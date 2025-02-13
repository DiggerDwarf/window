#include <iostream>

#define Vector_io
#include <Vector.hpp>

#include <Window.hpp>
#include <Mouse.hpp>
#include <Clock.hpp>
#include <cmath>


int main(int argc, char const *argv[])
{
    // Window backWindow(3000, 3000, "Eello, World !");
    Window window(1280, 800, "Hello, World !");
    // const iVec2 screenSize = Window::getScreenSize();
    // backWindow.setBox({-20, -20}, screenSize + iVec2(20, 20));

    // fVec2 vel(120, -120);

    Event event;
    bool running = true;

    // Clock clock;
    // float dt;

    while (running)
    {
        // while (backWindow.getEvent(&event));
        while (window.getEvent(&event))
        {
            switch (event.type)
            {
                case Event::EventType::Close:
                    running = false;
                    break;
                case Event::EventType::MousePress:
                    std::cout << "Click coordinates : " << iVec2(event.mouseInfo.x, event.mouseInfo.y) << "\n";
                    break;
                case Event::EventType::KeyPress:
                    printf("%d\n", static_cast<int>(event.keyInfo.key));
                
                default:
                    break;
            }
        }

        // dt = clock.restart().asSeconds();

        // vel.y += 120*dt;
        // window.move(vel * dt);
        // if (window.getPosition().y + window.getSize().y > screenSize.y)
        // {
        //     vel.y *= -0.9;
        //     window.setPosition({window.getPosition().x, screenSize.y - window.getSize().y});
        // }
        // if (window.getPosition().x + window.getSize().x > screenSize.x)
        // {
        //     vel.x *= -0.9;
        //     window.setPosition({screenSize.x - window.getSize().x, window.getPosition().y});
        // }
        // if (window.getPosition().x < 0)
        // {
        //     vel.x *= -0.9;
        //     window.setPosition({0, window.getPosition().y});
        // }
    }

    return 0;
}
