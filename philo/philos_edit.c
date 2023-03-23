/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeris <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:41:50 by haeris            #+#    #+#             */
/*   Updated: 2023/01/06 16:41:51 by haeris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	edit_philos(int i, t_table *table)
{
	t_philo	philo;

	philo.philo_id = i + 1;
	philo.philo_eat_num = 0;
	philo.last_meal_time = 0;
	philo.table = table;
	philo.death_time = table->death_time;
	philo.eat_time = table->eat_time;
	philo.sleep_time = table->sleep_time;
	philo.eat_num = table->eat_num;
	pthread_mutex_init(&philo.right_fork, NULL);
	return (philo);
}

void	create_philos(t_table	*table)
{
	int		i;

	i = -1;
	while (++i < table->philo_num)
		table->philos[i] = edit_philos(i, table);
	i = -1;
	while (++i < table->philo_num)
	{
		if (i == 0)
			table->philos[i].left_fork = \
				&table->philos[table->philo_num - 1].right_fork;
		else
			table->philos[i].left_fork = &table->philos[i - 1].right_fork;
	}
}

int	create_thread(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		if ((pthread_create(&table->philos[i].philo, NULL, \
			&lifecycle, (void *)&table->philos[i])) != 0)
		{
			printf("Beklenmeyen bir hata oluştu\n");
			return (0);
		}
	}
	return (1);
}
