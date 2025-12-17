#include "kitty_mocks.h"

#include "kitty_encoder_body.inc"

#include <string.h>
#include <ctype.h>

int get_key_code(const char* name) {
    if (strlen(name) == 1 && isprint(name[0])) return (int)name[0];
    
    if (strcmp(name, "Escape") == 0) return GLFW_FKEY_ESCAPE;
    if (strcmp(name, "Enter") == 0) return GLFW_FKEY_ENTER;
    if (strcmp(name, "Return") == 0) return GLFW_FKEY_ENTER; // Alias
    if (strcmp(name, "Tab") == 0) return GLFW_FKEY_TAB;
    if (strcmp(name, "BackSpace") == 0) return GLFW_FKEY_BACKSPACE;
    if (strcmp(name, "Insert") == 0) return GLFW_FKEY_INSERT;
    if (strcmp(name, "Delete") == 0) return GLFW_FKEY_DELETE;
    if (strcmp(name, "Left") == 0) return GLFW_FKEY_LEFT;
    if (strcmp(name, "Right") == 0) return GLFW_FKEY_RIGHT;
    if (strcmp(name, "Up") == 0) return GLFW_FKEY_UP;
    if (strcmp(name, "Down") == 0) return GLFW_FKEY_DOWN;
    if (strcmp(name, "Page_Up") == 0) return GLFW_FKEY_PAGE_UP;
    if (strcmp(name, "Page_Down") == 0) return GLFW_FKEY_PAGE_DOWN;
    if (strcmp(name, "Home") == 0) return GLFW_FKEY_HOME;
    if (strcmp(name, "End") == 0) return GLFW_FKEY_END;
    
    if (strcmp(name, "F1") == 0) return GLFW_FKEY_F1;
    if (strcmp(name, "F2") == 0) return GLFW_FKEY_F2;
    if (strcmp(name, "F3") == 0) return GLFW_FKEY_F3;
    if (strcmp(name, "F4") == 0) return GLFW_FKEY_F4;
    if (strcmp(name, "F5") == 0) return GLFW_FKEY_F5;
    if (strcmp(name, "F6") == 0) return GLFW_FKEY_F6;
    if (strcmp(name, "F7") == 0) return GLFW_FKEY_F7;
    if (strcmp(name, "F8") == 0) return GLFW_FKEY_F8;
    if (strcmp(name, "F9") == 0) return GLFW_FKEY_F9;
    if (strcmp(name, "F10") == 0) return GLFW_FKEY_F10;
    if (strcmp(name, "F11") == 0) return GLFW_FKEY_F11;
    if (strcmp(name, "F12") == 0) return GLFW_FKEY_F12;

    if (strcmp(name, "KP_0") == 0) return GLFW_FKEY_KP_0;
    if (strcmp(name, "KP_5") == 0) return GLFW_FKEY_KP_5;
    if (strcmp(name, "KP_9") == 0) return GLFW_FKEY_KP_9;
    
    if (strcmp(name, "KP_Home") == 0) return GLFW_FKEY_KP_HOME;
    if (strcmp(name, "KP_End") == 0) return GLFW_FKEY_KP_END;
    if (strcmp(name, "KP_Up") == 0) return GLFW_FKEY_KP_UP;
    if (strcmp(name, "KP_Down") == 0) return GLFW_FKEY_KP_DOWN;
    if (strcmp(name, "KP_Left") == 0) return GLFW_FKEY_KP_LEFT;
    if (strcmp(name, "KP_Right") == 0) return GLFW_FKEY_KP_RIGHT;
    if (strcmp(name, "KP_Page_Up") == 0) return GLFW_FKEY_KP_PAGE_UP;
    if (strcmp(name, "KP_Page_Down") == 0) return GLFW_FKEY_KP_PAGE_DOWN;
    if (strcmp(name, "KP_Insert") == 0) return GLFW_FKEY_KP_INSERT;
    if (strcmp(name, "KP_Delete") == 0) return GLFW_FKEY_KP_DELETE;
    if (strcmp(name, "KP_Begin") == 0) return GLFW_FKEY_KP_BEGIN;
    
    if (strcmp(name, "space") == 0) return ' ';
    
    fprintf(stderr, "Warning: Unknown key name '%s', returning 0.\n", name);
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s --key <Name> [--shift] [--ctrl] [--alt] [--super] [--caps] [--num] [--kitty-flags <int>] [--action <press|release|repeat>] [--cursor-key-mode]\n", argv[0]);
        return 1;
    }

    GLFWkeyevent ev;
    memset(&ev, 0, sizeof(ev));
    ev.action = GLFW_PRESS; // Default
    
    unsigned int kitty_flags = 0;
    bool cursor_key_mode = false;
    bool has_mods_that_prevent_text = false;

    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];
        if (strcmp(arg, "--key") == 0 && i + 1 < argc) {
            ev.key = get_key_code(argv[++i]);
        }
        else if (strcmp(arg, "--shift") == 0) ev.mods |= GLFW_MOD_SHIFT;
        else if (strcmp(arg, "--ctrl") == 0) { ev.mods |= GLFW_MOD_CONTROL; has_mods_that_prevent_text = true; }
        else if (strcmp(arg, "--alt") == 0) { ev.mods |= GLFW_MOD_ALT; has_mods_that_prevent_text = true; }
        else if (strcmp(arg, "--super") == 0) { ev.mods |= GLFW_MOD_SUPER; has_mods_that_prevent_text = true; }
        else if (strcmp(arg, "--caps") == 0) ev.mods |= GLFW_MOD_CAPS_LOCK;
        else if (strcmp(arg, "--num") == 0) ev.mods |= GLFW_MOD_NUM_LOCK;
        else if (strcmp(arg, "--action") == 0 && i + 1 < argc) {
            const char* action_str = argv[++i];
            if (strcmp(action_str, "release") == 0) ev.action = GLFW_RELEASE;
            else if (strcmp(action_str, "repeat") == 0) ev.action = GLFW_REPEAT;
            else ev.action = GLFW_PRESS;
        }
        else if (strcmp(arg, "--kitty-flags") == 0 && i + 1 < argc) {
            kitty_flags = atoi(argv[++i]);
        }
        else if (strcmp(arg, "--cursor-key-mode") == 0) {
            cursor_key_mode = true;
        }
    }
    
    // Minimal emulation of ev.text and ev.shifted_key to match kitty behavior.
    // When Ctrl/Alt/Super are pressed, ev.text must be NULL to force CSI-u output.
    if (ev.key >= 'a' && ev.key <= 'z') {
        static char text_buf[2] = {0};
        
        if (ev.mods & GLFW_MOD_SHIFT) {
            ev.shifted_key = ev.key - 32; // 'A'
            text_buf[0] = (char)ev.shifted_key;
        } else {
            ev.shifted_key = 0;
            text_buf[0] = (char)ev.key; // 'a'
        }
        
        if (!has_mods_that_prevent_text) {
             ev.text = text_buf;
        }

    } else if (ev.key < 128 && isprint(ev.key)) {
         static char text_buf[2] = {0};
         text_buf[0] = (char)ev.key;
         if (!has_mods_that_prevent_text) {
             ev.text = text_buf;
         }
    }


    char output[KEY_BUFFER_SIZE];
    memset(output, 0, KEY_BUFFER_SIZE);

    int result = encode_glfw_key_event(&ev, cursor_key_mode, kitty_flags, output);

    if (result == SEND_TEXT_TO_CHILD) {
        if (ev.text) {
            printf("%s", ev.text);
        }
    } else if (result > 0) {
        for (int i = 0; i < result; i++) {
            if (output[i] == '\x1b') printf("ESC");
            else if (output[i] < 32 || output[i] == 127) {
                switch(output[i]) {
                    case '\r': printf("\\r"); break;
                    case '\n': printf("\\n"); break;
                    case '\t': printf("\\t"); break;
                    case '\0': printf("\\0"); break;
                    case '\b': printf("\\b"); break;
                    default: printf("\\x%02x", (unsigned char)output[i]);
                }
            }
            else printf("%c", output[i]);
        }
    }

    fprintf(stderr, "[kittyTester] Key: %d, Mods: %d, Flags: %d, Action: %d, Text: '%s' -> Result Len: %d\n", 
            ev.key, ev.mods, kitty_flags, ev.action, ev.text ? ev.text : "(null)", result);

    return 0;
}