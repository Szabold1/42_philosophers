/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:51:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/21 16:40:21 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check continuously for the end of the simulation
// return true if a philosopher died or all philosophers ate all meals
static bool	check_end(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->lock);
		while (i < data->nb_of_philos && data->died == false)
		{
			if (get_current_time() - data->philos[i].last_meal_time
				> data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				data->died = true;
				return (pthread_mutex_unlock(&data->lock), true);
			}
			if (data->nb_of_full_philos == data->nb_of_philos)
				return (pthread_mutex_unlock(&data->lock), true);
			i++;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(1000);
	}
	return (false);
}

// join the threads of the philosophers
static void	join_threads(t_data *data, int i)
{
	while (--i >= 0)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			err_msg("pthread_join failed");
	}
}

// start simulation by creating the threads for the philosophers
// return OK if successful, ERR if not
int	simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	if (data->start_time == -1)
		return (ERR);
	while (i < data->nb_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]) != 0)
			return (join_threads(data, i), err_msg(THREAD_CREATE_ERR), ERR);
		i++;
	}
	check_end(data);
	join_threads(data, data->nb_of_philos);
	return (OK);
}
