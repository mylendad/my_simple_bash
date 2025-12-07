# Gemini Project Context: SimpleBashUtils

This document provides context for the C3_SimpleBashUtils-1 project, which contains custom implementations of the `cat` and `grep` command-line utilities.

## Project Overview

The project is written in C and aims to replicate the functionality of the standard Unix `cat` and `grep` tools. The source code is organized into two main directories: `cat` and `grep`.

Each utility supports a variety of command-line flags, including some GNU extensions. The code is compiled with strict flags (`-Wall -Werror -Wextra`), indicating a focus on code quality.

## Building and Running

The project uses a single `Makefile` in the root of the `src` directory for building the executables.

-   **Build:**
    ```bash
    make
    ```
-   **Run cat:**
    ```bash
    ./s21_cat [flags] [file...]
    ```
-   **Run grep:**
    ```bash
    ./s21_grep [flags] [pattern] [file...]
    ```
-   **Clean:**
    ```bash
    make clean
    ```

## Development Conventions

### Coding Style

The `.clang-format` file in the `grep` directory specifies `BasedOnStyle: Google`. This indicates that the project aims to adhere to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) for formatting C code.

### Testing

The project has a comprehensive test suite integrated into its `Makefile`. The tests are executed by comparing the output of the custom `s21_cat` and `s21_grep` implementations against the behavior of the standard system `cat` and `grep` commands.

To run the tests, use the `test` target in the `Makefile`:
```bash
make test
```

### Memory Safety

The `Makefile` includes a target for checking memory leaks using `valgrind`.

-   `make valgrind`