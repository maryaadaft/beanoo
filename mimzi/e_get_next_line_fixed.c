#include "get_next_line.h"
char *ft_strchr(char *s, int c) // good
{
	int i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return s + i;
		i++;
	}
	return NULL;
}
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}
size_t ft_strlen(char *s) // good
{
	size_t res = 0;
	while (s[res] != '\0')
	{
		res++;
	}
	return res;
}
void *ft_memmove(void *dest, const void *src, size_t n)
{
	// size_t i = ft_strlen((char *)src) - 1;
	size_t i;
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return dest;
}
// ================================================================
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1; // length of ret
	if (!s1 || !*s1)
		size1 = 0;
	else
		size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1); // malloc ret + buffer
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);		   // copy ret into tmp
	ft_memcpy(tmp + size1, s2, size2); // copy buffer into ret
	tmp[size1 + size2] = '\0';
	free(*s1); // free ret
	*s1 = tmp; // joined ret + b is now ret
	return 1;
}
int str_append_str(char **s1, char *s2)
{
	size_t size_two = ft_strlen(s2);
	return str_append_mem(s1, s2, size_two);
}
char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp;
	ssize_t read_ret = 1;
	while (read_ret > 0)
	{
		tmp = ft_strchr(b, '\n'); // check if ret has a new line
		if (tmp)
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				free(ret);
				return NULL;
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			return ret;
		}
		if (!str_append_str(&ret, b))
			return NULL;
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			b[0] = '\0';
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		b[read_ret] = 0;
	}
	if (ret && *ret == '\0')
	{
		free(ret);
		return NULL;
	}
	return ret;
}

