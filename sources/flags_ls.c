/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:37:53 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/17 15:37:56 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		is_lsflag(unsigned int *flags, char c)
{
	if (c == 'a')		
		*flags = *flags | A_LOW;
	else if (c == 'A')
		*flags = *flags | A_UPP;
	else if (c == 'l')
		*flags = *flags | L_LOW;
	else if (c == 't')
		*flags = *flags | T_LOW;
	else if (c == 'r')
		*flags = *flags | R_LOW;
	else if (c == 'R')
		*flags = *flags | R_UPP;
	else
		return (0);
	return (1);
}

void	set_lsflags(unsigned int *flags, char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (!is_lsflag(flags, s[i]))
			ft_printf("illegal flag: %c\n", s[i]);
}