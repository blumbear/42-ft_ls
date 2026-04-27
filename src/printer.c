/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:16:58 by tom               #+#    #+#             */
/*   Updated: 2026/04/27 17:45:15 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void printPerm(struct filesData file){
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

void printUser(struct filesData file) {
	struct passwd *pw = getpwuid(file.stat->st_uid);
	if (pw != NULL) ft_printf("%s ", pw->pw_name);
	else ft_printf("NULL ");
}

void printGroup(struct filesData file) {
	struct group *pw = getgrgid(file.stat->st_gid);
	if (pw != NULL) ft_printf("%s ", pw->gr_name);
	else ft_printf("NULL ");
}

void printLink(struct filesData file) {
	ft_printf("%d ", file.stat->st_nlink);
}

void printSize(struct filesData file) {
	ft_printf("%d ", file.stat->st_size);
}

void printLastModification(struct filesData file) {
	char *test = ctime(&file.stat->st_mtime);
	test+=3;
	test[13] = 0;
	ft_printf("%s ", test);
}

void printGroupFormat(struct filesData file) {
	printPerm(file);
	printLink(file);
	printGroup(file);
	printSize(file);
	printLastModification(file);
}

void printLongFormat(struct filesData file) {
	printPerm(file);
	printLink(file);
	printUser(file);
	printGroup(file);
	printSize(file);
	printLastModification(file);
}

void printLine(uint32_t flags_mask, struct filesData files) {
	if (flagIsSet(flags_mask, 's')) ft_printf("  %d ", (files.stat->st_blocks * 512 + 1023) / 1024);
	
	if (flagIsSet(flags_mask, 'g')) printGroupFormat(files);
	else if (flagIsSet(flags_mask, 'l')) printLongFormat(files);

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