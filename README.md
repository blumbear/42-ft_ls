# ft_ls

A small implementation of the Unix `ls` command. This project lists directory contents and supports a subset of common `ls` flags. The goal is to reproduce typical `ls` behaviors so the program can be used like the system `ls` for common directory listing tasks.

## Usage

    ft_ls [OPTIONS] [FILE...]

If no path is provided, `ft_ls` lists the current directory (`.`).

## Supported flags

The following options are supported by this implementation. The descriptions match common `ls` semantics; small differences may exist depending on the implementation details in this repository.

- `-a`  : Show all entries, including those whose names begin with a dot (`.`). Without `-a`, hidden files are skipped.
- `-d`  : List directory names themselves, instead of listing their contents. Use this to inspect directory names without descending into them.
- `-g`  : Long listing format without owner information (BSD-style). It is similar to `-l` but omits the owner column.
- `-l`  : Long listing format. Show file mode (permissions), number of links, owner, group, size, timestamp and filename (exact columns may vary). This is the verbose, multi-column listing used for detailed inspection.
- `-s`  : Print the allocated size (in blocks) before each file name. Useful to see disk usage per entry.
- `-R`  : Recursive. Traverse directories recursively and list their contents.
- `-t`  : Sort by modification time, newest entries first.
- `-r`  : Reverse the sort order. Combine with `-t` to get oldest-first by time, or with other sorts to invert the order.
- `-u`  : Use access time (instead of modification time) for sorting and/or display when combined with `-l` or `-t`. Behavior can depend on whether `-l` or `-t` are also provided.

## Combining flags

Flags can be combined in a single argument (for example `-al` is equivalent to `-a -l`). Sorting flags (`-t`, `-r`, `-u`) interact: `-t` chooses time-based ordering, `-r` reverses the result, and `-u` switches which timestamp is used for sorting.

Examples:

- `ft_ls` — list non-hidden entries in current directory.
- `ft_ls -a` — include hidden entries.
- `ft_ls -l /etc` — long listing of `/etc`.
- `ft_ls -ltr` — long listing, sorted by modification time oldest-first (because `-r` reverses `-t`).
- `ft_ls -R dir1 dir2` — recursively list `dir1` then `dir2`.

## Notes

- This README documents the flags this project implements. For full `ls` behavior (locale handling, colorization, many GNU extensions), consult your system `ls` man page (`man ls`).
- The implementation uses a compact bitmask representation for flags and a fast mapping from option character to bit; see `includes/ft_ls.h` for details.

If you want this README translated to another language or extended with examples and build instructions, tell me which details to add.