#include "samples/basic/databinding/eventsExample.h"
#include <numeric>

namespace EventsExample {

    Rml::DataModelHandle model_handle;
    int previousRating = 0;

    struct MyData {
        Rml::String hello_world = "Hello World!";
        Rml::String mouse_detector = "Mouse-move <em>Detector</em>.";
        int rating = 99;

        Rml::Vector<float> list = { 1, 2, 3, 4, 5 };

        Rml::Vector<Rml::Vector2f> positions;

        void AddMousePos(Rml::DataModelHandle model, Rml::Event &ev, const Rml::VariantList & /*arguments*/) {
            positions.emplace_back(ev.GetParameter("mouse_x", 0.f), ev.GetParameter("mouse_y", 0.f));
            model.DirtyVariable("positions");
        }

    } my_data;


    void ClearPositions(Rml::DataModelHandle model, Rml::Event &ev, const Rml::VariantList &arguments) {
        my_data.positions.clear();
        model.DirtyVariable("positions");
    }

    void HasGoodRating(Rml::Variant &variant) {
        variant = int(my_data.rating > 50);
    }

    bool Initialize(Rml::Context* context) {
        using namespace Rml;
        DataModelConstructor constructor = context->CreateDataModel("events");
        if (!constructor)
            return false;

        // Register all the types first
        constructor.RegisterArray<Rml::Vector<float>>();

        if (auto vec2_handle = constructor.RegisterStruct<Vector2f>()) {
            vec2_handle.RegisterMember("x", &Vector2f::x);
            vec2_handle.RegisterMember("y", &Vector2f::y);
        }
        constructor.RegisterArray<Rml::Vector<Vector2f>>();

        // Bind the variables to the data model
        constructor.Bind("hello_world", &my_data.hello_world);
        constructor.Bind("mouse_detector", &my_data.mouse_detector);
        constructor.Bind("rating", &my_data.rating);
        constructor.BindFunc("good_rating", &HasGoodRating);
        constructor.BindFunc("great_rating", [](Variant &variant) {
            variant = int(my_data.rating > 80);
        });

        constructor.Bind("list", &my_data.list);

        constructor.Bind("positions", &my_data.positions);

        constructor.BindEventCallback("clear_positions", &ClearPositions);
        constructor.BindEventCallback("add_mouse_pos", &MyData::AddMousePos, &my_data);

        model_handle = constructor.GetModelHandle();

        return true;
    }

    void Update() {
        if (previousRating != my_data.rating) {
            previousRating = my_data.rating;
            model_handle.DirtyVariable("good_rating");
            model_handle.DirtyVariable("great_rating");

            size_t new_size = my_data.rating / 10 + 1;
            if (new_size != my_data.list.size()) {
                my_data.list.resize(new_size);
                std::iota(my_data.list.begin(), my_data.list.end(), float(new_size));
                model_handle.DirtyVariable("list");
            }
        }
    }
}