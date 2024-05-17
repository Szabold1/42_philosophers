/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:00:01 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/17 09:35:20 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// take the right fork if the philosopher can
static void	take_right_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->fork_right_index]);
	print_status(philo, "has taken a fork");
}

// take the left fork if the philosopher can
static void	take_left_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->fork_left_index]);
	print_status(philo, "has taken a fork");
}

// take the forks in a specific order to avoid deadlock
void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	else
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

// put down the forks in a specific order to avoid deadlock
void	put_down_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->fork_left_index]);
		pthread_mutex_unlock(&data->forks[philo->fork_right_index]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->fork_right_index]);
		pthread_mutex_unlock(&data->forks[philo->fork_left_index]);
	}
}
