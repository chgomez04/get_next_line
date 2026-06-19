*This project was created as part of the 42 curriculum by chgomez.*

# get_next_line

## Overview

`get_next_line` is a C function that reads and returns one complete line from a file descriptor on each call.

The project focuses on dynamic memory management, incremental reading with `read()`, file descriptors, buffer handling and persistent state between function calls.

## Description

`get_next_line` makes it possible to read files, standard input or other file descriptors line by line without loading the full content into memory.

The implementation keeps a static buffer between calls to preserve bytes that have already been read but not yet returned.

This repository includes:

- Mandatory version for reading from one file descriptor.
- Bonus version for alternating reads across multiple file descriptors.
- Custom utility functions for memory and string handling.
- Support Makefile to compile, clean and run basic checks.

## Prototype

```c
char	*get_next_line(int fd);
```

The function returns the next line read, including the newline character when present. It returns `NULL` when the end of the file is reached or if an error occurs.

## Technologies

- C language
- POSIX `read()`
- File descriptors
- Static variables
- Dynamic memory allocation
- Compilation with `cc`
- Flags: `-Wall -Wextra -Werror`

## Project Structure

```text
.
├── Makefile
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils.c
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line_utils_bonus.c
└── docs/
    └── es.subject.pdf
```

## How to Compile

Compile the mandatory version:

```bash
make
```

Compile the bonus version:

```bash
make bonus
```

Change the `BUFFER_SIZE` value:

```bash
make CFLAGS="-Wall -Wextra -Werror -D BUFFER_SIZE=42"
```

Run basic compilation checks:

```bash
make test
```

Check the 42 Norm, if `norminette` is installed:

```bash
make norm
```

Remove generated build artifacts:

```bash
make fclean
```

## Usage Example

Create a simple `main.c` test file:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile it with:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o test_gnl
```

Run:

```bash
./test_gnl
```

Make sure an `example.txt` file exists in the same directory before running the test program.

## Implementation Highlights

- Configurable buffer through `BUFFER_SIZE`.
- Incremental reading until `\n` or EOF is reached.
- Persistent state handled with a static variable.
- Dynamic memory management so each returned line is separately allocated.
- Careful handling of EOF, empty files and files without a final newline.
- Bonus version with an independent buffer for each file descriptor.

## What I Learned

- How to use `read()` with file descriptors.
- How static variables preserve state between function calls.
- How to manage memory allocation and avoid leaks in repeated calls.
- How to split the problem into reading, line extraction and buffer preservation.
- How to handle edge cases such as EOF, empty files, invalid file descriptors and different `BUFFER_SIZE` values.
- How to build a reusable function under strict project constraints.

## Future Improvements

- Expand the automated test suite with large files, empty inputs and intensive file-descriptor alternation.
- Review the bonus file-descriptor limit according to the execution environment.
- Add performance comparison for different `BUFFER_SIZE` values.
- Add more examples for standard input and multiple file descriptors.

## Notes

This project follows the constraints and style expected in the 42 curriculum.
The implementation is intentionally written in C and focuses on low-level file reading, memory management and state preservation.

## Author

- Christian Gómez
- Junior Software Developer in training at 42 Barcelona
- GitHub: [github.com/chgomez04](https://github.com/chgomez04)
