/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   printerUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 12:35:24 by tom               #+#    #+#             */
/*   Updated: 2026/09/02 12:35:34 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int nbrlen(unsigned int n) {
	int res = 1;
	while (n >= 10) {
		n = n / 10;
		res++;
	}
	return res;
}

struct column_max_widths calculate_widths(struct filesData files[], int last) {
	struct column_max_widths w = {10, 0, 0, 0, 0, 12};
	
	for (int i = 0; i < last; i++) {
		if (!files[i].stat)
			continue;
		
		int links_len = nbrlen(files[i].stat->st_nlink);
		if (links_len > w.links) w.links = links_len;

		struct passwd *pw = getpwuid(files[i].stat->st_uid);
		if (pw) {
			int owner_len = ft_strlen(pw->pw_name);
			if (owner_len > w.owner) w.owner = owner_len;
		}
		
		struct group *gr = getgrgid(files[i].stat->st_gid);
		if (gr) {
			int group_len = ft_strlen(gr->gr_name);
			if (group_len > w.group) w.group = group_len;
		}
		
		int size_len = nbrlen(files[i].stat->st_size);
		if (size_len > w.size) w.size = size_len;
		
	}
	return w;
}
