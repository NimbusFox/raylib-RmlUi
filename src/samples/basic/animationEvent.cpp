#include "samples/event.h"
#include "raylib.h"
#include "raylibRmlUi.h"
#include "samples/basic/animation.h"

ExampleEvent::ExampleEvent(const Rml::String &value) : value(value) {}

void ExampleEvent::ProcessEvent(Rml::Event &event) {
    using namespace Rml;

    if (value == "exit") {
        AnimationSample::runGame = false;
        return;
    }

    switch (event.GetId()) {
        case EventId::Keydown: {
            Rml::Input::KeyIdentifier key_identifier = (Rml::Input::KeyIdentifier)event.GetParameter<int>("key_identifier", 0);

            if (key_identifier == Rml::Input::KI_SPACE) {
                AnimationSample::runLoop = !AnimationSample::runLoop;
            } else if (key_identifier == Rml::Input::KI_RETURN) {
                AnimationSample::runLoop = false;
                AnimationSample::singleLoop = true;
            } else if (key_identifier == Rml::Input::KI_OEM_PLUS) {
                AnimationSample::nudge = 1;
            } else if (key_identifier == Rml::Input::KI_OEM_MINUS) {
                AnimationSample::nudge = -1;
            } else if (key_identifier == Rml::Input::KI_LEFT) {
                auto el = RaylibRmlUi::Context->GetRootElement()->GetElementById("keyevent_response");
                if (el) el->Animate("left", Property{ -200.f, Property::DP }, 0.5, Tween{ Tween::Cubic });
            } else if (key_identifier == Rml::Input::KI_RIGHT) {
                auto el = RaylibRmlUi::Context->GetRootElement()->GetElementById("keyevent_response");
                if (el) el->Animate("left", Property{ 200.f, Property::DP }, 0.5, Tween{ Tween::Cubic });
            } else if (key_identifier == Rml::Input::KI_UP) {
                auto el = RaylibRmlUi::Context->GetRootElement()->GetElementById("keyevent_response");
                auto offset_right = Property{ 200.f, Property::DP };
                if (el) el->Animate("left", Property{ 0.f, Property::PX }, 0.5, Tween{ Tween::Cubic }, 1, true, 0, &offset_right);
            } else if (key_identifier == Rml::Input::KI_DOWN) {
                auto el = RaylibRmlUi::Context->GetRootElement()->GetElementById("keyevent_response");
                if (el) el->Animate("left", Property{ 0.f, Property::PX }, 0.5, Tween{ Tween::Cubic });
            }
        }
            break;

        case EventId::Click: {
            auto el = event.GetTargetElement();
            if (el->GetId() == "transition_class") {
                el->SetClass("move_me", !el->IsClassSet("move_me"));
            }
        }
            break;

        case EventId::Animationend: {
            auto el = event.GetTargetElement();
            if (el->GetId() == "animation_event") {
                el->Animate("top", Property(Math::RandomReal(200.f), Property::PX), 1.2f, Tween{ Tween::Cubic, Tween::InOut });
                el->Animate("left", Property(Math::RandomReal(100.f), Property::PERCENT), 0.8f, Tween{ Tween::Cubic, Tween::InOut });
            }
        }
            break;

        default:
            break;
    }
}

void ExampleEvent::OnDetach(Rml::Element*) {
    delete this;
}