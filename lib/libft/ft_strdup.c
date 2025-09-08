/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:31:57 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:31:59 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	i;

	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/*
// Test function for ft_strdup
void test_ft_strdup() {
    // Test case 1: Normal case
    char *original = "Hello, World!";
    char *duplicate = ft_strdup(original);
    if (duplicate == NULL) {
        printf("Test case 1 failed: ft_strdup returned NULL.\n");
        return;
    }
    if (strcmp(original, duplicate) != 0) {
        printf("Test case 1 failed:  not match.\n");
    } else {
        printf("Test case 1 passed.\n");
    }
    free(duplicate);  // Free allocated memory
}

int main() {
    test_ft_strdup();
    return 0;
}*/
