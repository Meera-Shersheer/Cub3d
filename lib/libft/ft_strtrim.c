/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:38:55 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:38:56 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	while (s1[end] && ft_strchr(set, s1[end]))
		--end;
	trimmed = ft_substr(s1, start, end - start + 1);
	return (trimmed);
}
/*
void test_ft_strtrim(const char *s1, const char *set)
{
    char *result = ft_strtrim(s1, set);
    
    if (result != NULL)
    {
        printf("Original: \"%s\", Set: \"%s\" -> Trimmed: \"%s\"\n", 
               s1 ? s1 : "NULL", set ? set : "NULL", result);
        free(result); // Free the allocated memory
    }
    else
    {
        printf("Memory allocation failed for input: \"%s\", 
        Set: \"%s\"\n", s1, set);
    }
}

int main()
{
    // Example test cases
    test_ft_strtrim("ababaaaMy name is Simonbbaaabbad", "ab");
    test_ft_strtrim("  Hello, World!  ", " ");
    test_ft_strtrim("!!Good Morning!!", "!");
    test_ft_strtrim("1234Test1234", "1234");
    test_ft_strtrim("", "abc"); 
    test_ft_strtrim("abc", "");
    test_ft_strtrim("   ", " ");
    
    return 0;
}
*/
