#ifndef __Font_hpp_INCLUDED
#define __Font_hpp_INCLUDED

#include <SW/Config.hpp>
#include <SW/Vector.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace sw
{

class SW_API Glyph
{
public:

    // minX, minY, maxX, maxY
    fVec4   bounds;

    struct SimpleGlyphData
    {
        std::vector<fVec2> points;
        std::vector<unsigned short> contourEnds;
    } simple;
    struct CompoundGlyphData
    {
        std::vector<Glyph*> parts;
    } Compound;

    bool isSimple;
};

class SW_API Font
{
public:     // change to private later
    static std::unordered_map<std::string, Font*> fonts;

    std::unordered_map<unsigned, unsigned> cmap;

    std::vector<Glyph> glyphs;

    Font(FILE* fontFile, bool* isValid = NULL);
public:
    Font() = delete;
    
    static const Font* open(std::string path, std::string name);
    static void close(std::string name);

    static const Font* get(std::string name);

    unsigned getGlyphIndex(unsigned charCode) const;
};

}   // namespace sw

#endif // __Font_hpp_INCLUDED
