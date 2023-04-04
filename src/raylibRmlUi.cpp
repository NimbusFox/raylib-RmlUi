#include "raylibRmlUi.h"
#include "raylibSystemInterface.h"
#include "raylibRenderInterface.h"
#include "raylib.h"

RaylibRenderInterface renderInterface;
RaylibSystemInterface systemInterface;
Rml::Context* context;
std::unordered_map<std::string, Rml::ElementDocument*> documents;

bool RaylibRmlUi::Initialize(int windowWidth, int windowHeight) {
	Rml::SetRenderInterface(&renderInterface);
	Rml::SetSystemInterface(&systemInterface);

	Rml::Initialise();

	context = Rml::CreateContext("demo", Rml::Vector2i{windowWidth, windowHeight});

	if (!context) {
		Rml::Shutdown();
		return false;
	}

	Rml::Debugger::Initialise(context);

	Rml::LoadFontFace("./assets/UbuntuMono-Regular.ttf");

	documents["index"] = context->LoadDocument("./assets/index.rml");

	documents["index"]->Show();
}

void RaylibRmlUi::DeInitialize() {
	for (auto &document : documents) {
		document.second->Close();
	}

	documents.clear();

	Rml::Shutdown();
}

void RaylibRmlUi::EnableDebugger() {
	Rml::Debugger::SetVisible(true);
}

void RaylibRmlUi::DisableDebugger() {
	Rml::Debugger::SetVisible(false);
}

void RaylibRmlUi::ToggleDebugger() {
	Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
}

void RaylibRmlUi::Update() {
	auto delta = GetMouseDelta();
	if (delta.x != 0 || delta.y != 0) {
		auto mousePos = GetMousePosition();

		context->ProcessMouseMove(mousePos.x, mousePos.y, 0);
	}

	if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
		context->ProcessMouseButtonDown(0, 0);
	}

	if (IsMouseButtonUp(MouseButton::MOUSE_BUTTON_LEFT)) {
		context->ProcessMouseButtonUp(0, 0);
	}

	context->Update();
}

void RaylibRmlUi::Draw() {
	context->Render();
}
