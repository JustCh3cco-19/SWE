# Stochastic Systems Lab

A collection of C++ exercises focused on stochastic systems, discrete-event
simulation, probability, queues, networks, optimization, and e-commerce
systems.

## Repository layout

```text
src/            Exercise implementations grouped by topic
include/        All public headers, grouped by topic and exercise
data/           Input files, expected results, and exercise PDFs
docs/           Exam instructions and supporting documents
CMakeLists.txt  Central CMake build configuration
.clang-format   Google C++ Style configuration
.uncrustify.cfg Autoformatter configuration
```

The exercises are organized into these topics:

- `probability-and-statistics`
- `queues-and-services`
- `optimization`
- `networks-and-reliability`
- `ecommerce`

Each exercise directory keeps the original exam session in its name using the
`YYYY-MM-DD-exN` format. This preserves the source context without making the
calendar year the primary organizational principle.

The MOCC support headers are part of the global `include/` tree under
`include/mocc/`. Its implementation is kept in
`src/mocc/`. Only components actually used by the exercises are included.

## Building

Requirements:

- CMake 3.20 or newer
- A C++23-compatible compiler

Configure and build in a separate directory:

```sh
cmake -S . -B build
cmake --build build -j
```

This creates one executable per exercise and a shared static target for the
MOCC support code. Build artifacts are ignored by Git.

## Style

The project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
The repository includes a `.clang-format` configuration based on the Google
style and a matching `.uncrustify.cfg` for environments where `clang-format`
is not installed. Format the whole project with:

```sh
find src include -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 \\
  | xargs -0 uncrustify -c .uncrustify.cfg --replace --no-backup
```

When `clang-format` is available, format a file with:

```sh
clang-format -i path/to/file.cpp path/to/file.hpp
```
