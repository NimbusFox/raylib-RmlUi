#include "example.h"
#include "raylibRmlUi.h"
#include "samples/event.h"
#include "samples/sample.h"

Rml::ElementDocument* document;

float animationTimer = 1.4f;

Rml::Vector2i Example::GetWindowSize() {
    return Rml::Vector2i{ 1700, 900 };
}

void Example::Initialize() {
    Sample::runLoop = true;
    Sample::singleLoop = false;
    Sample::nudge = 0;
    RaylibRmlUi::Initialize(1700, 900);

    RaylibRmlUi::LoadFont("LatoLatin-Bold.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-BoldItalic.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-Italic.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-Regular.ttf");
    RaylibRmlUi::LoadFont("NotoEmoji-Regular.ttf");

    ExampleEventInstancer eventListenerInstancer;
    Rml::Factory::RegisterEventListenerInstancer(&eventListenerInstancer);

    RaylibRmlUi::LoadRml("samples/basic/animation.rml", "animation", true);

    document = RaylibRmlUi::GetPage("animation");
    document->AddEventListener(Rml::EventId::Keydown, new ExampleEvent("hello"));
    document->AddEventListener(Rml::EventId::Keyup, new ExampleEvent("hello"));
    document->AddEventListener(Rml::EventId::Animationend, new ExampleEvent("hello"));

    document->GetElementById("title")->SetInnerRML("Animation");
    using namespace Rml;

    // Button fun
    {
        auto el = document->GetElementById("start_game");
        auto p1 = Transform::MakeProperty({ Transforms::Rotate2D{ 10.f }, Transforms::TranslateX{ 100.f }});
        auto p2 = Transform::MakeProperty({ Transforms::Scale2D{ 3.f }});
        el->Animate("transform", p1, 1.8f, Tween{ Tween::Elastic, Tween::InOut }, -1, true);
        el->AddAnimationKey("transform", p2, 1.3f, Tween{ Tween::Elastic, Tween::InOut });
    }
    {
        auto el = document->GetElementById("high_scores");
        el->Animate("margin-left", Property(0.f, Property::PX), 0.3f, Tween{ Tween::Sine, Tween::In }, 10, true, 1.f);
        el->AddAnimationKey("margin-left", Property(100.f, Property::PX), 3.0f, Tween{ Tween::Circular, Tween::Out });
    }
    {
        auto el = document->GetElementById("options");
        el->Animate("image-color", Property(Colourb(128, 255, 255, 255), Property::COLOUR), 0.3f, Tween{}, -1, false);
        el->AddAnimationKey("image-color", Property(Colourb(128, 128, 255, 255), Property::COLOUR), 0.3f);
        el->AddAnimationKey("image-color", Property(Colourb(0, 128, 128, 255), Property::COLOUR), 0.3f);
        el->AddAnimationKey("image-color", Property(Colourb(64, 128, 255, 0), Property::COLOUR), 0.9f);
        el->AddAnimationKey("image-color", Property(Colourb(255, 255, 255, 255), Property::COLOUR), 0.3f);
    }
    {
        auto el = document->GetElementById("exit");
        PropertyDictionary pd;
        StyleSheetSpecification::ParsePropertyDeclaration(pd, "transform", "translate(200px, 200px) rotate(1215deg)");
        el->Animate("transform", *pd.GetProperty(PropertyId::Transform), 3.f, Tween{ Tween::Bounce, Tween::Out }, -1);
    }

    // Transform tests
    {
        auto el = document->GetElementById("generic");
        auto p = Transform::MakeProperty({ Transforms::TranslateY{ 50, Property::PX }, Transforms::Rotate3D{ 0, 0, 1, -90, Property::DEG }, Transforms::ScaleY{ 0.8f }});
        el->Animate("transform", p, 1.5f, Tween{ Tween::Sine, Tween::InOut }, -1, true);
    }
    {
        auto el = document->GetElementById("combine");
        auto p = Transform::MakeProperty({ Transforms::Translate2D{ 50, 50, Property::PX }, Transforms::Rotate2D(1215) });
        el->Animate("transform", p, 8.0f, Tween{}, -1, true);
    }
    {
        auto el = document->GetElementById("decomposition");
        auto p = Transform::MakeProperty({ Transforms::TranslateY{ 50, Property::PX }, Transforms::Rotate3D{ 0.8f, 0, 1, 110, Property::DEG }});
        el->Animate("transform", p, 1.3f, Tween{ Tween::Quadratic, Tween::InOut }, -1, true);
    }

    // Mixed units tests
    {
        auto el = document->GetElementById("abs_rel");
        el->Animate("margin-left", Property(50.f, Property::PERCENT), 1.5f, Tween{}, -1, true);
    }
    {
        auto el = document->GetElementById("abs_rel_transform");
        auto p = Transform::MakeProperty({ Transforms::TranslateX{ 0, Property::PX }});
        el->Animate("transform", p, 1.5f, Tween{}, -1, true);
    }
    {
        auto el = document->GetElementById("animation_event");
        el->Animate("top", Property(Math::RandomReal(250.f), Property::PX), 1.5f, Tween{ Tween::Cubic, Tween::InOut });
        el->Animate("left", Property(Math::RandomReal(250.f), Property::PX), 1.5f, Tween{ Tween::Cubic, Tween::InOut });
    }
}

void Example::DeInitialize() {
    RaylibRmlUi::DeInitialize();
}

const char* Example::GetWindowTitle() {
    return "- Animation";
}

void Example::ToggleDebugger() {
    RaylibRmlUi::ToggleDebugger();
}

void Example::Update(float delta) {
    animationTimer -= delta;
        while (animationTimer < 0.0f) {
            auto el = document->GetElementById("help");
            if (el->IsClassSet("fadeout")) {
                el->SetClass("fadeout", false);
                el->SetClass("fadein", true);
            } else if (el->IsClassSet("fadein")) {
                el->SetClass("fadein", false);
                el->SetClass("textalign", true);
            } else {
                el->SetClass("textalign", false);
                el->SetClass("fadeout", true);
            }

            animationTimer += 1.4f;
        }
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