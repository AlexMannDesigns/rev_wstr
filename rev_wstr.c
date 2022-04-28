/*
Assignment name  : rev_wstr
Expected files   : rev_wstr.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a program that takes a string as a parameter, and prints its words in 
reverse order.

A "word" is a part of the string bounded by spaces and/or tabs, or the 
begin/end of the string.

If the number of parameters is different from 1, the program will display 
'\n'.

In the parameters that are going to be tested, there won't be any "additional" 
spaces (meaning that there won't be additionnal spaces at the beginning or at 
the end of the string, and words will always be separated by exactly one space).

Examples:

$> ./rev_wstr "le temps du mepris precede celui de l'indifference" | cat -e
l'indifference de celui precede mepris du temps le$
$> ./rev_wstr "abcdefghijklm"
abcdefghijklm
$> ./rev_wstr "il contempla le mont" | cat -e
mont le contempla il$
$> ./rev_wstr | cat -e
$
$>
*/

#include <unistd.h>
#include <stdlib.h>

static int	is_ws(char c)
{
	if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	return (0);
}

static size_t	word_count(char *str)
{
	size_t	wc, i;

	wc = i = 0;
	while (str[i])
	{
		if (!is_ws(str[i]))
		{
			wc++;
			while (!is_ws(str[i + 1]))
				i++;
		}
		i++;
	}
	return (wc);
}

static size_t	ft_substrlen(char *str)
{
	size_t i;

	i = 0;
	while (!is_ws(str[i]))
		i++;
	return (i);
}

static char	*copy_word(char *str, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *) malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

static char	**rev_wstr(char *str)
{
	char **arr;
	size_t wc, i, j, len;

	wc = word_count(str);
	arr = (char **) malloc(sizeof(char *) * (wc + 1));
	arr[wc] = NULL;
	if (wc == 0)
		return (arr);
	j = wc - 1;
	i = 0;
	while (str[i])
	{
		if (!is_ws(str[i]))
		{
			len = ft_substrlen(str + i);
			arr[j] = copy_word(str + i, len);
			j--;
			while (!is_ws(str[i + 1]))
				i++;
		}
		i++;
	}
	return (arr);
}

static void	ft_putstr(char *s)
{
	write(1, s, ft_substrlen(s));
}

int main(int ac, char **av)
{
	char	**arr;
	size_t	i;	

	if (ac == 2)
	{
		arr = rev_wstr(av[1]);
		i = 0;
		while (arr[i])
		{
			ft_putstr(arr[i]);
			if (arr[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
