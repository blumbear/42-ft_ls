/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:30:48 by tom               #+#    #+#             */
/*   Updated: 2026/04/28 15:19:23 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void sortFiles(struct filesData files[500], int k, struct env flags) {
	if (flagIsSet(flags.sort_flags_mask, 'S'))
		qsort(files, k, sizeof(struct filesData), cmpSize);
	else if (flagIsSet(flags.sort_flags_mask, 't'))
		qsort(files, k, sizeof(struct filesData), cmpTime);
	else
		qsort(files, k, sizeof(struct filesData), cmpName);

}

bool handleFlags(char *flags, struct env *tflags) {
	for (int i = 1; flags[i]; i++) {
		unsigned char c = (unsigned char)flags[i];
		uint32_t m = FLAG_MAP[c];
		if (m == 0) {
			ft_printf("ls: invalid option -- %c", c);
			return false;
		}
		if (c == 't' || c == 'S' || c == 'r')
			tflags->sort_flags_mask |= m;
		else
			tflags->flags_mask |= m;
		if (flags[i] == 'l' || flags[i] == 's' || flags[i] == 'S' || flags[i] == 'g' || flags[i] == 't')
			tflags->stat = true;
	}
	return true;
}

void initfList(struct env *flags) {
	flags->flags_mask = 0;
	flags->sort_flags_mask = 0;
	flags->stat = false;
}

void recursiveCompute(struct filesData file, bool format, struct env flags, char *path) {
	DIR				*dirfile;
	struct dirent	*readDir;
	
	if (file.type == 4) {
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, file.name);
		ft_printf("%s:\n", path);
	}
	dirfile = opendir(path);
	if (dirfile) {
		struct filesData	files[500];
		int		k = 0;
		size_t	size = 0;

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
		sortFiles(files, k, flags);
		filesPrinter(files, flags, k, size);
		putchar('\n');
		putchar('\n');
		if (flagIsSet(flags.flags_mask, 'R')) {
			for (int j = 0; files[j].type; j++) {
				if (files[j].type == 4)
					recursiveCompute(files[j], format, flags, path);
			}
		}
		closedir(dirfile);
		free(path);
	} else {
		return ;
	}
}

void compute(char **to_open, bool format, struct env flags) {
	DIR				*dirfile;
	struct dirent	*readDir;
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
			sortFiles(files, k, flags);
			filesPrinter(files, flags, k, size);
			putchar('\n');
			if (to_open[i + 1] != NULL || flagIsSet(flags.flags_mask, 'R'))
				putchar('\n');
			if (flagIsSet(flags.flags_mask, 'R')) {
				for (int j = 0; files[j].type; j++) {
					if (files[j].type == 4)
						recursiveCompute(files[j], format, flags, to_open[i]);
				}
			}
			closedir(dirfile);
		} else {
			ft_printf("ls: cannot access '%s': No such file or directory", to_open[i]);
		}
	}
}

int main(int ac, char **av) {
	struct env	flags;
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
				to_open[j] = NULL;
			}
		}
	}
	bool format = (j > 1) || flagIsSet(flags.flags_mask, 'R');

	compute(to_open, format, flags);
	return EXIT_SUCCESS;
}