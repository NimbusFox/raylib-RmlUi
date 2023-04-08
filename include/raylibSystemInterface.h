#ifndef RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H
#define RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include "raylib.h"

class RaylibSystemInterface : public Rml::SystemInterface {
public:
    double GetElapsedTime() override;

    bool LogMessage(Rml::Log::Type type, const Rml::String &message) override;

    Rml::Input::KeyIdentifier ConvertKey(KeyboardKey key);

    int ConvertKeyModifiers();

    void HandleKeyboardEvents(Rml::Context* context);

    void HandleMouseEvents(Rml::Context* context);

    void GetClipboardText(Rml::String &text) override;

    void SetClipboardText(const Rml::String &text) override;

    void SetMouseCursor(const Rml::String &cursor_name) override;
};

#endif //RMLUI_EXAMPLE_RAYLIBSYSTEMINTERFACE_H
