#ifndef RMLUI_EXAMPLE_FONTENGINEBITMAP_H
#define RMLUI_EXAMPLE_FONTENGINEBITMAP_H

#include <cstdint>
#include <RmlUi/Core/Types.h>
#include "fontEngineInterfaceBitmap.h"

class FontFaceBitmap;

namespace FontProviderBitmap {
    void Initialise();

    void Shutdown();

    bool LoadFontFace(const String &file_name);

    FontFaceBitmap* GetFontFaceHandle(const String &family, FontStyle style, FontWeight weight, int size);
}


struct BitmapGlyph {
    int advance = 0;
    Vector2f offset = { 0, 0 };
    Vector2f position = { 0, 0 };
    Vector2f dimension = { 0, 0 };
};

struct FontMetrics {
    int size = 0;
    int x_height = 0;
    int line_height = 0;
    int baseline = 0;
    float underline_position = 0, underline_thickness = 0;
};

// A mapping of characters to their glyphs.
using FontGlyphs = Rml::UnorderedMap<Character, BitmapGlyph>;

// Mapping of combined (left, right) character to kerning in pixels.
using FontKerning = Rml::UnorderedMap<std::uint64_t, int>;


class FontFaceBitmap {
public:
    FontFaceBitmap(String family, FontStyle style, FontWeight weight, FontMetrics metrics, Texture texture, Vector2f texture_dimensions, FontGlyphs &&glyphs,
            FontKerning &&kerning);

    // Get width of string.
    int GetStringWidth(const String &string, Character prior_character);

    // Generate the string geometry, returning its width.
    int GenerateString(const String &string, const Vector2f &position, const Colourb &colour, GeometryList &geometry);


    const FontMetrics &GetMetrics() const {
        return metrics;
    }

    const String &GetFamily() const {
        return family;
    }

    FontStyle GetStyle() const {
        return style;
    }

    FontWeight GetWeight() const {
        return weight;
    }

private:
    int GetKerning(Character left, Character right) const;

    String family;
    FontStyle style;
    FontWeight weight;

    FontMetrics metrics;

    Texture texture;
    Vector2f texture_dimensions;

    FontGlyphs glyphs;
    FontKerning kerning;
};


/*
	Parses the font meta data from an xml file.
*/

class FontParserBitmap : public Rml::BaseXMLParser {
public:
    FontParserBitmap() {
    }

    virtual ~FontParserBitmap();

    /// Called when the parser finds the beginning of an element tag.
    void HandleElementStart(const String &name, const Rml::XMLAttributes &attributes) override;

    /// Called when the parser finds the end of an element tag.
    void HandleElementEnd(const String &name) override;

    /// Called when the parser encounters data.
    void HandleData(const String &data, Rml::XMLDataType type) override;

    String family;
    FontStyle style = FontStyle::Normal;
    FontWeight weight = FontWeight::Normal;

    String texture_name;
    Vector2f texture_dimensions = { 0, 0 };

    FontMetrics metrics;
    FontGlyphs glyphs;
    FontKerning kerning;
};
#endif //RMLUI_EXAMPLE_FONTENGINEBITMAP_H
