#ifndef RMLUI_EXAMPLE_RAYLIBRENDERINTERFACE_H
#define RMLUI_EXAMPLE_RAYLIBRENDERINTERFACE_H

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

class RaylibRenderInterface : public Rml::RenderInterface {
public:
    void RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f &translation) override;

    void BeginFrame();

    void EndFrame();
    
    void EnableScissorRegion(bool enable) override;

    void SetScissorRegion(int x, int y, int width, int height) override;

    bool LoadTexture(Rml::TextureHandle &texture_handle, Rml::Vector2i &texture_dimensions, const Rml::String &source) override;

    void ReleaseTexture(Rml::TextureHandle texture) override;

    bool GenerateTexture(Rml::TextureHandle &texture_handle, const Rml::byte* source, const Rml::Vector2i &source_dimensions) override;

    void SetTransform(const Rml::Matrix4f* transform) override;

    ~RaylibRenderInterface();
};

#endif //RMLUI_EXAMPLE_RAYLIBRENDERINTERFACE_H
