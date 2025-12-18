#pragma once

#include <cstdint>
#include <string>
#include <cwchar>
#include <cwctype>
#include <cctype>
#include <vector>
#include <cstring>
#include <cstdio>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef wchar_t WCHAR;
typedef char CHAR;

typedef union _uCharUnion {
    WCHAR UnicodeChar;
    CHAR  AsciiChar;
} uCharUnion;

typedef struct _KEY_EVENT_RECORD {
    int bKeyDown;
    WORD wRepeatCount;
    WORD wVirtualKeyCode;
    WORD wVirtualScanCode;
    uCharUnion uChar;
    DWORD dwControlKeyState;
} KEY_EVENT_RECORD;

#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04
#define VK_BACK           0x08
#define VK_TAB            0x09
#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12 // Alt
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14 // Caps Lock
#define VK_ESCAPE         0x1B
#define VK_SPACE          0x20
#define VK_PRIOR          0x21 // Page Up
#define VK_NEXT           0x22 // Page Down
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C // Print Screen
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

// Digits 0-9 are 0x30 - 0x39
// Letters A-Z are 0x41 - 0x5A

#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D
#define VK_SLEEP          0x5F

#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F

#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B

#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5

// OEM specific keys
#define VK_OEM_1          0xBA
#define VK_OEM_PLUS       0xBB
#define VK_OEM_COMMA      0xBC
#define VK_OEM_MINUS      0xBD
#define VK_OEM_PERIOD     0xBE
#define VK_OEM_2          0xBF
#define VK_OEM_3          0xC0
#define VK_OEM_4          0xDB
#define VK_OEM_5          0xDC
#define VK_OEM_6          0xDD
#define VK_OEM_7          0xDE
#define VK_OEM_8          0xDF

#define VK_NONAME         0xFC

#define RIGHT_ALT_PRESSED   0x0001
#define LEFT_ALT_PRESSED    0x0002
#define RIGHT_CTRL_PRESSED  0x0004
#define LEFT_CTRL_PRESSED   0x0008
#define SHIFT_PRESSED       0x0010
#define NUMLOCK_ON          0x0020
#define SCROLLLOCK_ON       0x0040
#define CAPSLOCK_ON         0x0080
#define ENHANCED_KEY        0x0100

#define RIGHT_SHIFT_VSC     0x36

static inline std::string Wide2MB(const WCHAR* wstr) {
    if (!wstr || !*wstr) return "";
    std::string out;
    if (*wstr < 0x80) {
        out.push_back((char)*wstr);
    } else {
        out.push_back('?');
    }
    return out;
}

// Full mock of legacy key translation
static inline const char* VT_TranslateSpecialKey(WORD vk, bool ctrl, bool alt, bool shift, unsigned char /*keypad*/, WCHAR) {
    static char buf[64];
    
    int mod = 1;
    if (shift) mod += 1;
    if (alt)   mod += 2;
    if (ctrl)  mod += 4;

    const char* csi = "\x1b[";
    const char* ss3 = "\x1bO";

    switch (vk) {
        case VK_BACK:   return "\x7f";
        case VK_TAB:    return (shift && !ctrl && !alt) ? "\x1b[Z" : "\t";
        case VK_RETURN: return "\r";
        case VK_ESCAPE: return "\x1b";
        
        case VK_UP:
        case VK_DOWN:
        case VK_RIGHT:
        case VK_LEFT: {
            char suffix;
            if (vk == VK_UP) suffix = 'A';
            else if (vk == VK_DOWN) suffix = 'B';
            else if (vk == VK_RIGHT) suffix = 'C';
            else suffix = 'D';

            if (mod == 1) snprintf(buf, sizeof(buf), "%s%c", csi, suffix);
            else snprintf(buf, sizeof(buf), "%s1;%d%c", csi, mod, suffix);
            return buf;
        }

        case VK_HOME:
        case VK_END: {
            char suffix = (vk == VK_HOME) ? 'H' : 'F';
            if (mod == 1) snprintf(buf, sizeof(buf), "%s%c", csi, suffix);
            else snprintf(buf, sizeof(buf), "%s1;%d%c", csi, mod, suffix);
            return buf;
        }

        case VK_INSERT:
        case VK_DELETE:
        case VK_PRIOR:
        case VK_NEXT:
        {
            int code;
            if (vk == VK_INSERT) code = 2;
            else if (vk == VK_DELETE) code = 3;
            else if (vk == VK_PRIOR) code = 5;
            else code = 6;
            
            if (mod == 1) snprintf(buf, sizeof(buf), "%s%d~", csi, code);
            else snprintf(buf, sizeof(buf), "%s%d;%d~", csi, code, mod);
            return buf;
        }

        case VK_F1:
        case VK_F2:
        case VK_F3:
        case VK_F4: {
            char suffix = 'P' + (vk - VK_F1);
            if (mod == 1) snprintf(buf, sizeof(buf), "%s%c", ss3, suffix);
            else snprintf(buf, sizeof(buf), "%s1;%d%c", csi, mod, suffix);
            return buf;
        }

        case VK_F5:
        case VK_F6:
        case VK_F7:
        case VK_F8:
        case VK_F9:
        case VK_F10:
        case VK_F11:
        case VK_F12: {
            int code;
            if (vk <= VK_F5) code = 15;
            else if (vk <= VK_F8) code = 17 + (vk - VK_F6);
            else if (vk <= VK_F10) code = 20 + (vk - VK_F9);
            else code = 23 + (vk - VK_F11);

            if (mod == 1) snprintf(buf, sizeof(buf), "%s%d~", csi, code);
            else snprintf(buf, sizeof(buf), "%s%d;%d~", csi, code, mod);
            return buf;
        }
    }
    return nullptr;
}