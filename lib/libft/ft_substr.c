/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:38:25 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:38:27 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
/*
void test_ft_substr() {
    char *original;
    char *substring;

    // Test case 1: Substring in the middle of the string
    original = "Hello, World!";
    substring = ft_substr(original, 7, 5);  // Extracts "World"
    if (substring == NULL) {
        printf("Test case 1 failed: ft_substr returned NULL.\n");
    } else if (strcmp(substring, "World") != 0) {
        printf("Test case 1 failed: Expected 'World', got '%s'.\n", substring);
    } else {
        printf("Test case 1 passed.\n");
    }
    free(substring);  // Free allocated memory
    }
int main() {
    test_ft_substr();
    return 0;
}
*/
