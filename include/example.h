#ifndef RMLUI_EXAMPLE_EXAMPLE_H
#define RMLUI_EXAMPLE_EXAMPLE_H

#include "RmlUi/Core/Types.h"

namespace Example {
    const char* GetWindowTitle();
    Rml::Vector2i GetWindowSize();
    void Initialize();
    void DeInitialize();

    void Update(float delta);
    void Render();
    void ToggleDebugger();
    bool RunProgram();
    void StopProgram();
}
#endif //RMLUI_EXAMPLE_EXAMPLE_H
