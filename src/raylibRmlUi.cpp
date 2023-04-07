#include "raylibRmlUi.h"
#include "raylibFileInterface.h"
#include "raylibSystemInterface.h"
#include "raylibRenderInterface.h"
#include "raylib.h"

RaylibFileInterface fileInterface;
RaylibRenderInterface renderInterface;
RaylibSystemInterface systemInterface;

Rml::Context* RaylibRmlUi::Context;
std::unordered_map<std::string, Rml::ElementDocument*> documents;

bool RaylibRmlUi::Initialize(int windowWidth, int windowHeight) {
    Rml::SetFileInterface(&fileInterface);
    Rml::SetRenderInterface(&renderInterface);
    Rml::SetSystemInterface(&systemInterface);

    Rml::Initialise();

    Context = Rml::CreateContext("demo", Rml::Vector2i{windowWidth, windowHeight});

    if (!Context) {
        Rml::Shutdown();
        return false;
    }

    Rml::Debugger::Initialise(Context);

    return true;
}

void RaylibRmlUi::LoadFont(const char* path) {
    Rml::LoadFontFace(path);
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
    if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
        Context->ProcessMouseButtonDown(0, 0);
    }

    if (IsMouseButtonUp(MouseButton::MOUSE_BUTTON_LEFT)) {
        Context->ProcessMouseButtonUp(0, 0);
    }

    if (delta.x != 0 || delta.y != 0) {
        auto mousePos = GetMousePosition();

        Context->ProcessMouseMove(mousePos.x, mousePos.y, 0);
    }

    Context->ProcessMouseWheel(-GetMouseWheelMove(), 0);

    systemInterface.HandleKeyboardEvents(Context);

    Context->Update();
}

void RaylibRmlUi::Draw() {
    renderInterface.BeginFrame();
    Context->Render();
    renderInterface.EndFrame();
}

void RaylibRmlUi::LoadRml(const char* path, const char* id, bool show) {
    documents[id] = Context->LoadDocument(path);

    if (show) {
        ShowPage(id);
    }
}

void RaylibRmlUi::ShowPage(const char* id) {
    for (auto& page : documents) {
        page.second->Hide();

        if (page.first == id) {
            page.second->Show();
        }
    }
}

Rml::ElementDocument* RaylibRmlUi::GetPage(const char* id) {
    for (auto& page : documents) {
        if (page.first == id) {
            return page.second;
        }
    }

    return nullptr;
}
