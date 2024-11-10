/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:11:46 by akloster          #+#    #+#             */
/*   Updated: 2024/10/28 16:11:46 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	overflow(long sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_mod_atoi(const char *str)
{
	int		i;
	long	sign;
	long	nb;
	long	temp;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = nb;
		nb = nb * 10 + str[i++] - '0';
		if (temp > nb)
			return (overflow(sign));
	}
	nb = (nb * sign);
	return ((int) nb);
}
