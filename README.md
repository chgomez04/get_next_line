# get_next_line

C implementation of `get_next_line`, a function that reads and returns one complete line from a file descriptor on each call. This project is part of the 42 curriculum and focuses on dynamic memory management, incremental reading with `read()`, and persistent state between function calls.

## Description

`get_next_line` makes it possible to read files, standard input, or other file descriptors line by line without loading the full content into memory. The implementation keeps a static buffer between calls to preserve bytes that have already been read but not yet returned.

This repository includes:

- Mandatory version for reading from one file descriptor.
- Bonus version for alternating reads across multiple file descriptors.
- Custom allowed utility functions for memory and string handling.
- Support Makefile to compile, clean, and run basic checks.

## Technologies

- C language
- POSIX `read()`
- Compilation with `cc`
- Flags: `-Wall -Wextra -Werror`

## Structure

```text
.
|-- get_next_line.c
|-- get_next_line.h
|-- get_next_line_utils.c
|-- get_next_line_bonus.c
|-- get_next_line_bonus.h
|-- get_next_line_utils_bonus.c
|-- Makefile
`-- docs/
    `-- es.subject.pdf
```

## How to Compile

Compile the mandatory version as a static library:

```sh
make
```

Compile the bonus version:

```sh
make bonus
```

Change the `BUFFER_SIZE` value:

```sh
make CFLAGS="-Wall -Wextra -Werror -D BUFFER_SIZE=42"
```

Run basic compilation checks:

```sh
make test
```

Check the 42 Norm, if `norminette` is installed:

```sh
make norm
```

Remove generated build artifacts:

```sh
make fclean
```

## Prototype

```c
char	*get_next_line(int fd);
```

The function returns the next line read, including the newline character when present. It returns `NULL` when the end of the file is reached or if an error occurs.

## Implementation Highlights

- Configurable buffer through `BUFFER_SIZE`.
- Incremental reading until `\n` or EOF is reached.
- Persistent state handled with a static variable.
- Dynamic memory management so each returned line is separately allocated.
- Bonus version with an independent buffer for each file descriptor.

## What I Learned

- How to control leaks and errors in dynamic-memory workflows.
- How to use static variables responsibly to preserve state.
- How to handle edge cases such as EOF, files without a final newline, and variable `BUFFER_SIZE` values.
- How to separate reading, line extraction, and remainder-preservation logic.

## Future Improvements

- Expand the automated test suite with large files, empty inputs, and intensive file-descriptor alternation.
- Review the bonus file-descriptor limit according to the execution environment.
- Add a performance comparison for different `BUFFER_SIZE` values.

## Author

**Christian Gomez**  
Project developed as part of the 42 Barcelona curriculum.
