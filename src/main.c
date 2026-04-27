/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:30:48 by tom               #+#    #+#             */
/*   Updated: 2026/04/27 15:57:02 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static const uint32_t FLAG_MAP[256] = {
	['a'] = FLAG_A,
	['d'] = FLAG_D,
	// ['g'] = FLAG_G,
	['l'] = FLAG_L,
	['s'] = FLAG_S,
	['R'] = FLAG_R_CAP,
	['r'] = FLAG_R,
};

static inline int flagIsSet(uint32_t mask, unsigned char c) {
	return (mask & FLAG_MAP[c]) != 0;
}



void printLongFormat(struct filesData file) {
	if (file.type == 4) write(1, "d", 1);
	else write(1, "-", 1);
	
	if (S_IRUSR & file.stat->st_mode) write(1, "r", 1);
	else write(1, "-", 1);

	if (S_IWUSR & file.stat->st_mode) write(1, "w", 1);
	else write(1, "-", 1);

	if (S_IXUSR & file.stat->st_mode) write(1, "x", 1);
	else write(1, "-", 1);

	if (S_IRGRP & file.stat->st_mode) write(1, "r", 1);
	else write(1, "-", 1);

	if (S_IWGRP & file.stat->st_mode) write(1, "w", 1);
	else write(1, "-", 1);

	if (S_IXGRP & file.stat->st_mode) write(1, "x", 1);
	else write(1, "-", 1);

	if (S_IROTH & file.stat->st_mode) write(1, "r", 1);
	else write(1, "-", 1);

	if (S_IWOTH & file.stat->st_mode) write(1, "w", 1);
	else write(1, "-", 1);

	if (S_IXOTH & file.stat->st_mode) write(1, "x", 1);
	else write(1, "-", 1);
	
	write(1, " ", 1);
}

void printLine(uint32_t flags_mask, struct filesData files) {
	if (flagIsSet(flags_mask, 's')) ft_printf("  %d ", (files.stat->st_blocks * 512 + 1023) / 1024);
	
	if (flagIsSet(flags_mask, 'l')) printLongFormat(files);

	if (files.type == 4) ft_printf("\x1b[1m\x1b[34m%s  \x1b[0m", files.name);
	else ft_printf("%s  ", files.name);
	
	if (flagIsSet(flags_mask, 'l') || flagIsSet(flags_mask, 'g'))
		write(1, "\n", 1);
}

void filesPrinter(struct filesData files[500], uint32_t flags_mask, int last, size_t size) {
	if (flagIsSet(flags_mask, 'l') || flagIsSet(flags_mask, 's'))
		ft_printf("total %d\n", size);
	if (flagIsSet(flags_mask, 'r')) {
		last--;
		for (; last >= 0; last--){
			printLine(flags_mask, files[last]);
			if (files[last].stat) free(files[last].stat);
		}
	} else {
		for (int k = 0; k < last; k++){
			printLine(flags_mask, files[k]);
			if (files[k].stat) free(files[k].stat);
		}
	}
}

bool handleFlags(char *flags, struct env *tflags) {
	for (int i = 1; flags[i]; i++) {
		unsigned char c = (unsigned char)flags[i];
		uint32_t m = FLAG_MAP[c];
		if (m == 0) {
			ft_printf("ls: invalid option -- %c", c);
			return false;
		}
		tflags->flags_mask |= m;
		if (flags[i] == 'l' || flags[i] == 's' || flags[i] == 'S' || flags[i] == 'g')
			tflags->stat = true;
	}
	return true;
}

void initfList(struct env *flags) {
	flags->flags_mask = 0;
	flags->stat = false;
}

static int	cmpName(const void *a, const void *b)
{
	char *ca = ft_strdup(((struct filesData *)a)->name);
	char *cb = ft_strdup(((struct filesData *)b)->name);

	char *na = ca;
	char *nb = cb;
	while (*na == '.') na++;
	while (*nb == '.') nb++;

	for (int i = 0; na[i]; i++) na[i] = tolower(na[i]);
	for (int i = 0; nb[i]; i++) nb[i] = tolower(nb[i]);
	
	int res = ft_strncmp(na, nb, 256);

	free(ca);
	free(cb);

	return res;
}

int main(int ac, char **av) {
	struct env	flags;
	struct dirent	*readDir;
	DIR				*dirfile;
	char			*to_open[ac];
	int				j = 0;

	initfList(&flags);
	to_open[0] = ".";
	to_open[1] = NULL;
	if (ac > 1) {
		for (int i = 1; i < ac; i++) {
			if (av[i][0] == '-') {
				if (handleFlags(av[i], &flags) == false)
					return EXIT_SUCCESS;
			} else {
				to_open[j++] = av[i];
			}
		}
		if (to_open[j])
			to_open[j + 1] = NULL;
		else
			to_open[j] = NULL;
	}
	bool format = (j > 1);

	for (int i = 0; to_open[i]; i++) {
		dirfile = opendir(to_open[i]);
		if (dirfile) {
			struct filesData	files[500];
			int		k = 0;
			size_t	size = 0;

			if (format == true) ft_printf("%s:\n", to_open[i]);
			while ((readDir = readdir(dirfile)) != NULL) {
				if (readDir->d_name[0] == '.' && !flagIsSet(flags.flags_mask, 'a'))
					continue;
				strncpy(files[k].name, readDir->d_name, 255);
				files[k].name[255] = '\0';
				files[k].type = readDir->d_type;
				if (flags.stat) {
					files[k].stat = malloc(sizeof(struct stat));
					if (stat(files[k].name ,files[k].stat) != 0) {
						break;
					}
					size += ((files[k].stat->st_blocks * 512 + 1023) / 1024);
				} else files[k].stat = NULL;
				k++;
			}
			qsort(files, k, sizeof(struct filesData), cmpName);
			filesPrinter(files, flags.flags_mask, k, size);
			putchar('\n');
			if (to_open[i + 1] != NULL)
				putchar('\n');
			closedir(dirfile);
		} else {
			ft_printf("ls: cannot access '%s': No such file or directory", to_open[i]);
		}
	}
	return EXIT_SUCCESS;
}