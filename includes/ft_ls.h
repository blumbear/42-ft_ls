#pragma once

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>

#define RESET	"\x1b[0m"

/* Couleurs texte basiques */
#define BLACK	"\x1b[30m"
#define RED		"\x1b[31m"
#define GREEN	"\x1b[32m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define MAGENTA	"\x1b[35m"
#define CYAN	"\x1b[36m"
#define WHITE	"\x1b[37m"

/* Styles */
#define BOLD		"\x1b[1m"
#define UNDERLINE	"\x1b[4m"

#define FLAG_LIST "adglrstuR"

enum {
	FLAG_A = 1u << 0,
	FLAG_D = 1u << 1,
	FLAG_G = 1u << 2,
	FLAG_L = 1u << 3,
	FLAG_S = 1u << 4,
	FLAG_R_CAP = 1u << 5,
};

struct flags {
	uint32_t flags_mask;
	char sort;
};

//sort:
//	r -> reverse the sort
//	t -> by time
//	u -> weird (with -lt: sort by, and show, access time; with -l: show access time and sort by name; otherwise: sort by access time, newest first)

struct fList {
	char name[256];
	char data[500];
	unsigned char type;
	struct s_fList *next;
	
};

//struct dirent {
//	ino_t          d_ino;       /* Inode number */
//	off_t          d_off;       /* Not an offset; see below */
//	unsigned short d_reclen;    /* Length of this record */
//	unsigned char  d_type;      /* Type of file; not supported
//									by all filesystem types */
//	char           d_name[256]; /* Null-terminated filename */
//};

//	type :
//		file -> 8
//		dir -> 4