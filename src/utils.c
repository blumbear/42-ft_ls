/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 18:20:58 by tom               #+#    #+#             */
/*   Updated: 2026/09/22 18:03:57 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strjoin_wf(char *s1, char *s2, int f)
{
	char			*joinedstr;
	int				i;
	unsigned int	tmp;

	i = 0;
	tmp = (unsigned int)(ft_strlen(s1) + ft_strlen(s2));
	joinedstr = malloc((tmp + 1) * sizeof(char));
	if (!joinedstr)
		return (NULL);
	for (int j = 0; s1[j]; i++, j++) {
		joinedstr[i] = s1[j]; 
	}
	for (int j = 0; s2[j]; i++, j++) {
		joinedstr[i] = s2[j]; 
	}
	joinedstr[i] = '\0';
	if (f == 0)
		return (joinedstr);
	if (f == 1) {
		free(s1);
	} else if (f == 2) {
		free(s2);
	} else {
		free(s1);
		free(s2);
	}
	return (joinedstr);
}

bool check_dot_entries(char *name) {
	if (name[0] == '.' && name[1] == 0)
		return false;
	else if (name[0] == '.' && name[1] == '.' && name[2] == 0)
		return false;
	return true;
}