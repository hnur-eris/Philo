/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeris <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:41:58 by haeris            #+#    #+#             */
/*   Updated: 2023/01/06 16:42:01 by haeris           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		return (-1);
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	return (result);
}

unsigned long long	now_time(void)
{
	struct timeval			tv;
	static unsigned long	first_time = 0;

	gettimeofday(&tv, NULL);
	if (first_time == 0)
		first_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - first_time);
}

void	my_usleep(int ms)
{
	unsigned long long	time;

	time = now_time();
	while (now_time() < time + ms)
	{
		usleep(1);
	}
}

void	write_case(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	pthread_mutex_lock(&(philo->table->death_check_mutex));
	if (philo->table->death_num == 0)
	{
		pthread_mutex_lock(&philo->table->time_mutex);
		printf("%lld %d %s\n", now_time(), philo->philo_id, message);
		pthread_mutex_unlock(&philo->table->time_mutex);
	}
	pthread_mutex_unlock(&(philo->table->death_check_mutex));
	pthread_mutex_unlock(&philo->table->write_mutex);
}
