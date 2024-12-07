/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:22:18 by yilim             #+#    #+#             */
/*   Updated: 2024/09/24 23:22:18 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	action(int sig)
{
	(void)sig;
}

static void	send_bit(int pid, char c)
{
	int		bit;

	bit = 8;
	while (bit--)
	{
		if (c >> bit & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

static void	send_char(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_bit(pid, str[i]);
	send_bit(pid, '\0');
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_char(ft_atoi(argv[1]), argv[2]);
	return (0);
}
