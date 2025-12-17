/*
 * Constants for the kitty keyboard protocol
 * Reference: https://sw.kovidgoyal.net/kitty/keyboard-protocol/
 */

#pragma once

// Basic keys
#define KITTY_KEY_INSERT       2
#define KITTY_KEY_DELETE       3
#define KITTY_KEY_TAB          9
#define KITTY_KEY_ENTER        13
#define KITTY_KEY_ESCAPE       27
#define KITTY_KEY_BACKSPACE    127

// Navigation keys
#define KITTY_KEY_LEFT         1
#define KITTY_KEY_RIGHT        1
#define KITTY_KEY_UP           1
#define KITTY_KEY_DOWN         1
#define KITTY_KEY_HOME         1
#define KITTY_KEY_END          1
#define KITTY_KEY_KP_BEGIN     1
#define KITTY_KEY_PAGE_UP      5
#define KITTY_KEY_PAGE_DOWN    6

#define KITTY_KEY_CAPS_LOCK    57358
#define KITTY_KEY_SCROLL_LOCK  57359
#define KITTY_KEY_NUM_LOCK     57360
#define KITTY_KEY_PRINT_SCREEN 57361
#define KITTY_KEY_PAUSE        57362
#define KITTY_KEY_MENU         57363

// Function keys
#define KITTY_KEY_F1           11
#define KITTY_KEY_F2           12
#define KITTY_KEY_F3           13
#define KITTY_KEY_F4           14
#define KITTY_KEY_F5           15
#define KITTY_KEY_F6           17
#define KITTY_KEY_F7           18
#define KITTY_KEY_F8           19
#define KITTY_KEY_F9           20
#define KITTY_KEY_F10          21
#define KITTY_KEY_F11          23
#define KITTY_KEY_F12          24
#define KITTY_KEY_F13          57388
#define KITTY_KEY_F14          57389
#define KITTY_KEY_F15          57390
#define KITTY_KEY_F16          57391
#define KITTY_KEY_F17          57392
#define KITTY_KEY_F18          57393
#define KITTY_KEY_F19          57394
#define KITTY_KEY_F20          57395
#define KITTY_KEY_F21          57396
#define KITTY_KEY_F22          57397
#define KITTY_KEY_F23          57398
#define KITTY_KEY_F24          57399
#define KITTY_KEY_F25          57400
#define KITTY_KEY_F26          57401
#define KITTY_KEY_F27          57402
#define KITTY_KEY_F28          57403
#define KITTY_KEY_F29          57404
#define KITTY_KEY_F30          57405
#define KITTY_KEY_F31          57406
#define KITTY_KEY_F32          57407
#define KITTY_KEY_F33          57408
#define KITTY_KEY_F34          57409
#define KITTY_KEY_F35          57410

// Keypad keys
#define KITTY_KEY_KP_0         57399
#define KITTY_KEY_KP_1         57400
#define KITTY_KEY_KP_2         57401
#define KITTY_KEY_KP_3         57402
#define KITTY_KEY_KP_4         57403
#define KITTY_KEY_KP_5         57404
#define KITTY_KEY_KP_6         57405
#define KITTY_KEY_KP_7         57406
#define KITTY_KEY_KP_8         57407
#define KITTY_KEY_KP_9         57408
#define KITTY_KEY_KP_DECIMAL   57409
#define KITTY_KEY_KP_DIVIDE    57410
#define KITTY_KEY_KP_MULTIPLY  57411
#define KITTY_KEY_KP_SUBTRACT  57412
#define KITTY_KEY_KP_ADD       57413
#define KITTY_KEY_KP_ENTER     57414
#define KITTY_KEY_KP_EQUAL     57415
#define KITTY_KEY_KP_SEPARATOR 57416
#define KITTY_KEY_KP_LEFT      57417
#define KITTY_KEY_KP_RIGHT     57418
#define KITTY_KEY_KP_UP        57419
#define KITTY_KEY_KP_DOWN      57420
#define KITTY_KEY_KP_PAGE_UP   57421
#define KITTY_KEY_KP_PAGE_DOWN 57422
#define KITTY_KEY_KP_HOME      57423
#define KITTY_KEY_KP_END       57424
#define KITTY_KEY_KP_INSERT    57425
#define KITTY_KEY_KP_DELETE    57426

// Modifiers (as shift counts for CSI u)
// 1 = Shift
// 2 = Alt
// 4 = Ctrl
// 8 = Super
// 16 = Hyper
// 32 = Meta
// 64 = Caps Lock
// 128 = Num Lock

// Modifiers keys
#define KITTY_KEY_LEFT_SHIFT   57441
#define KITTY_KEY_LEFT_CONTROL 57442
#define KITTY_KEY_LEFT_ALT     57443
#define KITTY_KEY_LEFT_SUPER   57444
#define KITTY_KEY_LEFT_HYPER   57445
#define KITTY_KEY_LEFT_META    57446
#define KITTY_KEY_RIGHT_SHIFT  57447
#define KITTY_KEY_RIGHT_CONTROL 57448
#define KITTY_KEY_RIGHT_ALT    57449
#define KITTY_KEY_RIGHT_SUPER  57450
#define KITTY_KEY_RIGHT_HYPER  57451
#define KITTY_KEY_RIGHT_META   57452
#define KITTY_KEY_ISO_LEVEL3_SHIFT 57453
#define KITTY_KEY_ISO_LEVEL5_SHIFT 57454
