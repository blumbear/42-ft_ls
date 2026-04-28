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
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
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

enum {
	FLAG_A	 = 1u << 0,  /* -a : show hidden files */
	FLAG_D	 = 1u << 1,  /* -d : list directories themselves */
	FLAG_G	 = 1u << 2,  /* -g : (unused / group) */
	FLAG_L	 = 1u << 3,  /* -l : long format */
	FLAG_R_CAP = 1u << 5,  /* -R : recursive */
	FLAG_S	 = 1u << 6,  /* -s : show block size */
};

enum {
	FLAG_R = 1u << 0,  /* -r : reverse sort */
	FLAG_S_CAP = 1u << 1, /* -S : Sort by size */
	FLAG_T = 1u << 2, /* -t : sort by time, newest first*/
};

struct env {
	uint64_t flags_mask;
	uint64_t sort_flags_mask;
	bool stat;
};

struct filesData {
	char			name[256];
	unsigned char	type;
	struct stat		*stat;
};


static const uint32_t FLAG_MAP[256] = {
	['a'] = FLAG_A,
	['d'] = FLAG_D,
	['g'] = FLAG_G,
	['l'] = FLAG_L,
	['s'] = FLAG_S,
	['R'] = FLAG_R_CAP,
	['r'] = FLAG_R,
	['S'] = FLAG_S_CAP,
	['t'] = FLAG_T,
};

int	cmpName(const void *a, const void *b);
int	cmpSize(const void *a, const void *b);
int	cmpTime(const void *a, const void *b);


/* main.c */
static inline int flagIsSet(uint32_t mask, unsigned char c) {
	return (mask & FLAG_MAP[c]) != 0;
}
bool	handleFlags(char *flags, struct env *tflags);
void	initfList(struct env *flags);

/* printer.c */
void	printUser(struct filesData file);
void	printLongFormat(struct filesData file);
void	printLine(uint32_t flags_mask, struct filesData files);
void	filesPrinter(struct filesData files[500], struct env env, int last, size_t size);
void	printPerm(struct filesData file);


//struct dirent {
//     ino_t          d_ino;       /* Inode number */
//     off_t          d_off;       /* Not an offset; see below */
//     unsigned short d_reclen;    /* Length of this record */
//     unsigned char  d_type;      /* Type of file; not supported by all filesystem types */
//     char           d_name[256]; /* Null-terminated filename */
//};

//	type :
//		file -> 8
//		dir  -> 4



// struct stat {
//     dev_t     st_dev;      /* ID du périphérique contenant le fichier */
//     ino_t     st_ino;      /* Numéro inœud */
//     mode_t    st_mode;     /* Protection */
//     nlink_t   st_nlink;    /* Nb liens matériels */
//     uid_t     st_uid;      /* UID propriétaire */
//     gid_t     st_gid;      /* GID propriétaire */
//     dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
//     off_t     st_size;     /* Taille totale en octets */
//     blksize_t st_blksize;  /* Taille de bloc pour E/S */
//     blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
//     time_t    st_atime;    /* Heure dernier accès */
//     time_t    st_mtime;    /* Heure dernière modification */
//     time_t    st_ctime;    /* Heure dernier changement état */
// };
