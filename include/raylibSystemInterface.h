#ifndef RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H
#define RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

class RaylibSystemInterface : public Rml::SystemInterface {
public:
double GetElapsedTime() override;

bool LogMessage(Rml::Log::Type type, const Rml::String &message) override;
};

#endif //RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H
