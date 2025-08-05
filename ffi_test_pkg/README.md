This package contains a small command-line application (bin/), library code (lib/), and example unit tests (test/)

## Quick-start

1. Install system prerequisites  
   • macOS / Linux: `cmake` and `clang` or `gcc`  
   • Windows: Visual Studio Build Tools or mingw64

2. Build the native library once (run from `ffi_test_pkg` root):
   ```bash
   cd src
   cmake .
   make          # or `cmake --build .` on Windows
   cd ..
   ```

3. Fetch Dart packages:
   ```bash
   dart pub get
   ```

4. Run tests:
   ```bash
   dart test
   ```

> VS Code users: make sure the workspace folder is `ffi_test_pkg`.  
> The test runner assumes `Directory.current` points to that folder when it looks for `src/libtest_lib.{dylib,so,dll}`.