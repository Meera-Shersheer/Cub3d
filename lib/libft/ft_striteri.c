/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:39:55 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:40:11 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		(*f)(i, (s + i));
		++i;
	}
}
/*
void sample_function(unsigned int index, char *c) {
    *c = *c + 1; // Example modification: increment character
    printf("Index: %u, Character: %c\n", index, *c); 
    // Print index and modified character
}

void test_ft_striteri() {
    char str[] = "hello";
    printf("Original string: %s\n", str);
    
    ft_striteri(str, sample_function);
    
    printf("Modified string: %s\n", str); // Should print "ifmmp"
}

int main() {
    test_ft_striteri(); // Run the test
    return 0;
}
*/
