#!/usr/bin/env python3
import sys
import os

DEST_PATH = 'kitty_test/kitty_encoder_body.inc'

def extract(source_path):
    if not os.path.exists(source_path):
        print(f"Error: Source file '{source_path}' not found.", file=sys.stderr)
        sys.exit(1)

    with open(source_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    with open(DEST_PATH, 'w', encoding='utf-8') as f:
        f.write("// Extracted from " + os.path.basename(source_path) + "\n")
        for line in lines:
            if line.strip().startswith('#include'):
                f.write(f"// {line}")
            else:
                f.write(line)
    
    print(f"[*] Processed '{source_path}' into '{DEST_PATH}'")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 extract_kitty.py <path_to_key_encoding.c>", file=sys.stderr)
        sys.exit(1)
    extract(sys.argv[1])