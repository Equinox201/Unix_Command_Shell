#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	ft_partition(char **lst, int low, int high)
{
	char	*pivot;
	int		a;
	int		b;
	int		len;

	a = low - 1;
	b = low;
	pivot = lst[high];
	while (b < high)
	{
		len = ft_strfind(pivot, '=');
		if (ft_strncmp(lst[b], pivot, len) < 0)
		{
			a++;
			ft_swap(&lst[a], &lst[b]);
		}
		b++;
	}
	ft_swap(&lst[a + 1], &lst[high]);
	return (a + 1);
}

void	ft_quicksort(char **order, int low, int high)
{
	int	part;

	if (low < high)
	{
		part = ft_partition(order, low, high);
		ft_quicksort(order, low, part - 1);
		ft_quicksort(order, part + 1, high);
	}
}

void	ft_quicksort_prep(t_data *data, char **order, int count)
{
	t_env	*tmp;
	int		a;

	a = 0;
	tmp = data->env;
	while (tmp)
	{
		if (ft_isalpha(tmp->key[0]) == 1)
		{
			order[a] = ft_strjoin("export ", tmp->original);
			if (!order[a])
				return ;
			a++;
		}
		tmp = tmp->next;
	}
	ft_quicksort(order, 0, count - 1);
}
