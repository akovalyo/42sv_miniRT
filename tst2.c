#include "libft.h"
#include <error.h>

// void err()
// {
// 	exit(-1);
// }

int main()
{
	char a[] = " ";
	char **tab;
	int i = 0;
	tab = ft_strsplit(a, ' ');

	while (tab[i])
	{
		ft_printf("|%s|\n", tab[i]);
		i++;
	}
	ft_printf("%d\n", ft_strarraylen(tab));
	// if (ft_strncmp(tab[0], "R", 2) == 0)
	// 	err();
	ft_printf("OK\n");
	return (0);
}