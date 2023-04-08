#include "example.h"
#include "raylibRmlUi.h"
#include "samples/sample.h"

Rml::Vector2i Example::GetWindowSize() {
    return Rml::Vector2i{ 1280, 720 };
}

void Example::Initialize() {
    RaylibRmlUi::Initialize(1280, 720);

    RaylibRmlUi::LoadFont("UbuntuMono-Regular.ttf");

    RaylibRmlUi::LoadRml("raylib.rml", "index", true);
}

void Example::DeInitialize() {
    RaylibRmlUi::DeInitialize();
}

const char* Example::GetWindowTitle() {
    return "";
}

void Example::ToggleDebugger() {
    RaylibRmlUi::ToggleDebugger();
}

void Example::Update(float) {
    RaylibRmlUi::Update();
}

void Example::Render() {
    RaylibRmlUi::Draw();
}

bool Example::RunProgram() {
    return Sample::runGame;
}

void Example::StopProgram() {
    Sample::runGame = false;
}