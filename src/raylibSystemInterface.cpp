#include "raylibSystemInterface.h"
#include "raylib.h"
#include <map>

static std::map<KeyboardKey, Rml::Input::KeyIdentifier> keyMap;

bool initialized = false;

void Initialize() {
    if (initialized) {
        return;
    }

    initialized = true;

    //keyMap.emplace(KEY_COMMA, Rml::Input::KI_OEM_COMMA);

    keyMap[KEY_COMMA] = Rml::Input::KI_OEM_COMMA;
    keyMap[KEY_APOSTROPHE] = Rml::Input::KI_OEM_7;
    keyMap[KEY_MINUS] = Rml::Input::KI_OEM_MINUS;
    keyMap[KEY_PERIOD] = Rml::Input::KI_OEM_PERIOD;
    keyMap[KEY_SLASH] = Rml::Input::KI_OEM_2;
    keyMap[KEY_ZERO] = Rml::Input::KI_0;
    keyMap[KEY_ONE] = Rml::Input::KI_1;
    keyMap[KEY_TWO] = Rml::Input::KI_2;
    keyMap[KEY_THREE] = Rml::Input::KI_3;
    keyMap[KEY_FOUR] = Rml::Input::KI_4;
    keyMap[KEY_FIVE] = Rml::Input::KI_5;
    keyMap[KEY_SIX] = Rml::Input::KI_6;
    keyMap[KEY_SEVEN] = Rml::Input::KI_7;
    keyMap[KEY_EIGHT] = Rml::Input::KI_8;
    keyMap[KEY_NINE] = Rml::Input::KI_9;
    keyMap[KEY_SEMICOLON] = Rml::Input::KI_OEM_1;
    keyMap[KEY_EQUAL] = Rml::Input::KI_OEM_PLUS;
    keyMap[KEY_A] = Rml::Input::KI_A;
    keyMap[KEY_B] = Rml::Input::KI_B;
    keyMap[KEY_C] = Rml::Input::KI_C;
    keyMap[KEY_D] = Rml::Input::KI_D;
    keyMap[KEY_E] = Rml::Input::KI_E;
    keyMap[KEY_F] = Rml::Input::KI_F;
    keyMap[KEY_G] = Rml::Input::KI_G;
    keyMap[KEY_H] = Rml::Input::KI_H;
    keyMap[KEY_I] = Rml::Input::KI_I;
    keyMap[KEY_J] = Rml::Input::KI_J;
    keyMap[KEY_K] = Rml::Input::KI_K;
    keyMap[KEY_L] = Rml::Input::KI_L;
    keyMap[KEY_M] = Rml::Input::KI_M;
    keyMap[KEY_N] = Rml::Input::KI_N;
    keyMap[KEY_O] = Rml::Input::KI_O;
    keyMap[KEY_P] = Rml::Input::KI_P;
    keyMap[KEY_Q] = Rml::Input::KI_Q;
    keyMap[KEY_R] = Rml::Input::KI_R;
    keyMap[KEY_S] = Rml::Input::KI_S;
    keyMap[KEY_T] = Rml::Input::KI_T;
    keyMap[KEY_U] = Rml::Input::KI_U;
    keyMap[KEY_V] = Rml::Input::KI_V;
    keyMap[KEY_W] = Rml::Input::KI_W;
    keyMap[KEY_X] = Rml::Input::KI_X;
    keyMap[KEY_Y] = Rml::Input::KI_Y;
    keyMap[KEY_Z] = Rml::Input::KI_Z;
    keyMap[KEY_LEFT_BRACKET] = Rml::Input::KI_OEM_4;
    keyMap[KEY_BACKSLASH] = Rml::Input::KI_OEM_5;
    keyMap[KEY_RIGHT_BRACKET] = Rml::Input::KI_OEM_6;
    keyMap[KEY_GRAVE] = Rml::Input::KI_OEM_3;
    keyMap[KEY_SPACE] = Rml::Input::KI_SPACE;
    keyMap[KEY_ESCAPE] = Rml::Input::KI_ESCAPE;
    keyMap[KEY_ENTER] = Rml::Input::KI_RETURN;
    keyMap[KEY_TAB] = Rml::Input::KI_TAB;
    keyMap[KEY_BACKSPACE] = Rml::Input::KI_BACK;
    keyMap[KEY_INSERT] = Rml::Input::KI_INSERT;
    keyMap[KEY_DELETE] = Rml::Input::KI_DELETE;
    keyMap[KEY_RIGHT] = Rml::Input::KI_RIGHT;
    keyMap[KEY_LEFT] = Rml::Input::KI_LEFT;
    keyMap[KEY_DOWN] = Rml::Input::KI_DOWN;
    keyMap[KEY_UP] = Rml::Input::KI_UP;
    keyMap[KEY_PAGE_UP] = Rml::Input::KI_PRIOR;
    keyMap[KEY_PAGE_DOWN] = Rml::Input::KI_NEXT;
    keyMap[KEY_HOME] = Rml::Input::KI_HOME;
    keyMap[KEY_END] = Rml::Input::KI_END;
    keyMap[KEY_CAPS_LOCK] = Rml::Input::KI_CAPITAL;
    keyMap[KEY_SCROLL_LOCK] = Rml::Input::KI_SCROLL;
    keyMap[KEY_NUM_LOCK] = Rml::Input::KI_NUMLOCK;
    keyMap[KEY_PRINT_SCREEN] = Rml::Input::KI_PRINT;
    keyMap[KEY_PAUSE] = Rml::Input::KI_PAUSE;
    keyMap[KEY_F1] = Rml::Input::KI_F1;
    keyMap[KEY_F2] = Rml::Input::KI_F2;
    keyMap[KEY_F3] = Rml::Input::KI_F3;
    keyMap[KEY_F4] = Rml::Input::KI_F4;
    keyMap[KEY_F5] = Rml::Input::KI_F5;
    keyMap[KEY_F6] = Rml::Input::KI_F6;
    keyMap[KEY_F7] = Rml::Input::KI_F7;
    keyMap[KEY_F8] = Rml::Input::KI_F8;
    keyMap[KEY_F9] = Rml::Input::KI_F9;
    keyMap[KEY_F10] = Rml::Input::KI_F10;
    keyMap[KEY_F11] = Rml::Input::KI_F11;
    keyMap[KEY_F12] = Rml::Input::KI_F12;
    keyMap[KEY_LEFT_SHIFT] = Rml::Input::KI_LSHIFT;
    keyMap[KEY_LEFT_CONTROL] = Rml::Input::KI_LCONTROL;
    keyMap[KEY_LEFT_ALT] = Rml::Input::KI_LMETA;
    keyMap[KEY_LEFT_SUPER] = Rml::Input::KI_LWIN;
    keyMap[KEY_RIGHT_SHIFT] = Rml::Input::KI_RSHIFT;
    keyMap[KEY_RIGHT_CONTROL] = Rml::Input::KI_RCONTROL;
    keyMap[KEY_RIGHT_ALT] = Rml::Input::KI_RMETA;
    keyMap[KEY_RIGHT_SUPER] = Rml::Input::KI_RWIN;
    keyMap[KEY_KB_MENU] = Rml::Input::KI_RMENU;
    keyMap[KEY_KP_0] = Rml::Input::KI_NUMPAD0;
    keyMap[KEY_KP_1] = Rml::Input::KI_NUMPAD1;
    keyMap[KEY_KP_2] = Rml::Input::KI_NUMPAD2;
    keyMap[KEY_KP_3] = Rml::Input::KI_NUMPAD3;
    keyMap[KEY_KP_4] = Rml::Input::KI_NUMPAD4;
    keyMap[KEY_KP_5] = Rml::Input::KI_NUMPAD5;
    keyMap[KEY_KP_6] = Rml::Input::KI_NUMPAD6;
    keyMap[KEY_KP_7] = Rml::Input::KI_NUMPAD7;
    keyMap[KEY_KP_8] = Rml::Input::KI_NUMPAD8;
    keyMap[KEY_KP_9] = Rml::Input::KI_NUMPAD9;
    keyMap[KEY_KP_DECIMAL] = Rml::Input::KI_DECIMAL;
    keyMap[KEY_KP_DIVIDE] = Rml::Input::KI_DIVIDE;
    keyMap[KEY_KP_MULTIPLY] = Rml::Input::KI_MULTIPLY;
    keyMap[KEY_KP_SUBTRACT] = Rml::Input::KI_SUBTRACT;
    keyMap[KEY_KP_ADD] = Rml::Input::KI_ADD;
    keyMap[KEY_KP_ENTER] = Rml::Input::KI_RETURN;
    keyMap[KEY_KP_EQUAL] = Rml::Input::KI_RETURN;
    keyMap[KEY_VOLUME_UP] = Rml::Input::KI_VOLUME_UP;
    keyMap[KEY_VOLUME_DOWN] = Rml::Input::KI_VOLUME_DOWN;
}

double RaylibSystemInterface::GetElapsedTime() {
    return GetTime();
}

bool RaylibSystemInterface::LogMessage(Rml::Log::Type type, const Rml::String &message) {
    auto output = TextFormat("[RmlUi] %s", message.c_str());
    switch (type) {
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

Rml::Input::KeyIdentifier RaylibSystemInterface::ConvertKey(KeyboardKey key) {
    if (keyMap.contains(key)) {
        return keyMap[key];
    }

    return Rml::Input::KI_UNKNOWN;
}

void RaylibSystemInterface::HandleKeyboardEvents(Rml::Context* context) {
    Initialize();
    for (auto &key: keyMap) {
        if (IsKeyDown(key.first)) {
            context->ProcessKeyDown(key.second, 0);
            continue;
        }

        if (IsKeyUp(key.first)) {
            context->ProcessKeyUp(key.second, 0);
        }
    }
}

RaylibSystemInterface::RaylibSystemInterface() : Rml::SystemInterface() {
}
