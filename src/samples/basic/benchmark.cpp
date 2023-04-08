#include "example.h"
#include "raylibRmlUi.h"
#include "samples/sample.h"
#include "samples/event.h"

Rml::ElementDocument* document;

Rml::Vector2i Example::GetWindowSize() {
    return Rml::Vector2i{ 1800, 1000 };
}

void Example::Initialize() {
    Sample::runGame = RaylibRmlUi::Initialize(1800, 1000);

    if (!Sample::runGame) {
        return;
    }

    RaylibRmlUi::LoadFont("LatoLatin-Bold.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-BoldItalic.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-Italic.ttf");
    RaylibRmlUi::LoadFont("LatoLatin-Regular.ttf");
    RaylibRmlUi::LoadFont("NotoEmoji-Regular.ttf");

    ExampleEventInstancer eventListenerInstancer;
    Rml::Factory::RegisterEventListenerInstancer(&eventListenerInstancer);

    RaylibRmlUi::LoadRml("samples/basic/benchmark.rml", "benchmark", true);

    document = RaylibRmlUi::GetPage("benchmark");

    document->GetElementById("title")->SetInnerRML("Benchmark");
}

void Example::DeInitialize() {
    RaylibRmlUi::DeInitialize();
}

const char* Example::GetWindowTitle() {
    return "- Benchmark";
}

void Example::ToggleDebugger() {
    RaylibRmlUi::ToggleDebugger();
}

void Example::Update(float delta) {


    if (Sample::runUpdate || Sample::singleUpdate) {
        Sample::singleUpdate = false;

        RMLUI_ZoneScoped;

        if (!document)
            return;

        Rml::String rml;

        for (int i = 0 ; i < 50 ; i++) {
            int index = rand() % 1000;
            int route = rand() % 50;
            int max = (rand() % 40) + 10;
            int value = rand() % max;
            Rml::String rml_row = Rml::CreateString(1000, R"(
			<div class="row">
				<div class="col col1"><button class="expand" index="%d">+</button>&nbsp;<a>Route %d</a></div>
				<div class="col col23"><input type="range" class="assign_range" min="0" max="%d" value="%d"/></div>
				<div class="col col4">Assigned</div>
				<select>
					<option>Red</option><option>Blue</option><option selected>Green</option><option style="background-color: yellow;">Yellow</option>
				</select>
				<div class="inrow unmark_collapse">
					<div class="col col123 assign_text">Assign to route</div>
					<div class="col col4">
						<input type="submit" class="vehicle_depot_assign_confirm" quantity="0">Confirm</input>
					</div>
				</div>
			</div>)",
                    index,
                    route,
                    max,
                    value
            );
            rml += rml_row;
        }

        if (auto el = document->GetElementById("performance"))
            el->SetInnerRML(rml);
    }

    static constexpr int buffer_size = 200;
    static float fps_buffer[buffer_size] = {};
    static int buffer_index = 0;

    static double t_prev = 0.0f;
    double t = Rml::GetSystemInterface()->GetElapsedTime();
    float dt = float(t - t_prev);
    t_prev = t;
    static int count_frames = 0;
    count_frames += 1;

    float fps = 1.0f / dt;
    fps_buffer[buffer_index] = fps;
    buffer_index = ((buffer_index + 1) % buffer_size);

    if (count_frames > buffer_size / 8) {
        float fps_mean = 0;
        for (int i = 0 ; i < buffer_size ; i++)
            fps_mean += fps_buffer[(buffer_index + i) % buffer_size];
        fps_mean = fps_mean / (float)buffer_size;

        auto el = document->GetElementById("fps");
        count_frames = 0;
        el->SetInnerRML(Rml::CreateString(20, "FPS: %f", fps_mean));
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