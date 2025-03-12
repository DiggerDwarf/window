#include <iostream>

#define sw_Vector_io
#include <SW/Window.hpp>
#include <SW/Mouse.hpp>
#include <SW/Clock.hpp>
#include <cmath>

#include <SW/View.hpp>
#define SW_GL_DEBUG
#ifdef SW_GL_DEBUG
    #define gl_CheckErrors()                                \
    {                                                       \
        GLenum err;                                         \
        while ((err = glGetError()) != GL_NO_ERROR)         \
        std::cout << "OpenGL error: " << err << std::endl;  \
    }
#else
    #define gl_CheckErrors()
#endif

#include <winbase.h>

int main(int argc, char const *argv[])
{
    sw::Window window(1200, 800, "Hello, World !");

    window.setCursor(sw::Mouse::Cursor::CROSS);

    sw::View view;
    
    view.type = sw::View::Perspective;
    view.position = {0, 0, -5};
    view.fovY = 1.57079632679;
    // view.fovY = 10;
    view.nearPlane = 0.01;
    view.farPlane = 10;
    window.setView(view);

    sw::Event event;
    bool running = true;
    
    const float vertices[8*3] = {
       -1, -1, -1,
       -1, -1,  1,
       -1,  1,  1,
       -1,  1, -1,
        1,  1, -1,
        1,  1,  1,
        1, -1,  1,
        1, -1, -1
    };

    const unsigned indices[12*3] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 7,
        0, 7, 6,
        0, 6, 1,
        2, 1, 6,
        6, 4, 7,
        4, 3, 2,
        5, 2, 6,
        5, 6, 4,
        5, 4, 2
    };

    const sw::Color colors[8] = {
        sw::Color::Blue,
        sw::Color::Green,
        sw::Color::Red,
        sw::Color::Magenta,
        sw::Color::White,
        sw::Color::Cyan,
        sw::Color::Blue,
        sw::Color::Green
    };
    const sw::Color outline_colors[8] = {
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black,
        sw::Color::Black
    };

    const unsigned outline_indices[24] = {
        0, 1,       4, 3,
        0, 3,       4, 5,
        0, 7,       4, 7,
        2, 1,       6, 1,
        2, 3,       6, 5,
        2, 5,       6, 7
    };

    
    sw::Rotation theta({0, 1, 0}, 0);
    sw::Rotation phi({1, 0, 0}, 0);

    sw::Clock clock;
    float dt;

    while (running)
    {
        dt = clock.restart().asSeconds();
        // glMatrixMode(GL_MODELVIEW);
        // glRotatef(dt*50, 1, 0, 0);
        // glRotatef(dt*25, 0, 1, 0);
        // glRotatef(dt*30, 2, 0,-1);

        while (window.getEvent(&event))
        {
            switch (event.type)
            {
                case sw::Event::EventType::Close:
                    running = false;
                    break;
                
                case sw::Event::EventType::KeyPress:
                    if (event.keyInfo.key == sw::Keyboard::Key::Escape)
                        running = false;
                    break;

                default:
                    break;
            }
        }
        
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Right))    view.position.x -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Left))     view.position.x += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::PageUp))   view.position.y += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::PageDown)) view.position.y -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Down))     view.position.z -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Up))       view.position.z += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::L))        theta.angle += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::J))        theta.angle -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::I))        phi.angle += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::K))        phi.angle -= dt;

        view.rotation = phi + theta;

        window.setView(view);

        window.clear(sw::Color::Black);

        glEnable(GL_DEPTH_TEST);

        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);

        glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, indices);

        glColorPointer(4, GL_UNSIGNED_BYTE, 0, outline_colors);

        glLineWidth(5);

        glDisable(GL_DEPTH_TEST);

        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, outline_indices);

        gl_CheckErrors();

        window.display();

    }

    return 0;
}
