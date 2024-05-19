/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:51:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/19 17:58:17 by bszabo           ###   ########.fr       */
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
				pthread_mutex_unlock(&data->lock);
				print_status(&data->philos[i], "died");
				pthread_mutex_lock(&data->lock);
				data->died = true;
				return (pthread_mutex_unlock(&data->lock), true);
			}
			if (data->nb_of_full_philos == data->nb_of_philos)
				return (pthread_mutex_unlock(&data->lock), true);
			i++;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(500);
	}
	return (false);
}

// join the threads of the philosophers
static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
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
			return (join_threads(data), err_msg(THREAD_CREATE_ERR), ERR);
		i++;
	}
	check_end(data);
	join_threads(data);
	return (OK);
}
