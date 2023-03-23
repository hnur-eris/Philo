/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeris <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:40:56 by haeris            #+#    #+#             */
/*   Updated: 2023/01/06 16:40:58 by haeris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	write_case("philo has taken a fork", philo);
	pthread_mutex_lock(&philo->right_fork);
	write_case("philo has taken a fork", philo);
	write_case("philo is eating", philo);
	pthread_mutex_lock(&philo->table->eat_check_mutex);
	philo->philo_eat_num++;
	pthread_mutex_unlock(&philo->table->eat_check_mutex);
	my_usleep(philo->eat_time);
	pthread_mutex_lock(&philo->table->time_mutex);
	philo->last_meal_time = now_time();
	pthread_mutex_unlock(&philo->table->time_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	write_case("philo is sleeping", philo);
	my_usleep(philo->sleep_time);
	write_case("philo is thinking", philo);
	return (0);
}

void	lifecycle2(t_philo *philo)
{
	int		control;

	pthread_mutex_lock(&philo->table->death_check_mutex);
	control = philo->table->death_num;
	pthread_mutex_unlock(&philo->table->death_check_mutex);
	while (control == 0)
	{
		eat_cycle(philo);
		pthread_mutex_lock(&philo->table->death_check_mutex);
		control = philo->table->death_num;
		pthread_mutex_unlock(&philo->table->death_check_mutex);
	}
}

void	*lifecycle(void *tmp)
{
	int		control;
	t_philo	*philo;

	philo = (t_philo *)tmp;
	if (philo->philo_id % 2 == 0)
		my_usleep(1);
	if (philo->table->argc == 6)
	{
		pthread_mutex_lock(&philo->table->death_check_mutex);
		control = philo->table->death_num;
		pthread_mutex_unlock(&philo->table->death_check_mutex);
		while (control == 0 && philo->philo_eat_num < philo->eat_num)
		{
			eat_cycle(philo);
			pthread_mutex_lock(&philo->table->death_check_mutex);
			control = philo->table->death_num;
			pthread_mutex_unlock(&philo->table->death_check_mutex);
		}
	}
	else
		lifecycle2(philo);
	return (0);
}
