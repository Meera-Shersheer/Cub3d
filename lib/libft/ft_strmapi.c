/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:35:24 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:35:25 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
/*
char sample_function(unsigned int index, char c) {
    //Example modification: increment character by 1 
    return c + 1;
}

void test_ft_strmapi() {
    char str[] = "hello";
    printf("Original string: %s\n", str);

    // Apply ft_strmapi and capture the result 
    char *modified_str = ft_strmapi(str, sample_function);

    //Print the modified string 
    if (modified_str) {
        printf("Modified string: %s\n", modified_str); // Should print "ifmmp"
        printf("Original string: %s\n", str);
        free(modified_str); // Don't forget to free the allocated memory
    } else {
        printf("Memory allocation failed\n");
    }
}

int main() {
    test_ft_strmapi(); // Run the test
    return 0;
}
*/
