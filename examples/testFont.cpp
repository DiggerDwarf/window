#include <iostream>
#define SW_WANT_GL_SYMBOLS
#include <SW/Window.hpp>
#include <SW/Font.hpp>

#define gl_CheckErrors()                                \
{                                                       \
    GLenum err;                                         \
    while ((err = glGetError()) != GL_NO_ERROR)         \
    std::cout << "OpenGL error: " << err << std::endl;  \
}

void displayGlyphs(const sw::Font* font)
{
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(10);
    glLoadIdentity();
    glScaled(5, 5, 5);
    glColor3f(1, 1, 1);
    for (std::size_t glyphID = 0; glyphID < font->glyphs.size(); glyphID++)
    {
        std::cout << "drew Glyph\t";
        const sw::Glyph& glyph = font->glyphs.at(glyphID);
        if (!glyph.isSimple) continue;

        
        glVertexPointer(2, GL_FLOAT, 0, glyph.simple.points.data());
        glDrawArrays(GL_TRIANGLES, 0, glyph.simple.points.size());


        glTranslatef(8, 0, 0);
    }
    glPointSize(10);
    glBegin(GL_POINT);
    glVertex3f(0, 0, 0);
    glEnd();
    gl_CheckErrors();
}


int main()
{
    const sw::Font* consolas = sw::Font::open("consolas.ttf", "consolas");
    std::cout << "font has " << consolas->glyphs.size() << " glyphs.\n";
    
    if (consolas == NULL)
        return 1;

    sw::Window window(1280, 720, "testFont.exe");


    sw::View view;
    view.type = sw::View::Projection::Perspective;
    view.position = {0, 0, 0};
    view.nearPlane = -1;
    view.farPlane = 1;
    view.fovY = 3;

    window.setView(view);

    sw::Event event;
    bool running = true;

    sw::Rotation theta({0, 1, 0}, 0);
    sw::Rotation phi({1, 0, 0}, 0);

    sw::Clock clock;
    float dt;

    sw::fVec3 offset;

    glLineWidth(1);

    while (running)
    {
        while (window.getEvent(&event))
        {
            switch (event.type)
            {
            case sw::Event::Type::Close:
                running = false;
                break;
            
            case sw::Event::Type::Text:
                printf("Character %c has glyph index %u.\n", event.textInfo.character, consolas->getGlyphIndex(event.textInfo.character));
                break;
                
            
            default:
                break;
            }
        }

        dt = clock.restart().asSeconds();

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

        window.setView(view);

        window.clear();

        displayGlyphs(consolas);

        window.display();
    }
    

    return 0;
}
