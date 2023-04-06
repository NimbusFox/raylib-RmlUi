#ifndef RMLUI_EXAMPLE_EVENT_H
#define RMLUI_EXAMPLE_EVENT_H

#include "RmlUi/Core.h"

class ExampleEvent : public Rml::EventListener {
public:
    void ProcessEvent(Rml::Event &event) override;

    void OnDetach(Rml::Element* /*element*/) override;

    explicit ExampleEvent(const Rml::String &value);

private:
    Rml::String value;
};

class ExampleEventInstancer : public Rml::EventListenerInstancer {
public:
    Rml::EventListener* InstanceEventListener(const Rml::String &value, Rml::Element* /*element*/) override {
        return new ExampleEvent(value);
    }
};

#endif //RMLUI_EXAMPLE_EVENT_H
