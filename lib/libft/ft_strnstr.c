/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:37:11 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:37:14 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *) haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}
