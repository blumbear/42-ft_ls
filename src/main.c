/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:30:48 by tom               #+#    #+#             */
/*   Updated: 2026/03/02 16:16:45 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static const uint32_t FLAG_MAP[256] = {
	['a'] = FLAG_A,
	['d'] = FLAG_D,
	['g'] = FLAG_G,
	['l'] = FLAG_L,
	['s'] = FLAG_S,
	['R'] = FLAG_R_CAP,
};

static inline int flags_is_set(uint32_t mask, unsigned char c) {
	return (mask & FLAG_MAP[c]) != 0;
}

void filePrinter(char name[256], unsigned char type) {
	if (type == 4)
		printf("\x1b[1m\x1b[34m%s  \x1b[0m", name);
	else 
		printf("%s  ", name);
}

bool handleFlags(char *flags, struct flags *tflags) {
	for (int i = 1; flags[i]; i++) {
		unsigned char c = (unsigned char)flags[i];
		uint32_t m = FLAG_MAP[c];
		if (m == 0) {
			printf("ls: invalid option -- %c", c);
			return false;
		}
		tflags->flags_mask |= m;
	}
	return true;
}

void initfList(struct flags *flags) {
	flags->flags_mask = 0;
	flags->sort = 0;
}

int main(int ac, char **av) {
	struct flags flags;
	struct dirent *readDir;

	DIR *dirfile;
	char *to_open[ac-1];
	int j = 0;
	to_open[0] = "."; to_open[1] = NULL;
	if (ac > 1) {
		for (int i = 1; i < ac; i++) {
			if (av[i][0] == '-') {
				if (handleFlags(av[i], &flags) == false)
					return EXIT_SUCCESS;
			} else {
				to_open[j++] = av[i];
			}
			to_open[j] = NULL;
		}
	}
	bool format = (j > 1);

	for (int i = 0; to_open[i]; i++) {
		dirfile = opendir(to_open[i]);
		if (dirfile) {
			if (format == true) printf("%s:\n", to_open[i]);
			while ((readDir = readdir(dirfile)) != NULL) {
				// skipped hidden files
				if ((readDir->d_name[0] == '.' && !flags_is_set(flags.flags_mask, 'a'))) continue;

				// color folder to increased readability
				filePrinter(readDir->d_name, readDir->d_type);
			}
			putchar('\n');
			if (to_open[i + 1] != NULL)
				putchar('\n');
			closedir(dirfile);
		} else {
			printf("ls: cannot access '%s': No such file or directory", to_open[i]);
		} 
	}
	return EXIT_SUCCESS;
}