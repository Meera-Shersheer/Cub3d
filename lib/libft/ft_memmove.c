/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:12:15 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 14:12:17 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}
/*
#include <stdio.h>
int	main()
{
	char	buff[] = "hello world";
	char	*s1 = buff + 1;
	char	*d1 = buff;
	char	*s2 = buff + 1;
	char	*d2 = buff;
	ft_memmove(d1, s1, 7);
	memmove(d2, s2, 7);
	printf("%s\n", d1);
	printf("%s\n", d2);
}*/
