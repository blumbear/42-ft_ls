/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:49:46 by ttaquet           #+#    #+#             */
/*   Updated: 2023/10/20 16:07:14 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char	*s, unsigned int start, size_t	len)
{
	size_t	i;
	char	*sub;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = (size_t)ft_strlen(s + start);
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		sub[i] = (char)s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
