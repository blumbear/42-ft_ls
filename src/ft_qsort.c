#include <stddef.h>

static void swap_bytes(char *a, char *b, size_t size)
{
    char tmp;

    while (size--)
    {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

void ft_qsort(void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *))
{
    char    *arr;
    size_t  i;
    size_t  store;

    arr = base;
    while (nmemb > 1 && size > 0)
    {
        swap_bytes(arr, arr + (nmemb / 2) * size, size);
        store = 0;
        i = 0;
        while (++i < nmemb)
            if (compar(arr + i * size, arr) < 0)
                swap_bytes(arr + ++store * size, arr + i * size, size);
        swap_bytes(arr, arr + store * size, size);
        if (store < nmemb - store - 1)
        {
            ft_qsort(arr, store, size, compar);
            arr += (store + 1) * size;
            nmemb -= store + 1;
        }
        else
        {
            ft_qsort(arr + (store + 1) * size, nmemb - store - 1, size, compar);
            nmemb = store;
        }
    }
}