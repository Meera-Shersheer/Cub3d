/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:34:03 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 13:19:02 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	new = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (new);
}
/*void test_ft_strjoin(const char *s1, const char *s2)
{
    char *result = ft_strjoin(s1, s2);

    if (result != NULL)
    {
        printf("Result of joining \"");
	printf("%s", s1 ? s1 : "NULL");
	printf("\" and \"");
	printf("%s", s2 ? s2 : "NULL");
	printf("\": \"%s\"\n", result);
        free(result);  // Free the allocated memory
    }
    else
    {
        printf("Memory allocation failed or input strings are NULL\n");
    }
}

int main()
{
    // Example test cases
    test_ft_strjoin("Hello, ", "world!");
    test_ft_strjoin("42", " School");
    test_ft_strjoin(NULL, "world!");
    test_ft_strjoin("Hello, ", NULL);
    test_ft_strjoin(NULL, NULL);
    test_ft_strjoin("", "Empty string test");
    test_ft_strjoin("Non-empty", "");

    return 0;
}*/
