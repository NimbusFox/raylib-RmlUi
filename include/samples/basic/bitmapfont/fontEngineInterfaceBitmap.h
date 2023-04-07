#ifndef RMLUI_EXAMPLE_FONTENGINEINTERFACEBITMAP_H
#define RMLUI_EXAMPLE_FONTENGINEINTERFACEBITMAP_H

#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/FontEngineInterface.h>

using Rml::FontFaceHandle;
using Rml::FontEffectsHandle;

using Rml::Vector2i;
using Rml::Vector2f;
using Rml::Colourb;
using Rml::Texture;
using Rml::String;
using Rml::Character;
using Rml::Style::FontStyle;
using Rml::Style::FontWeight;
using Rml::byte;

using Rml::FontEffectList;
using Rml::GeometryList;


class FontEngineInterfaceBitmap : public Rml::FontEngineInterface {
public:
    FontEngineInterfaceBitmap();

    virtual ~FontEngineInterfaceBitmap();

    /// Called by RmlUi when it wants to load a font face from file.
    bool LoadFontFace(const String &file_name, bool fallback_face, FontWeight weight) override;

    /// Called by RmlUi when it wants to load a font face from memory, registered using the provided family, style, and weight.
    /// @param[in] data A pointer to the data.
    bool LoadFontFace(const byte* data, int data_size, const String &family, FontStyle style, FontWeight weight, bool fallback_face) override;

    /// Called by RmlUi when a font configuration is resolved for an element. Should return a handle that
    /// can later be used to resolve properties of the face, and generate string geometry to be rendered.
    FontFaceHandle GetFontFaceHandle(const String &family, FontStyle style, FontWeight weight, int size) override;

    /// Called by RmlUi when a list of font effects is resolved for an element with a given font face.
    FontEffectsHandle PrepareFontEffects(FontFaceHandle handle, const FontEffectList &font_effects) override;

    /// Should return the point size of this font face.
    int GetSize(FontFaceHandle handle) override;

    /// Should return the pixel height of a lower-case x in this font face.
    int GetXHeight(FontFaceHandle handle) override;

    /// Should return the default height between this font face's baselines.
    int GetLineHeight(FontFaceHandle handle) override;

    /// Should return the font's baseline, as a pixel offset from the bottom of the font.
    int GetBaseline(FontFaceHandle handle) override;

    /// Should return the font's underline, as a pixel offset from the bottom of the font.
    float GetUnderline(FontFaceHandle handle, float &thickness) override;

    /// Called by RmlUi when it wants to retrieve the width of a string when rendered with this handle.
    int GetStringWidth(FontFaceHandle handle, const String &string, Character prior_character = Character::Null) override;

    /// Called by RmlUi when it wants to retrieve the geometry required to render a single line of text.
    int GenerateString(FontFaceHandle face_handle, FontEffectsHandle font_effects_handle, const String &string, const Vector2f &position,
            const Colourb &colour, float opacity, GeometryList &geometry) override;

    /// Called by RmlUi to determine if the text geometry is required to be re-generated.eometry.
    int GetVersion(FontFaceHandle handle) override;
};
#endif //RMLUI_EXAMPLE_FONTENGINEINTERFACEBITMAP_H
