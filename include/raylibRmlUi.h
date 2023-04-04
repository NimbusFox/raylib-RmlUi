#ifndef RMLUI_EXAMPLE_RAYLIBRMLUI_H
#define RMLUI_EXAMPLE_RAYLIBRMLUI_H

class RaylibRmlUi {
private:
public:
static bool Initialize(int windowWidth, int windowHeight);

static void DeInitialize();

static void EnableDebugger();

static void DisableDebugger();

static void ToggleDebugger();

static void Update();

static void Draw();
};

#endif //RMLUI_EXAMPLE_RAYLIBRMLUI_H
