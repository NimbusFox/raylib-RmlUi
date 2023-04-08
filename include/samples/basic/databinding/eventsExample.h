#ifndef RMLUI_EXAMPLE_EVENTSEXAMPLE_H
#define RMLUI_EXAMPLE_EVENTSEXAMPLE_H

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

namespace EventsExample {
    void ClearPositions(Rml::DataModelHandle model, Rml::Event & ev, const Rml::VariantList & arguments);

    void HasGoodRating(Rml::Variant &variant);

    bool Initialize(Rml::Context* context);

    void Update();
}
#endif //RMLUI_EXAMPLE_EVENTSEXAMPLE_H
