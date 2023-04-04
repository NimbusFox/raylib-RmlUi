#include "raylibSystemInterface.h"
#include "raylib.h"

double RaylibSystemInterface::GetElapsedTime() {
    return GetTime();
}

bool RaylibSystemInterface::LogMessage(Rml::Log::Type type, const Rml::String &message) {
    auto output = TextFormat("[RmlUi] %s", message.c_str());
    switch(type) {
        case Rml::Log::LT_ERROR:
            TraceLog(TraceLogLevel::LOG_ERROR, output);
            break;
        case Rml::Log::LT_ASSERT:
            TraceLog(TraceLogLevel::LOG_TRACE, output);
            break;
        case Rml::Log::LT_WARNING:
            TraceLog(TraceLogLevel::LOG_WARNING, output);
            break;
        case Rml::Log::LT_INFO:
            TraceLog(TraceLogLevel::LOG_INFO, output);
            break;
        case Rml::Log::LT_DEBUG:
            TraceLog(TraceLogLevel::LOG_DEBUG, output);
            break;
        case Rml::Log::LT_ALWAYS:
        case Rml::Log::LT_MAX:
            break;
    }

    return true;
}
