#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

char *ft_strcat(char *dst, const char *src)
{
    size_t  dst_idx; // To find the end of dst
    size_t  src_idx; // To iterate through src

    dst_idx = 0;
    while (dst[dst_idx])
        dst_idx++;
    src_idx = 0;
    while (src[src_idx])
    {
        dst[dst_idx] = src[src_idx];
        dst_idx++;
        src_idx++;
    }
    dst[dst_idx] = '\0';
    return (dst);
}
