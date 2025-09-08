/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:33:09 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:33:10 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (!dst && !src)
		return (NULL);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (n > 0)
	{
		*(tmp_dst++) = *(tmp_src++);
		n--;
	}
	return (dst);
}
