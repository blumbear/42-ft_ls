#include "ft_ls.h"

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

void printLongFormat(struct filesData file) {
	printPerm(file);
}