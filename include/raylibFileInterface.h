#ifndef RMLUI_EXAMPLE_RAYLIBFILEINTERFACE_H
#define RMLUI_EXAMPLE_RAYLIBFILEINTERFACE_H

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>

class RaylibFileInterface : public Rml::FileInterface {
public:
Rml::FileHandle Open(const Rml::String &path) override;
void Close(Rml::FileHandle file) override;
size_t Read(void *buffer, std::size_t size, Rml::FileHandle file) override;
bool Seek(Rml::FileHandle file, long offset, int origin) override;
size_t Tell(Rml::FileHandle file) override;

static std::string ParsePath(const std::string &path);
};

#endif //RMLUI_EXAMPLE_RAYLIBFILEINTERFACE_H
