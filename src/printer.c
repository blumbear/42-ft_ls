/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:16:58 by tom               #+#    #+#             */
/*   Updated: 2026/09/02 14:21:32 by tom              ###   ########.fr       */
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
}

void print_with_space(char *str){
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(str, 1);
}

void printOwner(struct filesData file) {
	if (file.owner != NULL) print_with_space(file.owner);
	else ft_putstr_fd("NULL ", 1);
}

void printGroup(struct filesData file) {
	if (file.group != NULL) print_with_space(file.group);
	else ft_putstr_fd("NULL ", 1);
}

void printLink(struct filesData file) {
	ft_putnbr_fd(file.stat->st_nlink, 1);
}

void printSize(struct filesData file) {
	ft_putnbr_fd(file.stat->st_size, 1);
}

void printLastModification(struct filesData file) {
	char *lastUse = ctime(&file.stat->st_mtime);
	lastUse += 3;
	lastUse[13] = 0;
	print_with_space(lastUse);
	ft_putchar_fd(' ', 1);
}

void printGroupFormat(struct filesData file, struct column_max_widths w) {
	printPerm(file);
	for (int i = -1; i < w.links - nbrlen(file.stat->st_nlink) ;i++) ft_putchar_fd(' ', 1);
	printLink(file);

	for (size_t i = -1; i < w.group - ft_strlen(file.group) ;i++) ft_putchar_fd(' ', 1);
	printGroup(file);

	for (int i = -1; i < w.size - nbrlen(file.stat->st_size) ;i++) ft_putchar_fd(' ', 1);
	printSize(file);

	printLastModification(file);
}

void printLongFormat(struct filesData file, struct column_max_widths w) {
	printPerm(file);
	
	for (int i = -1; i < w.links - nbrlen(file.stat->st_nlink) ;i++) ft_putchar_fd(' ', 1);
	printLink(file);

	for (size_t i = -1; i < w.owner - ft_strlen(file.owner) ;i++) ft_putchar_fd(' ', 1);
	printOwner(file);

	for (size_t i = -1; i < w.group - ft_strlen(file.group) ;i++) ft_putchar_fd(' ', 1);
	printGroup(file);

	for (int i = -1; i < w.size - nbrlen(file.stat->st_size) ;i++) ft_putchar_fd(' ', 1);
	printSize(file);

	printLastModification(file);
}

void printLine(uint32_t flags_mask, struct filesData file, struct column_max_widths w) {

	if (flagIsSet(flags_mask, 's')) {
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd((file.stat->st_blocks * 512 + 1023) /1024, 1);
	}

	if (flagIsSet(flags_mask, 'g')) printGroupFormat(file, w);
	else if (flagIsSet(flags_mask, 'l')) printLongFormat(file, w);
	
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(file.name, 1);

	if (flagIsSet(flags_mask, 'l') || flagIsSet(flags_mask, 'g')) write(1, "\n", 1);

}

void filesPrinter(struct filesData files[250], struct env env, int last, size_t size) {
	if (flagIsSet(env.flags_mask, 'l') || flagIsSet(env.flags_mask, 's') || flagIsSet(env.flags_mask, 'g')) {
		ft_putstr_fd("total ", 1);
		ft_putnbr_fd(size, 1);
		ft_putchar_fd('\n', 1);
	}

	struct column_max_widths w = {10, 1, 0, 0, 0, 12};
	if (flagIsSet(env.flags_mask, 'l') || flagIsSet(env.flags_mask, 'g'))
		w = calculate_widths(files, last);

	if (flagIsSet(env.sort_flags_mask, 'r')) {
		last--;
		for (; last >= 0; last--){
			printLine(env.flags_mask, files[last], w);
			if (files[last].stat) free(files[last].stat);
		}
	} else {
		for (int k = 0; k < last; k++){
			printLine(env.flags_mask, files[k], w);
			if (files[k].stat) free(files[k].stat);
		}
	}
}