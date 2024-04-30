/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:40 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/30 16:25:19 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check number of arguments and if they are valid
// return OK if valid, ERR if invalid
int	check_args(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (err_msg("Invalid number of arguments\n"), ERR);
	i = 1;
	while (i < argc)
	{
		if (atoi_philo(argv[i]) == ERR)
			return (err_msg("Invalid argument\n"), ERR);
		i++;
	}
	return (OK);
}

int	main(int argc, char *argv[])
{
	if (check_args(argc, argv) == ERR)
		return (1);
	return (0);
}