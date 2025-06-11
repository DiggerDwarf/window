#include <SW/Font.hpp>
#include <cstdint>
#include <iostream>


namespace sw
{

namespace FontParser
{
    void invertEndianness(void* elem, size_t size)
    {
        char* bytes = reinterpret_cast<char*>(elem);
        char temp;
        for (size_t i = 0; i < size/2; i++)
        {
            temp = bytes[i];
            bytes[i] = bytes[size-i];
            bytes[size-i] = temp;
        }
    }

    uint64_t invertEndianness(uint64_t number)
    {
        return (
            ((number & 0xFF              ) << 56) |
            ((number & 0xFF00            ) << 40) |
            ((number & 0xFF0000          ) >> 24) |
            ((number & 0xFF000000        ) << 8 ) |
            ((number & 0xFF00000000      ) >> 8 ) |
            ((number & 0xFF0000000000    ) >> 24) |
            ((number & 0xFF000000000000  ) >> 40) |
            ((number & 0xFF00000000000000) >> 56)
        );
    }
    uint32_t invertEndianness(uint32_t number)
    {
        return (
            ((number & 0xFF      ) << 24) |
            ((number & 0xFF00    ) << 8 ) |
            ((number & 0xFF0000  ) >> 8 ) |
            ((number & 0xFF000000) >> 24)
        );
    }
    uint16_t invertEndianness(uint16_t number)
    {
        return (
            ((number & 0xFF  ) << 8) |
            ((number & 0xFF00) >> 8)
        );
    }

    size_t fread_big(void* buffer, size_t elemSize, size_t elemNum, FILE* file)
    {
        size_t out = fread(buffer, elemSize, elemNum, file);
        
        switch (elemSize)
        {
            case sizeof(uint8_t):
                break;
            case sizeof(uint16_t): {
                uint16_t* buf = reinterpret_cast<uint16_t*>(buffer);
                for (size_t i = 0; i < elemNum; i++)
                    buf[i] = invertEndianness(buf[i]);
                break;
            }
            case sizeof(uint32_t): {
                uint32_t* buf = reinterpret_cast<uint32_t*>(buffer);
                for (size_t i = 0; i < elemNum; i++)
                    buf[i] = invertEndianness(buf[i]);
                break;
            }
            case sizeof(uint64_t): {
                uint64_t* buf = reinterpret_cast<uint64_t*>(buffer);
                for (size_t i = 0; i < elemNum; i++)
                    buf[i] = invertEndianness(buf[i]);
                break;
            }
            default: {
                for (size_t i = 0; i < elemNum; i++)
                    invertEndianness((char*)buffer + (elemNum*elemSize), elemSize);
                break;
            }
        }

        return out;
    }

    bool equals(const char* a, const char* b, size_t max = -1)
    {
        if (!max) return true;
        size_t i = 0;
        while (a[i] == b[i] && i+1 < max && a[i++] != 0);
        return a[i] == b[i];
    }

    typedef struct {
        uint32_t checksum;
        uint32_t offset;
        uint32_t length;
    } tableHeader_t;

    typedef struct {
        tableHeader_t cmap;
        tableHeader_t glyf;
        tableHeader_t head;
        tableHeader_t hhea;
        tableHeader_t hmtx;
        tableHeader_t loca;
        tableHeader_t maxp;
        tableHeader_t name;
        tableHeader_t post;
    } tableDir_t;

    bool verifyTableChecksum(tableHeader_t table, FILE* file)
    {
        fpos_t initialFilePos;
        fgetpos(file, &initialFilePos);

        fseek(file, table.offset, SEEK_SET);

        size_t uintsToRead = (table.length + 3) / 4;

        uint32_t checksum = 0;

        uint32_t temp;

        while (uintsToRead-- > 0)
        {
            fread_big(&temp, sizeof(uint32_t), 1, file);
            checksum += temp;
        }
        
        fsetpos(file, &initialFilePos);

        return checksum == table.checksum;
    }

    bool parseTableDir(FILE* file, tableDir_t* tableDir)
    {
        // read scalerType and check file is true TrueType and not just sfnt-housed
        char scalerType[4];
        fread(scalerType, 1, 4, file);
        if (not equals(scalerType, "true") && not equals(scalerType, "\x00\x01\x00\x00"))
        {
            std::cerr << "File provided is not a ttf font.\n";
            return false;
        }

        // read the offset subtable
        struct offsetSubtable_t {
            uint16_t numTables;
            uint16_t searchRange;
            uint16_t entrySelector;
            uint16_t rangeShift;
        } offsetSubtable;
        fread_big(&offsetSubtable, sizeof(uint16_t), 4, file);

        char tempName[4];
        tableHeader_t tempHeader;

        for (size_t i = 0; i < offsetSubtable.numTables; i++)
        {
            fread(tempName, 1, 4, file);
            fread_big(&tempHeader, sizeof(uint32_t), 3, file);
            if      (equals(tempName, "cmap", 4)) tableDir->cmap = tempHeader;
            else if (equals(tempName, "glyf", 4)) tableDir->glyf = tempHeader;
            else if (equals(tempName, "head", 4)) tableDir->head = tempHeader;
            else if (equals(tempName, "hhea", 4)) tableDir->hhea = tempHeader;
            else if (equals(tempName, "hmtx", 4)) tableDir->hmtx = tempHeader;
            else if (equals(tempName, "loca", 4)) tableDir->loca = tempHeader;
            else if (equals(tempName, "maxp", 4)) tableDir->maxp = tempHeader;
            else if (equals(tempName, "name", 4)) tableDir->name = tempHeader;
            else if (equals(tempName, "post", 4)) tableDir->post = tempHeader;

            // Try to look more into checksum for the 'head' table.
            if (!equals(tempName, "head", 4) && !verifyTableChecksum(tempHeader, file))
                std::cerr << "Checksum for font table " << tempName << " is invalid.\n";
        }
        
        if (tableDir->cmap.offset == 0
         || tableDir->glyf.offset == 0
         || tableDir->head.offset == 0
         || tableDir->hhea.offset == 0
         || tableDir->hmtx.offset == 0
         || tableDir->loca.offset == 0
         || tableDir->maxp.offset == 0
         || tableDir->post.offset == 0
         || tableDir->name.offset == 0)
        {
            std::cerr << "One of the required TrueType tables was not found.\n";
            return false;
        }

        return true;
    }

    float fread_FUnit(FILE* file, float FUnitsPerEm)
    {
        uint16_t temp;
        fread(&temp, 2, 1, file);
        return static_cast<int16_t>(invertEndianness(temp)) / (FUnitsPerEm);
    }
    void fread_FUnits(float* buf, size_t number, FILE* file, float FUnitsPerEm)
    {
        for (size_t i = 0; i < number; i++)
        {
            buf[i] = fread_FUnit(file, FUnitsPerEm);
        }
    }

    void parseCmapFormat_0(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        cmap.reserve(256);
        fseek(file, 4, SEEK_CUR);   // skip table length and language code
        uint8_t cmapArray[256] = {0};
        fread(cmapArray, 1, 256, file);
        for (size_t i = 0; i < 256; i++)
            cmap[i] = cmapArray[i];
        return;
    }

    // void parseCmapFormat_2(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap);

    void parseCmapFormat_4(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        uint16_t subtableLength;
        fread_big(&subtableLength, sizeof(uint16_t), 1, file);

        fseek(file, 2, SEEK_CUR);   // skip language code

        uint16_t segCount;
        fread_big(&segCount, sizeof(uint16_t), 1, file);
        
        segCount /= 2;
        fseek(file, 6, SEEK_CUR);   // ignore optimized search shenanigans

        uint16_t memLength = subtableLength/2 - 8;
        uint16_t* mem = new uint16_t[memLength];

        uint16_t* endCodes = mem;
        fread_big(endCodes, sizeof(uint16_t), segCount, file);

        fseek(file, 2, SEEK_CUR);   // skip reserved

        uint16_t* startCodes = mem + segCount;
        uint16_t* idDelta = startCodes + segCount;
        uint16_t* idRangeOffset = idDelta + segCount;

        fread_big(startCodes, sizeof(uint16_t), memLength - segCount, file);

        uint16_t glyphIndex;

        for (uint16_t seg = 0; seg < segCount; seg++)
        {
            if (!idRangeOffset[seg])
            {
                for (uint16_t charCode = startCodes[seg]; charCode < endCodes[seg]; charCode++)
                {
                    cmap[charCode] = charCode + idDelta[seg];
                }
            }
            else
            {
                for (uint16_t charCode = startCodes[seg]; charCode < endCodes[seg]; charCode++)
                {
                    glyphIndex = *(&idRangeOffset[seg] + idRangeOffset[seg]/2 + (charCode - startCodes[seg]));
                    cmap[charCode] = glyphIndex ? glyphIndex + idDelta[seg] : 0;
                }
            }
        }

        delete[] mem;
        return;
    }

    void parseCmapFormat_6(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        fseek(file, 4, SEEK_CUR);   // skip table length and language code
        uint16_t range[2];
        fread_big(range, sizeof(uint16_t), 2, file);
        
        uint16_t* cmapArray = new uint16_t[range[1]];

        for (size_t i = 0; i < range[1]; i++)
            cmap[i + range[0]] = cmapArray[i];
        

        delete[] cmapArray;
        return;
    }

    // void parseCmapFormat_8(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap);

    void parseCmapFormat_10(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        fseek(file, 10, SEEK_CUR);   // skip reserved, length and language
        uint32_t range[2];
        fread_big(range, sizeof(uint32_t), 2, file);

        uint16_t* cmapArray = new uint16_t[range[1]];

        for (size_t i = 0; i < range[1]; i++)
            cmap[i + range[0]] = cmapArray[i];
        
        delete[] cmapArray;
        return;
    }

    void parseCmapFormat_12(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        fseek(file, 10, SEEK_CUR);  // skip reserved, length and laguage
        uint32_t numGroups;
        fread_big(&numGroups, sizeof(uint32_t), 1, file);

        uint32_t header[3];

        for (uint32_t grp = 0; grp < numGroups; grp++)
        {
            fread_big(header, sizeof(uint32_t), 3, file);
            header[2] -= header[0];     // header[2] becomes an char-glyph offset, like the delta in cmap 4
            for (uint32_t charCode = header[0]; charCode < header[1]; charCode++)
            {
                cmap[charCode] = header[2] + charCode;
            }
        }
    }

    void parseCmapFormat_13(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        // format 13 is same as 12 except no delta
        fseek(file, 10, SEEK_CUR);  // skip reserved, length and laguage
        uint32_t numGroups;
        fread_big(&numGroups, sizeof(uint32_t), 1, file);

        uint32_t header[3];

        for (uint32_t grp = 0; grp < numGroups; grp++)
        {
            fread_big(header, sizeof(uint32_t), 3, file);
            for (uint32_t charCode = header[0]; charCode < header[1]; charCode++)
            {
                cmap[charCode] = header[2];
            }
        }
    }

    // void parseCmapFormat_14(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap);

    bool parseCmapSubtable(FILE* file, std::unordered_map<uint32_t, uint32_t>& cmap)
    {
        uint16_t format;
        fread_big(&format, sizeof(uint16_t), 1, file);

        switch (format)
        {
            case 0:
                parseCmapFormat_0(file, cmap);
                break;
            // case 2:
            //     parseCmapFormat_2(file, cmap);
            //     break;
            case 4:
                parseCmapFormat_4(file, cmap);
                break;
            case 6:
                parseCmapFormat_6(file, cmap);
                break;
            // case 8:
            //     parseCmapFormat_8(file, cmap);
            //     break;
            case 10:
                parseCmapFormat_10(file, cmap);
                break;
            case 12:
                parseCmapFormat_12(file, cmap);
                break;
            case 13:
                parseCmapFormat_13(file, cmap);
                break;
            // case 14:
            //     parseCmapFormat_14(file, cmap);
            //     break;
            default:
                std::cerr << "Cmap format " << format << "not implemented yet (ttf parser)\n";
                return false;
        }
        return true;
    }

    std::unordered_map<uint32_t, uint32_t> parseCmap(FILE* file, const tableDir_t& tableDir)
    {
        fseek(file, tableDir.cmap.offset + sizeof(uint16_t), SEEK_SET);
        uint16_t cmapSubtables;
        fread_big(&cmapSubtables, sizeof(uint16_t), 1, file);
        
        uint16_t platformID[2];
        uint32_t subtableOffset;

        fpos_t chosenTableOffset;
        int chosenTablePriority = -1;
        uint16_t chosenTablePlatform[2];

        int newPriority;

        for (size_t i = 0; i < cmapSubtables; i++)
        {
            fread_big(platformID, sizeof(uint16_t), 2, file);
            fread_big(&subtableOffset, sizeof(uint32_t), 1, file);

            if ((platformID[0] == 0 && platformID[1] != 14) ||
                (platformID[0] == 3 && (platformID[1] == 1 || platformID[1] == 10)))
            {   // if so, the cmap is unicode-encoded
                printf("this table is unicode !!\n");
            }

            if ((platformID[0] == 0 && platformID[1] == 4) ||   //  \____ Unicode, not limited to BMP
                (platformID[0] == 3 && platformID[1] == 10))    //  /
            {
                newPriority = 10;
            } else
            if ((platformID[0] == 0 && platformID[1] == 3) ||   //  \____ Unicode, limited to BMP
                (platformID[0] == 3 && platformID[1] == 1))     //  /
            {
                newPriority = 8;
            }
            else    // Honestly if a font doesn't have one of the above tables imma kms
            {
                newPriority = -1;
            }

            if (newPriority > chosenTablePriority)
            {
                chosenTablePriority = newPriority;
                chosenTableOffset = subtableOffset;
                memcpy(chosenTablePlatform, platformID, 2*sizeof(uint16_t));
            }

        }

        std::unordered_map<uint32_t, uint32_t> cmap;

        if (chosenTablePriority == -1)
        {
            std::cerr << "No suitable cmap table found\n";
            return cmap;
        }
        
        fseek(file, tableDir.cmap.offset + chosenTableOffset, SEEK_SET);

        if (!parseCmapSubtable(file, cmap))
        {
            std::cerr << "An error occured while parsing cmap with platform ID [ "
                    << chosenTablePlatform[0] << " / " << chosenTablePlatform[1]
                    << " ] (ttf parser)\n";
        }

        return cmap;
    }

    void parseSimpleGlyph(Glyph& glyph, uint8_t* glyphData, float unitsPerEm)
    {
        int16_t numContours = (glyphData[0] << 8) + glyphData[1];
        uint8_t* cursor = glyphData + 10;

        for (int contourID = 0; contourID < numContours; contourID++)
        {
            glyph.simple.contourEnds.push_back((cursor[0] << 8) + cursor[1]);
            cursor += 2;
        }
        uint16_t numPoints = glyph.simple.contourEnds.end()[-1];

        cursor += (cursor[0] << 8) + cursor[1] + 2;     // skipping instruction table

        // now i need to extend the flags (get rid of the "reapeat this n times" by repeating it n times)
        std::vector<uint8_t> flags;
        for (; flags.size() < numPoints; cursor++)
        {
            uint8_t flag = *cursor;
            flags.push_back(flag);
            if (flag & (1 << 3))    // check repeat bit
            {
                cursor++;
                flags.insert(flags.end(), *cursor, flag);
            }
        }

        std::vector<int16_t> xCoords, yCoords;
        int16_t where = 0;
        // do for x
        for (int16_t pointID = 0; pointID < numPoints; pointID++)
        {
            if (flags[pointID] & 1 << 1) {
                // 1 byte case
                where += (flags[pointID] & (1 << 4)) ? *cursor : -*cursor;
                cursor++;
            } else if (!(flags[pointID] & (1 << 4))) {
                where += ((cursor[0] << 8) + cursor[1]);
                cursor += 2;
            }
            xCoords.push_back(where);
            // std::cout << where << " = ";
            // std::cout << xCoords.at(pointID) << ' ';
        }
        // then do for y
        where = 0;
        for (int16_t pointID = 0; pointID < numPoints; pointID++)
        {
            if (flags[pointID] & 1 << 2) {
                // 1 byte case
                where += (flags[pointID] & (1 << 5)) ? *cursor : -*cursor;
                cursor++;
            } else if (!(flags[pointID] & (1 << 5))) {
                where += ((cursor[0] << 8) + cursor[1]);
                cursor += 2;
            }
            yCoords.push_back(where);
            // std::cout << where << ' ';
        }
    
        // unwrap into the glyph
        glyph.simple.points.reserve(numPoints);
        for (int16_t pointID = 0; pointID < numPoints; pointID++)
        {
            
            glyph.simple.points.push_back(fVec2(
                xCoords[pointID] / unitsPerEm,
                yCoords[pointID] / unitsPerEm
            ));
            // std::cout << xCoords.at(pointID) << " => " << glyph.simple.points.at(pointID).x << ' ';
        }

    }
    
    void parseCompoundGlyph(Glyph& glyph, uint8_t* glyphData)
    {
        return;
    }

    void parseGlyphs(FILE* file, uint16_t numGlyphs, std::vector<Glyph>& glyphs, tableDir_t tableDir)
    {
        // Get some infos from the head table
        float unitsPerEm;
        fseek(file, tableDir.head.offset, SEEK_SET);
        fseek(file, 18, SEEK_CUR);
        fread_big(&unitsPerEm, sizeof(uint16_t), 1, file);

        unitsPerEm = *reinterpret_cast<uint16_t*>(&unitsPerEm);

        fseek(file, 30, SEEK_CUR); 
        int16_t indexToLocFormat;
        fread_big(&indexToLocFormat, sizeof(int16_t), 1, file);

        // Gather glyph data sizes
        fseek(file, tableDir.loca.offset, SEEK_SET);
        
        uint32_t* loca = new uint32_t[numGlyphs + 1];
        if (indexToLocFormat) {
            fread_big(loca, sizeof(uint32_t), numGlyphs+1, file);
        } else {
            std::cout << "Loca unwrapping is done is this font.\n";
            fread_big(loca, sizeof(uint16_t), numGlyphs, file);
            // Need to unwrap
            uint16_t* shortLoca = reinterpret_cast<uint16_t*>(loca);
            for (int i = numGlyphs - 1; i >= 0; i--)
            {
                loca[i] = shortLoca[i] << 1;
            }
        }

        uint32_t maxGlyphDataSize;

        for (uint16_t glyphID = 0; glyphID < numGlyphs; glyphID++)
        {
            if (loca[glyphID+1] - loca[glyphID] > maxGlyphDataSize)
            {
                maxGlyphDataSize = loca[glyphID+1] - loca[glyphID];
            }
        }

        uint8_t* glyphData = new uint8_t[maxGlyphDataSize];

        
        for (size_t glyphID = 0; glyphID < numGlyphs; glyphID++)
        {
            glyphs.push_back(Glyph());
            Glyph& glyph = glyphs[glyphID];
            fseek(file, tableDir.glyf.offset + loca[glyphID], SEEK_SET);
            fread(glyphData, 1, loca[glyphID+1] - loca[glyphID], file);

            // now i can parse glyph data but i'm freeee from the shackes of freading

            int16_t numContours = (glyphData[0] << 8) + glyphData[1];
            glyph.bounds.x = ((glyphData[2] << 8) + glyphData[3]) / unitsPerEm;
            glyph.bounds.y = ((glyphData[4] << 8) + glyphData[5]) / unitsPerEm;
            glyph.bounds.z = ((glyphData[6] << 8) + glyphData[7]) / unitsPerEm;
            glyph.bounds.w = ((glyphData[8] << 8) + glyphData[9]) / unitsPerEm;

            glyph.isSimple = numContours >= 0;
            if (glyph.isSimple) parseSimpleGlyph(glyph, glyphData, unitsPerEm);
            else parseCompoundGlyph(glyph, glyphData);
        }
        
        delete[] glyphData;
        delete[] loca;

        return;
    }

}   // namespace FontParser


std::unordered_map<std::string, Font*> Font::fonts;


Font::Font(FILE* file, bool* isValid)
{
    using namespace FontParser;

    tableDir_t tableDir{};


    if (!parseTableDir(file, &tableDir))
    {
        std::cerr << "Something wrong happened while parsing the font's table directory.\n";
        if (isValid) *isValid = false;
        return;
    }

    this->cmap = parseCmap(file, tableDir);
    if (this->cmap.size() == 0)
    {
        std::cerr << "No character to glyph mapping was extracted\n";
        if (isValid) *isValid = false;
        return;
    }

    std::cout << "Characters in cmap : " << this->cmap.size() << '\n';

    fseek(file, tableDir.maxp.offset + 4, SEEK_SET);    // Also skip version
    uint16_t numGlyphs;
    fread_big(&numGlyphs, sizeof(uint16_t), 1, file);

    this->glyphs.reserve(numGlyphs);
    
    parseGlyphs(file, numGlyphs, this->glyphs, tableDir);

    if (isValid) *isValid = true;
    return;
}

const Font* Font::open(std::string path, std::string name)
{
    FILE* fontFile = fopen(path.c_str(), "rb");
    bool isValid;
    Font* newFontPtr = new Font(fontFile, &isValid);
    fclose(fontFile); fontFile = NULL;

    if (isValid)
    {
        Font::fonts.insert(std::make_pair(name, newFontPtr));
        return newFontPtr;
    }
    else
    {
        std::cerr << "There was a problem while parsing the font at " << path << ".\n";
        delete newFontPtr;
        return NULL;
    }

}

void Font::close(std::string name)
{
    if (Font::fonts.find(name) == Font::fonts.end())
        return;
    
    Font::fonts.erase(name);
    return;
}

const Font* Font::get(std::string name)
{
    if (Font::fonts.find(name) == Font::fonts.end())
        return NULL;

    return Font::fonts.at(name);
}

unsigned Font::getGlyphIndex(unsigned charCode) const
{
    std::unordered_map<unsigned, unsigned>::const_iterator it = cmap.find(charCode);
    return it == cmap.end() ? 0 : it->second;
}

}   // namespace sw

#pragma GCC diagnostic pop
