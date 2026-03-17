#pragma once

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"

#define RESET		"\x1b[0m"

/* Couleurs texte basiques */
#define BLACK		"\x1b[30m"
#define RED			"\x1b[31m"
#define GREEN		"\x1b[32m"
#define YELLOW		"\x1b[33m"
#define BLUE		"\x1b[34m"
#define MAGENTA		"\x1b[35m"
#define CYAN		"\x1b[36m"
#define WHITE		"\x1b[37m"

/* Styles */
#define BOLD		"\x1b[1m"
#define UNDERLINE	"\x1b[4m"

#define FLAG_LIST "adglrstuR"

enum {
	FLAG_A	 = 1u << 0,  /* -a : show hidden files */
	FLAG_D	 = 1u << 1,  /* -d : list directories themselves */
	FLAG_G	 = 1u << 2,  /* -g : (unused / group) */
	FLAG_L	 = 1u << 3,  /* -l : long format */
	FLAG_S	 = 1u << 4,  /* -s : show block size */
	FLAG_R_CAP = 1u << 5,  /* -R : recursive */
	FLAG_R = 1u << 6,  /* -r : reverse sort */
};

struct flags {
	uint32_t flags_mask;
};

struct filesData {
	char			name[256];
	unsigned char	type;
	struct stat		stat;
};

/* prototypes */
void	filePrinter(char name[256], unsigned char type);
bool	handleFlags(char *flags, struct flags *tflags);
void	initfList(struct flags *flags);

//struct dirent {
//	ino_t		  d_ino;	   /* Inode number */
//	off_t		  d_off;	   /* Not an offset; see below */
//	unsigned short d_reclen;	/* Length of this record */
//	unsigned char  d_type;	  /* Type of file; not supported
//								   by all filesystem types */
//	char		   d_name[256]; /* Null-terminated filename */
//};

//	type :
//		file -> 8
//		dir  -> 4