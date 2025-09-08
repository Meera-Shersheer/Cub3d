/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:31:21 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:31:24 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
/*
void test_ft_atoi(const char *str)
{
    int result_ft_atoi = ft_atoi(str);
    int result_std_atoi = atoi(str);  // Using standard atoi for comparison

    printf("Input: \"%s\"\n", str);
    printf("ft_atoi: %d\n", result_ft_atoi);
    printf("std_atoi: %d\n", result_std_atoi);

    if (result_ft_atoi == result_std_atoi)
        printf("Test passed!\n\n");
    else
        printf("Test failed!\n\n");
}

int main(void)
{
    // Test cases
    test_ft_atoi("123456");          // Regular positive number
    test_ft_atoi("    789");         // Number with leading spaces
    test_ft_atoi("-42");             // Negative number
    test_ft_atoi("  +54");           // Positive number with '+' sign
    test_ft_atoi("   -999");         // Negative number with leading spaces
    test_ft_atoi("0");               // Zero
    test_ft_atoi("+-123");           // Invalid number
    test_ft_atoi("42abc");           // Number followed by characters
    test_ft_atoi("    -2147483648"); // Edge case: INT_MIN
    test_ft_atoi("2147483647");      // Edge case: INT_MAX
    test_ft_atoi("     ");           // Input with only spaces
    test_ft_atoi("abc123");          // Non-numeric characters

    return 0;
}
*/
