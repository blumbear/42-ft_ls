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
	const char *fa = ((const struct filesData *)a)->name;
    const char *fb = ((const struct filesData *)b)->name;
    const char *na = fa;
    const char *nb = fb;

    while (*na == '.') na++;
    while (*nb == '.') nb++;
    while (*na && tolower((unsigned char)*na) == tolower((unsigned char)*nb))
    {
        na++;
        nb++;
    }
    int diff = tolower((unsigned char)*na) - tolower((unsigned char)*nb);
    if (diff != 0)
        return diff;
    return ft_strncmp(fa, fb, 256);
}

int cmpNameMain(const void *a, const void *b) {
	const char *fa = ((const struct filesData *)a)->name;
    const char *fb = ((const struct filesData *)b)->name;
    const char *na = fa;
    const char *nb = fb;

    while (*na == '.') na++;
    while (*nb == '.') nb++;
    while (*na && tolower((unsigned char)*na) == tolower((unsigned char)*nb))
    {
        na++;
        nb++;
    }
    int diff = tolower((unsigned char)*na) - tolower((unsigned char)*nb);
    if (diff != 0)
        return diff;
    return ft_strncmp(fa, fb, 256);
}