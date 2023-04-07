#include "samples/event.h"
#include "raylibRmlUi.h"
#include "samples/sample.h"

ExampleEvent::ExampleEvent(const Rml::String &value) : value(value) {
}

void ExampleEvent::ProcessEvent(Rml::Event &event) {
    using namespace Rml;

    if (value == "exit") {
        Sample::runGame = false;
    }

    if (event == "keydown") {
        auto key_identifier = (Rml::Input::KeyIdentifier)event.GetParameter<int>("key_identifier", 0);

        if (key_identifier == Rml::Input::KI_SPACE) {
            Sample::runLoop = !Sample::runLoop;
        } else if (key_identifier == Rml::Input::KI_DOWN) {
            Sample::runLoop = false;
            Sample::singleLoop = true;
        } else if (key_identifier == Rml::Input::KI_RIGHT) {
            Sample::runUpdate = false;
            Sample::singleUpdate = true;
        } else if (key_identifier == Rml::Input::KI_RETURN) {
            Sample::runUpdate = !Sample::runUpdate;
        }
    }
}

void ExampleEvent::OnDetach(Rml::Element*) {
    delete this;
}