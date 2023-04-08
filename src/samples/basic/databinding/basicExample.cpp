#include "samples/basic/databinding/basicExample.h"

namespace BasicExample {
    struct MyData {
        Rml::String title = "Simple data binding example";
        Rml::String animal = "dog";
        bool show_text = true;
    } my_data;

    Rml::DataModelHandle model_handle;

    bool Initialize(Rml::Context* context) {
        Rml::DataModelConstructor constructor = context->CreateDataModel("basics");
        if (!constructor)
            return false;

        constructor.Bind("title", &my_data.title);
        constructor.Bind("animal", &my_data.animal);
        constructor.Bind("show_text", &my_data.show_text);

        model_handle = constructor.GetModelHandle();

        return true;
    }
}