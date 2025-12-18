#!/usr/bin/env python3
import sys
import os

def extract_function_body(source_path, dest_path):
    if not os.path.exists(source_path):
        print(f"Error: Source file '{source_path}' not found.", file=sys.stderr)
        sys.exit(1)

    with open(source_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    body = []
    in_function = False
    brace_level = 0
    
    # Signature of the function we want to extract
    func_sig = "std::string VT_TranslateKeyToKitty"

    for line in lines:
        if not in_function:
            if func_sig in line and "{" in line:
                in_function = True
                brace_level = line.count("{") - line.count("}")
                body.append("// Extracted body of VT_TranslateKeyToKitty\n")
            elif func_sig in line:
                in_function = True
                brace_level = 0
        else:
            # We are inside the function
            # If we just started and brace_level is 0, wait for opening brace
            if brace_level == 0 and "{" in line:
                brace_level += line.count("{")
                brace_level -= line.count("}")
                continue # Skip the line with the first opening brace if it was separate

            brace_level += line.count("{")
            brace_level -= line.count("}")

            if brace_level <= 0:
                break
            
            body.append(line)

    if not body:
        print(f"Error: Function body for '{func_sig}' not found or empty.", file=sys.stderr)
        sys.exit(1)

    with open(dest_path, 'w', encoding='utf-8') as f:
        f.writelines(body)
    
    print(f"[*] Extracted far2l logic to '{dest_path}'")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        # Default behavior for Makefile simplicity if called without args, 
        # though Makefile should ideally pass them.
        source = 'source/vtshell_translation_kitty.cpp'
        dest = 'far2l_test/far2l_key_press_body.inc'
    else:
        source = sys.argv[1]
        dest = 'far2l_test/far2l_key_press_body.inc'

    extract_function_body(source, dest)