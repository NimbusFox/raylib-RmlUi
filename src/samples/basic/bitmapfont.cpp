#include "example.h"
#include "raylibRmlUi.h"
#include "samples/sample.h"
#include "samples/event.h"
#include "samples/basic/bitmapfont/fontEngineInterfaceBitmap.h"

Rml::ElementDocument* document;
std::unique_ptr<FontEngineInterfaceBitmap> fontEngine;

Rml::Vector2i Example::GetWindowSize() {
    return Rml::Vector2i{ 1024, 768 };
}

void Example::Initialize() {
    fontEngine = Rml::MakeUnique<FontEngineInterfaceBitmap>();
    Rml::SetFontEngineInterface(fontEngine.get());

    Sample::runGame = RaylibRmlUi::Initialize(1024, 768);

    if (!Sample::runGame) {
        return;
    }

    if (!Rml::LoadFontFace("samples/basic/bitmapfont/Comfortaa_Regular_22.fnt")) {
        Sample::runGame = false;
        return;
    }

    ExampleEventInstancer eventListenerInstancer;
    Rml::Factory::RegisterEventListenerInstancer(&eventListenerInstancer);

    RaylibRmlUi::LoadRml("samples/basic/bitmapfont.rml", "bitmapfont", true);

    document = RaylibRmlUi::GetPage("bitmapfont");

    document->GetElementById("title")->SetInnerRML("Bitmap font");
}

void Example::DeInitialize() {
    fontEngine.reset();
    RaylibRmlUi::DeInitialize();
}

const char* Example::GetWindowTitle() {
    return "- Bitmap Font";
}

void Example::ToggleDebugger() {
    RaylibRmlUi::ToggleDebugger();
}

void Example::Update(float delta) {
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