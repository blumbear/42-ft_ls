#include "ft_ls.h"

int	cmpSize(const void *a, const void *b) {
	int res = ((struct filesData *)b)->stat->st_size - ((struct filesData *)a)->stat->st_size;
	if (res == 0)
		return cmpName(a, b);
	return res;
}

int	cmpTime(const void *a, const void *b) {
	unsigned int res = ((struct filesData *)b)->stat->st_mtim.tv_sec - ((struct filesData *)a)->stat->st_mtim.tv_sec;
	if (res == 0) {
		unsigned int res = ((struct filesData *)b)->stat->st_mtim.tv_nsec - ((struct filesData *)a)->stat->st_mtim.tv_nsec;
		if (res == 0)
			return cmpName(a, b);
		return res;
	}
	return res;
}

int	cmpName(const void *a, const void *b) {

	char *na = ((struct filesData *)a)->name;
	char *nb = ((struct filesData *)b)->name;

	while (*na == '.') na++;
	while (*nb == '.') nb++;
	while (*na && tolower((unsigned char)*na) == tolower((unsigned char)*nb))
    {
        na++;
        nb++;
    }
	
	return tolower((unsigned char)*na) - tolower((unsigned char)*nb);
}

int cmpNameMain(const void *a, const void *b) {
	char *na = *(char * const *)a;
	char *nb = *(char * const *)b;

	while (*na == '.') na++;
	while (*nb == '.') nb++;
	while (*na && tolower((unsigned char)*na) == tolower((unsigned char)*nb))
    {
        na++;
        nb++;
    }

	return tolower((unsigned char)*na) - tolower((unsigned char)*nb);
}