#ifndef RMLUI_EXAMPLE_RAYLIBRMLUI_H
#define RMLUI_EXAMPLE_RAYLIBRMLUI_H

#include "RmlUi/Core.h"

class RaylibRmlUi {
private:
public:
    static Rml::Context* Context;

    static bool Initialize(int windowWidth, int windowHeight);

    static void LoadFont(const char* path);

    static void DeInitialize();

    static void EnableDebugger();

    static void DisableDebugger();

    static void ToggleDebugger();

    static void LoadRml(const char* path, const char* id, bool show = false);

    static void ShowPage(const char* id);

    static void Update();

    static void Draw();

    static Rml::ElementDocument* GetPage(const char* id);
};

#endif //RMLUI_EXAMPLE_RAYLIBRMLUI_H
