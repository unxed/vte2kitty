#!/bin/bash
rm key_encoding.c
wget https://raw.githubusercontent.com/kovidgoyal/kitty/d7ce3eb66e5bf78f45e73818426d086004e52e61/kitty/key_encoding.c
#
rm vte.cc
wget https://gitlab.gnome.org/unxed/vte/-/raw/b40502b2ce7e1bc3af732d602ea457639853ac42/src/vte.cc
# This links to MR. Link should be updated to upstream upon merge
#
rm vtshell_translation_kitty.cpp
wget https://raw.githubusercontent.com/elfmz/far2l/b9702f965384b8b227e6e7c0da0fa62c833ec9a9/far2l/src/vt/vtshell_translation_kitty.cpp
#
rm keyboard.rs
wget https://raw.githubusercontent.com/alacritty/alacritty/18372031d1f1bda853b2027b7ef1c75b45942829/alacritty/src/input/keyboard.rs
