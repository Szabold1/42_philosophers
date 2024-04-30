/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:58:26 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/30 16:29:18 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// printf 'str' to 'fd'
static void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(fd, &str[i++], 1);
}

// print an error message to stderr
void	err_msg(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
}

// convert a string to an integer and return it
// return ERR if 'str' is not a valid positive integer
int	atoi_philo(char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	if (!str)
		return (ERR);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERR);
		num = num * 10 + (str[i] - '0');
		if (num > MAX_INT)
			return (ERR);
		i++;
	}
	return (num);
}
