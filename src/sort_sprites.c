/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:29:39 by edgribei          #+#    #+#             */
/*   Updated: 2025/12/22 18:29:40 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
