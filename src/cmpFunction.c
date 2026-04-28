#include "ft_ls.h"

int	cmpSize(const void *a, const void *b) {
	int res = ((struct filesData *)b)->stat->st_size - ((struct filesData *)a)->stat->st_size;
	if (res == 0)
		return cmpName(a, b);
	return res;
}

int	cmpTime(const void *a, const void *b) {
	unsigned int res = ((struct filesData *)b)->stat->st_mtime - ((struct filesData *)a)->stat->st_mtime;
	if (res == 0)
		return cmpName(a, b);
	return res;
}

int	cmpName(const void *a, const void *b) {
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