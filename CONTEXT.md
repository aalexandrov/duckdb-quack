# Fork Context

> **Note**: This file is specific to the `aalexandrov` fork and is not part of
> upstream `duckdb/ducklake`.

## Build instructions

Building requires `cmake`, `ninja`, and `vcpkg` (the latter provides the
`roaring` dependency used for deletion vectors, see `CMakeLists.txt`).

### Setup (once)
```bash
brew install cmake ninja vcpkg
# brew's vcpkg formula only ships the CLI; the CMake integration scripts require the full repo
git clone https://github.com/microsoft/vcpkg.git ~/supabase/vcpkg
~/supabase/vcpkg/bootstrap-vcpkg.sh
git submodule update --init --recursive
```

### Build
```bash
export VCPKG_TOOLCHAIN_PATH=~/supabase/vcpkg/scripts/buildsystems/vcpkg.cmake
export GEN=ninja
make
```

### Running

The build links the `ducklake` extension directly into the `duckdb` binary, so
no `LOAD` is needed. Start a `duckdb` instance 

```bash
./build/release/duckdb
```

and configure your ducklake yourself. Alternatively, start with the
pre-configured `scratchpad` duckake:

```bash
./build/release/duckdb -init scratchpad/init.sql
```

### Notes
- Do not run `make pull` unless you intend to move the
  `duckdb`/`extension-ci-tools` submodules to their latest remote commits — it
  can advance them past the commits this code was written against and break the
  build with upstream API mismatches. If that happens, restore the pinned
  commits with `git submodule update --init --recursive`.
- IDE support (VSCode + clangd) is configured via `.vscode/settings.json`, which
  points to the `compile_commands.json` generated under `build/release/`.
