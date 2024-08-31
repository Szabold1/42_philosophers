/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:14:08 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/21 16:23:59 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// destroy the forks mutexes and free the memory
void	clean_up_forks(pthread_mutex_t *forks, int i)
{
	while (--i >= 0)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
			err_msg(MUTEX_DESTROY_ERR);
	}
	free(forks);
	forks = NULL;
}

// free the memory and destroy the mutexes
void	clean_up(t_data *data)
{
	if (data->forks)
		clean_up_forks(data->forks, data->nb_of_philos);
	if (pthread_mutex_destroy(&data->print_lock) != 0)
		err_msg(MUTEX_DESTROY_ERR);
	if (pthread_mutex_destroy(&data->lock) != 0)
		err_msg(MUTEX_DESTROY_ERR);
	if (data->philos)
		free(data->philos);
}
