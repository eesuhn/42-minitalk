/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:21:08 by yilim             #+#    #+#             */
/*   Updated: 2024/09/24 23:21:08 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

static void	action(int sig, siginfo_t *t_i, void *ctx)
{
	static int				bit;
	static unsigned char	c;

	(void)ctx;
	c |= (sig == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		if (!c)
		{
			kill(t_i->si_pid, SIGUSR2);
			ft_putchar_fd('\n', 1);
		}
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sa;

	ft_printf("Server PID: %d\n", getpid());
	s_sa.sa_sigaction = action;
	s_sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sa, 0);
	sigaction(SIGUSR2, &s_sa, 0);
	while (1)
		pause();
	return (0);
}
