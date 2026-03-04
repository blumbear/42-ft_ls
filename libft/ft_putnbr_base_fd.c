/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:58:43 by ttaquet           #+#    #+#             */
/*   Updated: 2026/03/04 11:31:57 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(size_t n, char *base, int fd)
{
	if (n >= ft_strlen(base))
		ft_putnbr_base_fd(n / ft_strlen(base), base, fd);
	ft_putchar_fd(base[n % ft_strlen(base)], fd);
}