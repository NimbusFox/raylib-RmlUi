#include "samples/basic/databinding/formsExample.h"
#include "RmlUi/Core/DataModelHandle.h"

Rml::DataModelHandle model_handle;

struct MyData {
    int rating = 50;
    bool pizza = true;
    bool pasta = false;
    bool lasagne = false;
    Rml::String animal = "dog";
    Rml::Vector<Rml::String> subjects = { "Choose your subject", "Feature request", "Bug report", "Praise", "Criticism" };
    int selected_subject = 0;
    Rml::String new_subject = "New subject";
} my_data;

bool FormsExample::Initialize(Rml::Context* context) {
    Rml::DataModelConstructor constructor = context->CreateDataModel("forms");
    if (!constructor)
        return false;

    constructor.RegisterArray<Rml::Vector<Rml::String>>();

    constructor.Bind("rating", &my_data.rating);
    constructor.Bind("pizza", &my_data.pizza);
    constructor.Bind("pasta", &my_data.pasta);
    constructor.Bind("lasagne", &my_data.lasagne);
    constructor.Bind("animal", &my_data.animal);
    constructor.Bind("subjects", &my_data.subjects);
    constructor.Bind("selected_subject", &my_data.selected_subject);
    constructor.Bind("new_subject", &my_data.new_subject);

    constructor.BindEventCallback("add_subject", [](Rml::DataModelHandle model, Rml::Event & /*ev*/, const Rml::VariantList &arguments) {
        Rml::String name = (arguments.size() == 1 ? arguments[0].Get<Rml::String>() : "");
        if (!name.empty()) {
            my_data.subjects.push_back(std::move(name));
            model.DirtyVariable("subjects");
        }
    });
    constructor.BindEventCallback("erase_subject", [](Rml::DataModelHandle model, Rml::Event & /*ev*/, const Rml::VariantList &arguments) {
        const int i = (arguments.size() == 1 ? arguments[0].Get<int>(-1) : -1);
        if (i >= 0 && i < (int)my_data.subjects.size()) {
            my_data.subjects.erase(my_data.subjects.begin() + i);
            my_data.selected_subject = 0;
            model.DirtyVariable("subjects");
            model.DirtyVariable("selected_subject");
        }
    });

    model_handle = constructor.GetModelHandle();

    return true;
}
