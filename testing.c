
#include "libft/libft.h"

char	**ft_split_v2(char const *s, char c, char d);

int main(void)
{
	int	i;
	char	c;
	char **arr;

	i = -1;
	c = 39;
	arr = ft_split_v2("awk {count++} END {print count}", ' ', c);
	while (arr[++i])
		ft_printf("%s\n", arr[i]);
	return (0);
}
