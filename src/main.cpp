#include <iostream>

#define Vector_io
#include <Vector.hpp>

#include <Window.hpp>
#include <Mouse.hpp>
#include <Clock.hpp>
#include <cmath>


int main(int argc, char const *argv[])
{
    sw::Window window(800, 800, "Hello, World !");

    window.setCursor(sw::Mouse::Cursor::CROSS);

    sw::Event event;
    bool running = true;

    #define nb_VERTICES 6

    float vertices[nb_VERTICES*2] = {
        -0.5, -0.5,
        0, 0.5,
        0.5, -0.5,
        -0.5, 0.5,
        0, -0.5,
        0.5, 1.0
    };

    const sw::Color colors[nb_VERTICES] = {
        sw::Color::Red,
        sw::Color::Blue,
        sw::Color::Green,
        sw::Color(255, 0, 0, 255),
        sw::Color(0, 255, 0, 127),
        sw::Color(0, 0, 255, 0)
    };

    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // glDisable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);

    // glMatrixMode(GL_PROJECTION);
    // glOrtho(0, 1280, 0, 800, -1, 1);

    float deltaTime;
    sw::Clock clock;
    unsigned selected = 0;

    while (running)
    {
        deltaTime = clock.restart().asSeconds();
        while (window.getEvent(&event))
        {
            switch (event.type)
            {
                case sw::Event::EventType::Close:
                    running = false;
                    break;
                case sw::Event::EventType::MousePress:
                    std::cout << "Click coordinates : " << sw::iVec2(event.mouseInfo.x, event.mouseInfo.y) << "\n";
                    break;
                case sw::Event::EventType::KeyPress:
                    switch (event.keyInfo.key)
                    {
                    case sw::Keyboard::Key::Right:
                        vertices[2*selected] += deltaTime;
                        break;
                    case sw::Keyboard::Key::Left:
                        vertices[2*selected] -= deltaTime;
                        break;
                    case sw::Keyboard::Key::Up:
                        vertices[2*selected + 1] += deltaTime;
                        break;
                    case sw::Keyboard::Key::Down:
                        vertices[2*selected + 1] -= deltaTime;
                        break;
                    case sw::Keyboard::Key::Enter:
                        selected = (selected + 1) % nb_VERTICES;
                        break;

                    default:
                        break;
                    }
                
                default:
                    break;
            }
        }

        window.clear(sw::Color::Black);



        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

        glDrawArrays(GL_TRIANGLES, 0, nb_VERTICES);

        window.update();



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
