# Test Harness for kitty keyboard protocol implementation in GNOME VTE

This project is a specialized testing infrastructure designed to verify the implementation of the **kitty keyboard protocol** within **GNOME VTE**.

It works by extracting the core key encoding logic from both the **kitty** source code (the reference implementation) and the **VTE** source code (the target implementation), wrapping them in isolated mock environments, and running a comprehensive differential test suite against thousands of key combinations.

## Project Structure

```text
.
├── Makefile              # Automates code extraction, compilation, and linking
├── run_tests.py          # Main Python test runner and comparator
├── source/               # PLACE SOURCE FILES HERE (see Setup)
│   ├── vte.cc            # From vte source tree (src/vte.cc)
│   └── key_encoding.c    # From kitty source tree (kitty/key_encoding.c)
├── kitty_test/           # Mock environment and CLI wrapper for kitty logic
│   ├── extract_kitty.py  # Script to strip includes from kitty source
│   ├── kitty_mocks.h     # Mocks for GLFW and internal kitty types
│   └── kitty_tester.c    # Entry point for the kitty tester binary
└── vte_test/             # Mock environment and CLI wrapper for VTE logic
    ├── extract_code.py   # Script to extract specific function bodies from VTE
    ├── kittykeys.h       # Protocol constants
    ├── main.cc           # Entry point for the vte tester binary
    ├── vte_key_tester.cc # Wrapper for the extracted VTE logic
    └── vte_key_tester.h  # Mocks for GDK/GTK types and XKB common
```

## Setup & Prerequisites

### Dependencies
You need a standard C/C++ build environment and `libxkbcommon` development headers.
*   **Debian/Ubuntu:** `sudo apt install build-essential libxkbcommon-dev pkg-config`
*   **Fedora:** `sudo dnf install @development-tools libxkbcommon-devel`

### Preparing Source Files
This harness does not include the original source code. You must copy the relevant files from your VTE and kitty repositories into the `source/` directory:

1.  Copy `kitty/key_encoding.c` from the kitty repo to `source/key_encoding.c`.
2.  Copy `src/vte.cc` from your modified VTE repo to `source/vte.cc`.

## Usage

1.  **Build the testers:**
    Run `make` in the root directory. This will:
    *   Extract the relevant code snippets from the files in `source/`.
    *   Compile the isolated testers against their mock headers.
    *   Generate binaries in `build/bin/`.

    ```bash
    make
    ```

2.  **Run the test suite:**
    Run the Python script to generate key combinations and compare outputs.

    ```bash
    python3 run_tests.py
    ```

    **Options:**
    *   `--limit N`: Run only the first N tests (useful for quick checks).
    *   `--debug`: Print the exact commands being executed and their stderr output.

3.  **Analyze Results:**
    *   **Console:** Shows progress and a summary.
    *   **`mismatches.log`**: Contains a human-readable diff of every case where kitty and VTE disagreed.
    *   **`test_results.json`**: Contains the raw data for all tests.

---

## Design Rationale

This testing infrastructure was built based on specific constraints and lessons learned from previous attempts. Here is why it is built the way it is:

### 1. Why Code Extraction?
Linking against the full `libvte` or building the full `kitty` binary is overkill and introduces massive dependencies (GTK, Wayland/X11, GLib event loops, Python runtime for kitty).
*   **Decision:** We extract *only* the specific C/C++ functions responsible for translating key events into escape sequences (`encode_glfw_key_event` in kitty and `widget_key_press` logic in VTE).
*   **Result:** The resulting test binaries are tiny, compile instantly, and have almost no runtime overhead.

### 2. Why Mocking?
Early attempts using tools like `xdotool`, `send_key`, or `xtest` to send events to a running terminal window were unreliable.
*   **Problem:** Very slow, focus stealing, race conditions, and the overhead of the display server made tests flaky and slow. Also, some xtest'ed key combinations may log you out, send you to the kernel console or burn your house. Also, GTK ignores "synthetic" keyboard events completely.
*   **Decision:** We mock the environment. We created `kitty_mocks.h` and `vte_key_tester.h` to emulate the necessary structs (`GLFWkeyevent`, `GdkEventKey`) and constants.
*   **Result:** The tests run in a "headless" CLI environment. They are deterministic, reproducible, and extremely fast (thousands of checks per second).

