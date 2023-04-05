#include "raylibRenderInterface.h"
#include "raylibFileInterface.h"
#include "raylib.h"
#include "rlgl.h"

void RenderTriangle(Rml::Vertex &vertex, const Rml::Vector2f &translation) {
    auto c = Color{vertex.colour.red, vertex.colour.green, vertex.colour.blue, vertex.colour.alpha};
    rlColor4ub(c.r, c.g, c.b, c.a);
    rlTexCoord2f(vertex.tex_coord.x, vertex.tex_coord.y);
    rlVertex2f(vertex.position.x + translation.x, vertex.position.y + translation.y);
}

void RaylibRenderInterface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f &translation) {
    if (texture == 0) {
        return;
    }
    auto target = *(Texture2D*)texture;

    if (target.id == 0) {
        return;
    }


    if (num_indices < 3) {
        return;
    }

    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling();

    rlBegin(RL_TRIANGLES);
    rlSetTexture(target.id);

    for (unsigned int i = 0; i <= (num_indices - 3); i+=3) {
        if (rlCheckRenderBatchLimit(3)) {
            rlBegin(RL_TRIANGLES);
            rlSetTexture(target.id);
        }

        auto indexA = indices[i];
        auto indexB = indices[i + 1];
        auto indexC = indices[i + 2];

        auto vertexA = vertices[indexA];
        auto vertexB = vertices[indexB];
        auto vertexC = vertices[indexC];

        RenderTriangle(vertexA, translation);
        RenderTriangle(vertexB, translation);
        RenderTriangle(vertexC, translation);
    }
    rlEnd();
    rlSetTexture(0);

    rlDisableScissorTest();
    rlEnableBackfaceCulling();
}

void RaylibRenderInterface::EnableScissorRegion(bool enable) {
    if (!enable) {
        EndScissorMode();
    }
}

void RaylibRenderInterface::SetScissorRegion(int x, int y, int width, int height) {
    BeginScissorMode(x, y, width, height);
}

bool RaylibRenderInterface::LoadTexture(Rml::TextureHandle &texture_handle, Rml::Vector2i &texture_dimensions, const Rml::String &source) {
    auto path = RaylibFileInterface::ParsePath(source);
    if (!FileExists(path.c_str())) {
        return false;
    }

    auto texture = ::LoadTexture(path.c_str());

    if (texture.id == 0) {
        return false;
    }

    auto allocation = (Texture2D*)RL_MALLOC(sizeof(Texture2D));
    allocation[0] = texture;
    texture_handle = (Rml::TextureHandle)allocation;

    texture_dimensions.x = texture.width;
    texture_dimensions.y = texture.height;
    return true;
}

void RaylibRenderInterface::ReleaseTexture(Rml::TextureHandle texture) {
    if (texture == 0) {
        return;
    }
    auto texture2D = (Texture2D*)texture;

    UnloadTexture(*texture2D);

    RL_FREE(texture2D);
}

bool RaylibRenderInterface::GenerateTexture(Rml::TextureHandle &texture_handle, const Rml::byte* source, const Rml::Vector2i &source_dimensions) {
    auto image = GenImageColor(source_dimensions.x, source_dimensions.y, BLANK);

    image.data = (void*) source;

    auto texture = LoadTextureFromImage(image);

    if (texture.id == 0) {
        return false;
    }

    auto allocation = (Texture2D*)RL_MALLOC(sizeof(Texture2D));
    allocation[0] = texture;

    texture_handle = (Rml::TextureHandle)allocation;

    return true;
}
