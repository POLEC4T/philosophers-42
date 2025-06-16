/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:58:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/06/12 13:45:04 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	is_out_of_int_range(unsigned long res, int sign)
{
	if (sign == 1 && res > (unsigned long)INT_MAX)
		return (1);
	if (sign == -1 && res > (unsigned long)INT_MAX + 1)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i++] - '0';
		if (is_out_of_int_range(res, sign))
			return (-1);
	}
	return (res * sign);
}
