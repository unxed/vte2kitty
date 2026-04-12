#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <string.h>
#include "../source/kcon.h"

struct KeyDef {
    uint16_t vk;
    uint32_t ch;
    uint32_t shift_ch;
};

std::map<std::string, KeyDef> key_map;

void init_key_map() {
    for (char c = 'a'; c <= 'z'; ++c) {
        key_map[std::string(1, c)] = { (uint16_t)toupper(c), (uint32_t)c, (uint32_t)toupper(c) };
    }
    std::string numbers = "0123456789";
    std::string shift_nums = ")!@#$%^&*(";
    for (int i = 0; i < 10; ++i) {
        key_map[numbers.substr(i, 1)] = { (uint16_t)(0x30 + i), (uint32_t)numbers[i], (uint32_t)shift_nums[i] };
    }
    for (int i = 1; i <= 12; ++i) {
        key_map["F" + std::to_string(i)] = { (uint16_t)(0x70 + i - 1), 0, 0 };
    }
    key_map["Escape"] = { 0x1B, 0, 0 };
    key_map["Tab"] = { 0x09, '\t', '\t' };
    key_map["Return"] = { 0x0D, '\r', '\r' };
    key_map["BackSpace"] = { 0x08, '\x08', '\x08' };
    key_map["space"] = { 0x20, ' ', ' ' };

    key_map["Insert"] = { 0x2D, 0, 0 };
    key_map["Delete"] = { 0x2E, 0, 0 };
    key_map["Home"] = { 0x24, 0, 0 };
    key_map["End"] = { 0x23, 0, 0 };
    key_map["Page_Up"] = { 0x21, 0, 0 };
    key_map["Page_Down"] = { 0x22, 0, 0 };
    key_map["Up"] = { 0x26, 0, 0 };
    key_map["Down"] = { 0x28, 0, 0 };
    key_map["Left"] = { 0x25, 0, 0 };
    key_map["Right"] = { 0x27, 0, 0 };

    key_map["`"] = { 0xC0, '`', '~' };
    key_map["~"] = { 0xC0, '`', '~' };
    key_map["-"] = { 0xBD, '-', '_' };
    key_map["minus"] = { 0xBD, '-', '_' };
    key_map["_"] = { 0xBD, '-', '_' };
    key_map["="] = { 0xBB, '=', '+' };
    key_map["equal"] = { 0xBB, '=', '+' };
    key_map["+"] = { 0xBB, '=', '+' };
    key_map["["] = { 0xDB, '[', '{' };
    key_map["bracketleft"] = { 0xDB, '[', '{' };
    key_map["{"] = { 0xDB, '[', '{' };
    key_map["]"] = { 0xDD, ']', '}' };
    key_map["bracketright"] = { 0xDD, ']', '}' };
    key_map["}"] = { 0xDD, ']', '}' };
    key_map["\\"] = { 0xDC, '\\', '|' };
    key_map["backslash"] = { 0xDC, '\\', '|' };
    key_map["|"] = { 0xDC, '\\', '|' };
    key_map[";"] = { 0xBA, ';', ':' };
    key_map["semicolon"] = { 0xBA, ';', ':' };
    key_map[":"] = { 0xBA, ';', ':' };
    key_map["'"] = { 0xDE, '\'', '"' };
    key_map["apostrophe"] = { 0xDE, '\'', '"' };
    key_map["\""] = { 0xDE, '\'', '"' };
    key_map[","] = { 0xBC, ',', '<' };
    key_map["comma"] = { 0xBC, ',', '<' };
    key_map["<"] = { 0xBC, ',', '<' };
    key_map["."] = { 0xBE, '.', '>' };
    key_map["period"] = { 0xBE, '.', '>' };
    key_map[">"] = { 0xBE, '.', '>' };
    key_map["/"] = { 0xBF, '/', '?' };
    key_map["slash"] = { 0xBF, '/', '?' };
    key_map["?"] = { 0xBF, '/', '?' };

    key_map["KP_0"] = { 0x60, 0, 0 };
    key_map["KP_1"] = { 0x61, 0, 0 };
    key_map["KP_2"] = { 0x62, 0, 0 };
    key_map["KP_3"] = { 0x63, 0, 0 };
    key_map["KP_4"] = { 0x64, 0, 0 };
    key_map["KP_5"] = { 0x65, 0, 0 };
    key_map["KP_6"] = { 0x66, 0, 0 };
    key_map["KP_7"] = { 0x67, 0, 0 };
    key_map["KP_8"] = { 0x68, 0, 0 };
    key_map["KP_9"] = { 0x69, 0, 0 };
    key_map["KP_Decimal"] = { 0x6E, 0, 0 };
    key_map["KP_Divide"] = { 0x6F, '/', '/' };
    key_map["KP_Multiply"] = { 0x6A, '*', '*' };
    key_map["KP_Subtract"] = { 0x6D, '-', '-' };
    key_map["KP_Add"] = { 0x6B, '+', '+' };

    key_map["KP_Home"] = { 0x24, 0, 0 };
    key_map["KP_End"] = { 0x23, 0, 0 };
    key_map["KP_Page_Up"] = { 0x21, 0, 0 };
    key_map["KP_Page_Down"] = { 0x22, 0, 0 };
    key_map["KP_Up"] = { 0x26, 0, 0 };
    key_map["KP_Down"] = { 0x28, 0, 0 };
    key_map["KP_Left"] = { 0x25, 0, 0 };
    key_map["KP_Right"] = { 0x27, 0, 0 };
    key_map["KP_Begin"] = { 0x0C, 0, 0 };
    key_map["KP_Insert"] = { 0x2D, 0, 0 };
    key_map["KP_Delete"] = { 0x2E, 0, 0 };

    key_map["я"] = { 'Z', 0x044F, 0x042F };
}

int main(int argc, char** argv) {
    init_key_map();
    if (argc < 2) {
        std::cerr << "Usage: libkcon_tester --key <name> [mods...] [--kitty-flags N]" << std::endl;
        return 1;
    }

    std::string key_name;
    kcon_event_t ev;
    memset(&ev, 0, sizeof(ev));
    ev.is_down = true;
    ev.type = KCON_EVENT_PRESS;
    ev.repeat_count = 1;

    int kitty_flags = 0;
    bool is_num = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--key" && i + 1 < argc) key_name = argv[++i];
        else if (arg == "--shift") ev.control_state |= KCON_SHIFT_PRESSED;
        else if (arg == "--ctrl") ev.control_state |= KCON_LEFT_CTRL_PRESSED;
        else if (arg == "--alt") ev.control_state |= KCON_LEFT_ALT_PRESSED;
        else if (arg == "--super") ; // libkcon lacks super mapping, safely ignore
        else if (arg == "--caps") ev.control_state |= KCON_CAPSLOCK_ON;
        else if (arg == "--num") { ev.control_state |= KCON_NUMLOCK_ON; is_num = true; }
        else if (arg == "--kitty-flags" && i + 1 < argc) kitty_flags = std::stoi(argv[++i]);
        else if (arg == "--action" && i + 1 < argc) {
            std::string act = argv[++i];
            if (act == "release") { ev.is_down = false; ev.type = KCON_EVENT_RELEASE; }
            else if (act == "repeat") { ev.type = KCON_EVENT_REPEAT; }
        }
    }

    if (key_name.empty()) {
        std::cerr << "Error: --key missing" << std::endl;
        return 1;
    }

    if (key_name == "KP_Enter") {
        ev.vk = 0x0D;
        ev.unicode = '\r';
        ev.control_state |= KCON_ENHANCED_KEY;
    } else if (key_map.count(key_name)) {
        KeyDef def = key_map[key_name];
        ev.vk = def.vk;

        if (ev.vk == 0x2D || ev.vk == 0x2E || ev.vk == 0x24 || ev.vk == 0x23 ||
            ev.vk == 0x21 || ev.vk == 0x22 || ev.vk == 0x26 || ev.vk == 0x28 ||
            ev.vk == 0x25 || ev.vk == 0x27 || ev.vk == 0x6F) {
            if (key_name.rfind("KP_", 0) != 0) {
                ev.control_state |= KCON_ENHANCED_KEY;
            }
        }

        bool shift = (ev.control_state & KCON_SHIFT_PRESSED);
        bool ctrl = (ev.control_state & KCON_LEFT_CTRL_PRESSED);
        bool alt = (ev.control_state & KCON_LEFT_ALT_PRESSED);

        if (def.ch != 0) {
            bool isLetter = ev.vk >= 'A' && ev.vk <= 'Z';
            bool useShifted = isLetter ? (shift ^ ((ev.control_state & KCON_CAPSLOCK_ON) != 0)) : shift;
            uint32_t actual_char = useShifted ? def.shift_ch : def.ch;

            // Following kitty protocol: 'unicode' field represents the identity of the key (unshifted)
            ev.unicode = def.ch;

            bool has_mods_that_prevent_text = (ctrl || alt); // Simple emulation of OS text gen rule
            if (!has_mods_that_prevent_text) {
                ev.k_text = actual_char;
            }

            if (ctrl && isalpha(def.ch)) {
                ev.unicode = (uint32_t)(toupper(def.ch) - 'A' + 1);
            }

            uint32_t shifted_ch = def.shift_ch;
            if ((ev.control_state & KCON_CAPSLOCK_ON) && isLetter) {
                if (shifted_ch >= 'A' && shifted_ch <= 'Z') {
                    shifted_ch += 32;
                }
            }
            uint32_t unshifted_ch = def.ch;
            if (shifted_ch == unshifted_ch) {
                shifted_ch = 0;
            }
            ev.k_shifted = shifted_ch;
            ev.k_base = isLetter ? (uint32_t)tolower(ev.vk) : def.ch;
        }

        if (key_name.rfind("KP_", 0) == 0 && key_name.length() == 4 && isdigit(key_name[3])) {
            if (is_num) {
                ev.unicode = key_name[3];
                ev.k_text = key_name[3];
            } else {
                ev.unicode = 0;
            }
        }
    } else {
        std::cerr << "Error: Unknown key " << key_name << std::endl;
        return 1;
    }

    char buf[256];
    size_t len = kcon_write_kitty(&ev, kitty_flags, buf, sizeof(buf));
    if (len > 0) {
        std::cout.write(buf, len);
    } else {
        std::cout << "[EMPTY]";
    }

    return 0;
}