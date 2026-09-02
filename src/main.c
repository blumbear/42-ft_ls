/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:30:48 by tom               #+#    #+#             */
/*   Updated: 2026/09/02 15:20:10 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void sortFiles(struct filesData files[250], int k, struct env flags) {
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
			ft_putstr_fd("ls: invalid option -- '", 1);
			ft_putchar_fd(c, 1);
			ft_putstr_fd("'\n", 1);
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

void recursiveCompute(struct filesData file, bool several_folder, struct env flags, char *path) {
	DIR				*dirfile;
	struct dirent	*readDir;
	
	if (file.type == 4) {
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, file.name);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(":\n", 1);
	}
	dirfile = opendir(path);
	if (dirfile) {
		struct filesData	files[250];
		int		k = 0;
		size_t	size = 0;
		ft_bzero(files, sizeof(files));

		while ((readDir = readdir(dirfile)) != NULL) {
				
				if (readDir->d_name[0] == '.' && !flagIsSet(flags.flags_mask, 'a'))
					continue;
					
				strncpy(files[k].name, readDir->d_name, 255);
				files[k].name[255] = '\0';
				files[k].type = readDir->d_type;
				
				if (flags.stat) {
					files[k].stat = malloc(sizeof(struct stat));
					
					char full_path[512];
					snprintf(full_path, 512, "%s/%s", path, files[k].name);
					
					if (stat(full_path, files[k].stat) != 0) {
						free(files[k].stat);
						files[k].stat = NULL;
						k++;
						continue;
					}
					size += ((files[k].stat->st_blocks * 512 + 1023) / 1024);
					
					if (flagIsSet(flags.flags_mask, 'l')) {
						struct passwd *pw = getpwuid(files[k].stat->st_uid);
						if (pw != NULL) files[k].owner = pw->pw_name;
						else files[k].owner = NULL;
					}
					
					if (flagIsSet(flags.flags_mask, 'g') || flagIsSet(flags.flags_mask, 'l')) {
						struct group *gr = getgrgid(files[k].stat->st_gid);
						if (gr != NULL) files[k].group = gr->gr_name;
						else files[k].group = NULL;
					}
				} else files[k].stat = NULL;
				k++;
			}
		sortFiles(files, k, flags);
		filesPrinter(files, flags, k, size);
		putchar('\n');
		putchar('\n');
		if (flagIsSet(flags.flags_mask, 'R')) {
			if (flagIsSet(flags.sort_flags_mask, 'r')) {
				for (int j = k - 1; j >= 0; j--) {
					if (files[j].type == 4)
						recursiveCompute(files[j], several_folder, flags, path);
				}
			} else {
				for (int j = 0; j < k; j++) {
					if (files[j].type == 4)
						recursiveCompute(files[j], several_folder, flags, path);
				}
			}
		}
		closedir(dirfile);
		free(path);
	} else {
		return ;
	}
}

void handle_d_flag(char **to_open,  uint64_t flags) {
	struct stat sb;
	struct filesData file;

	for (int i = 0; to_open[i]; i++) {
		if (stat(to_open[i], &sb) == 0)
			continue;
		else {
			ft_putstr_fd("ls: cannot access '", 1);
			ft_putstr_fd(to_open[i], 1);
			ft_putstr_fd("': No such file or directory\n", 1);
			ft_putstr_fd(to_open[i], 1);
		}
	}
	struct column_max_widths w = {10, 1, 0, 0, 0, 12};
	for (int i = 0; to_open[i]; i++) {
		if (stat(to_open[i], &sb) == 0){
			strncpy(file.name, to_open[i], 255);
			file.type = (S_ISDIR(sb.st_mode)) ? 4 : 8;
			file.stat = &sb;
			printLine(flags, file, w);
		}
	}
	putchar('\n');
}

void compute(char **to_open, bool several_folder, struct env flags) {
	DIR				*dirfile;
	struct dirent	*readDir;

	if (flagIsSet(flags.flags_mask, 'd')) {
		handle_d_flag(to_open, flags.flags_mask);
		return ;
	}

	for (int i = 0; to_open[i]; i++) {
		dirfile = opendir(to_open[i]);
		if (dirfile) {
			struct filesData	files[250];
			int		k = 0;
			size_t	size = 0;
			ft_bzero(files, sizeof(files));

			if (several_folder == true) {
				ft_putstr_fd(to_open[i],1);
				ft_putstr_fd(":\n", 1);
			}
			while ((readDir = readdir(dirfile)) != NULL) {
				
				if (readDir->d_name[0] == '.' && !flagIsSet(flags.flags_mask, 'a'))
					continue;
					
				strncpy(files[k].name, readDir->d_name, 255);
				files[k].name[255] = '\0';
				files[k].type = readDir->d_type;
				
				if (flags.stat) {
					files[k].stat = malloc(sizeof(struct stat));
					
					char full_path[512];
					snprintf(full_path, 512, "%s/%s", to_open[i], files[k].name);
					
					if (stat(full_path, files[k].stat) != 0) {
						free(files[k].stat);
						files[k].stat = NULL;
						k++;
						continue;
					}
					size += ((files[k].stat->st_blocks * 512 + 1023) / 1024);
					
					if (flagIsSet(flags.flags_mask, 'l')) {
						struct passwd *pw = getpwuid(files[k].stat->st_uid);
						if (pw != NULL) files[k].owner = pw->pw_name;
						else files[k].owner = NULL;
					}
					
					if (flagIsSet(flags.flags_mask, 'g') || flagIsSet(flags.flags_mask, 'l')) {
						struct group *gr = getgrgid(files[k].stat->st_gid);
						if (gr != NULL) files[k].group = gr->gr_name;
						else files[k].group = NULL;
					}
				} else files[k].stat = NULL;
				k++;
			}
			sortFiles(files, k, flags);
			filesPrinter(files, flags, k, size);
			putchar('\n');
			if (to_open[i + 1] != NULL || flagIsSet(flags.flags_mask, 'R'))
				putchar('\n');
			if (flagIsSet(flags.flags_mask, 'R')) {
				if (flagIsSet(flags.sort_flags_mask, 'r')) {
				for (int j = k - 1; j >= 0; j--) {
					if (files[j].type == 4)
						recursiveCompute(files[j], several_folder, flags, ".");
				}
			} else {
				for (int j = 0; j < k; j++) {
					if (files[j].type == 4)
						recursiveCompute(files[j], several_folder, flags, ".");
				}
			}
			closedir(dirfile);
		} else {
			ft_putstr_fd("ls: cannot access '", 1);
			ft_putstr_fd(to_open[i], 1);
			ft_putstr_fd("': No such file or directory\n", 1);
		}
	}
}}

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
	bool several_folder = (j > 1) || flagIsSet(flags.flags_mask, 'R');

	compute(to_open, several_folder, flags);
	return EXIT_SUCCESS;
}