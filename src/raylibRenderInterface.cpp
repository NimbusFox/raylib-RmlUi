#include "raylibRenderInterface.h"
#include "raylib.h"

void RaylibRenderInterface::RenderGeometry(Rml::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rml::TextureHandle texture, const Rml::Vector2f &translation) {
	if (texture == 0) {
		return;
	}
	auto target = *(Texture2D*)texture;

	for (auto i = 0 ; i < num_indices ; i += 6) {
		auto topLeft = vertices[indices[i]];
		auto bottomRight = vertices[indices[i + 5]];

		auto topLeftTarget = Vector2{ topLeft.tex_coord.x * target.width, topLeft.tex_coord.y * target.height };
		auto bottomRightTarget = Vector2{ bottomRight.tex_coord.x * target.width, bottomRight.tex_coord.y * target.height };

		DrawTexturePro(target,
				Rectangle{ topLeftTarget.x, topLeftTarget.y, bottomRightTarget.x - topLeftTarget.x, bottomRightTarget.y - topLeftTarget.y },
				Rectangle{ topLeft.position.x + translation.x, topLeft.position.y + translation.y, bottomRight.position.x - topLeft.position.x,
						   bottomRight.position.y - topLeft.position.y },
				Vector2{ 0, 0 },
				0.0f,
				Color{ topLeft.colour.red, topLeft.colour.green, topLeft.colour.blue, topLeft.colour.alpha });
	}
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
	if (!FileExists(source.c_str())) {
		return false;
	}

	auto texture = ::LoadTexture(source.c_str());

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
