void	sort_sprites(int *const order,
				const float *const distance, const int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i;
		while (j < count - 1)
		{
			if (distance[order[j]] > distance[order[j + 1]])
			{
				tmp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
