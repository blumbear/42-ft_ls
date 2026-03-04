/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:07:33 by ttaquet           #+#    #+#             */
/*   Updated: 2023/10/20 15:03:56 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*str, int c)
{
	int	i;
	int	tmp;

	tmp = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c % 256)
			tmp = i;
		i++;
	}
	if (tmp == -1)
	{
		if ((unsigned char)c == '\0')
			return ((char *)str + i);
		return (NULL);
	}
	return ((char *)str + tmp);
}
