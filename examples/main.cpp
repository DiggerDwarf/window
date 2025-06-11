#include <iostream>

#define SW_WANT_GL_SYMBOLS

#define sw_Vector_io
#include <SW/Window.hpp>
#include <SW/Font.hpp>

#include <sstream>

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

void displayGlyphs(const std::string& text)
{
    const sw::Font* font = sw::Font::get("sillay");
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(2);
    glLoadIdentity();

    glDisableClientState(GL_COLOR_ARRAY);

    for (std::size_t i = 0; i < text.size(); i++)
    {
        const sw::Glyph& glyph = font->glyphs.at(font->cmap.at(text.at(i)));
        if (!glyph.isSimple) continue;

        glVertexPointer(2, GL_FLOAT, 0, glyph.simple.points.data());
        
        glColor3b(255, 255, 255);

        for (size_t cID = 0; cID < glyph.simple.contourEnds.size(); cID++)
        {
            unsigned short cStart = cID ? glyph.simple.contourEnds.at(cID-1) : 0;
            glDrawArrays(GL_LINE_STRIP, cStart, glyph.simple.contourEnds.at(cID) - cStart);
        }

        glTranslatef(1, 0, 0);
    }
    glLoadIdentity();
    gl_CheckErrors();
}


int main(int argc, const char *argv[])
{
    // SetConsoleOutputCP(1252);

    sw::Font::open("consolas.ttf", "sillay");
    
    sw::Window window(1200, 800, "Hello, World !");

    window.setCursor(sw::Mouse::Cursor::CROSS);

    sw::View view;
    
    view.type = sw::View::Perspective;
    view.position = {0, 0, -5};
    view.fovY = 1.57079632679;
    // view.fovY = 5;
    view.nearPlane = 0.001;
    view.farPlane = 100;
    window.setView(view);

    sw::Event event;
    bool running = true;
    
    const sw::VertexArray cube({
       {{-1, -1, -1}, sw::Color::Blue},
       {{-1, -1,  1}, sw::Color::Green},
       {{-1,  1,  1}, sw::Color::Red},
       {{-1,  1, -1}, sw::Color::Magenta},
       {{ 1,  1, -1}, sw::Color::White},
       {{ 1,  1,  1}, sw::Color::Cyan},
       {{ 1, -1,  1}, sw::Color::Blue},
       {{ 1, -1, -1}, sw::Color::Green}
    }, {
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
    });

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

    const float thing[] = {
        -2, -2, -2
    };

    sw::Rotation theta({0, 1, 0}, 0);
    sw::Rotation phi({1, 0, 0}, 0);

    sw::Clock clock;
    float dt;

    sw::fVec3 offset;

    std::ostringstream demo;

    while (running)
    {
        dt = clock.restart().asSeconds();


        while (window.getEvent(&event))
        {
            switch (event.type)
            {
                case sw::Event::Type::Close:
                    running = false;
                    break;
                
                case sw::Event::Type::KeyPress:
                    if (event.keyInfo.key == sw::Keyboard::Key::Escape)
                        running = false;
                    break;

                case sw::Event::Type::Text:
                    std::wcout << event.textInfo.character;
                    demo << event.textInfo.character;
                    break;

                default:
                    break;
            }
        }
        
        offset = sw::fVec3();

        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Right))    offset.x -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Left))     offset.x += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::PageUp))   offset.y += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::PageDown)) offset.y -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Down))     offset.z -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::Up))       offset.z += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::L))        theta.angle += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::J))        theta.angle -= dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::K))        phi.angle += dt;
        if (sw::Keyboard::isKeyPressed(sw::Keyboard::Key::I))        phi.angle -= dt;

        view.rotation = phi + theta;

        // std::cout << offset << ", " << phi.angle << ", " << theta.angle << ", " << view.rotation.appliedTo(offset) << '\n';

        view.position += view.rotation.appliedTo(offset);

        window.setView(view);

        window.clear(sw::Color(224, 194, 153));

        glEnableClientState(GL_COLOR_ARRAY);

        glEnable(GL_DEPTH_TEST);

        window.draw(cube);

        // glVertexPointer(3, GL_FLOAT, sizeof(sw::Vertex), cube.vertexaccess());
        // glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(sw::Vertex), (const char*)cube.vertexaccess() + 20);

        // glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, cube.indexaccess());

        glColorPointer(4, GL_UNSIGNED_BYTE, 0, outline_colors);

        glLineWidth(5);

        glDisable(GL_DEPTH_TEST);

        glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, outline_indices);

        gl_CheckErrors();

        glPointSize(10);
        glVertexPointer(3, GL_FLOAT, 0, thing);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, &sw::Color::White);
        glDrawArrays(GL_POINTS, 0, 1);

        displayGlyphs(demo.str());

        window.display();

        std::ostringstream oss;
        oss << "Current position : " << view.position;

        window.setTitle(oss.str());
    }

    return 0;
}
