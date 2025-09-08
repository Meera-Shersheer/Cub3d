/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:37:00 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:37:01 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	while (i < count * size)
		tmp[i++] = 0;
	return (tmp);
}
/*
void test_ft_calloc(size_t count, size_t size)
{
    unsigned char *ft_mem;
    unsigned char *std_mem;

    // Allocate memory using ft_calloc and calloc
    ft_mem = (unsigned char *)ft_calloc(count, size);
    std_mem = (unsigned char *)calloc(count, size);

    printf("Testing ft_calloc with count = %zu, size = %zu:\n", count, size);

    // Check if both returned NULL in case of allocation failure
    if (!ft_mem || !std_mem)
    {
        if (!ft_mem && !std_mem)
            printf("Both ft_calloc and calloc failed as expected.\n\n");
        else
            printf("Mismatch: One succeeded while the other failed.\n\n");
        return;
    }

    // Compare the memory blocks to see if they're both zero-initialized
    if (memcmp(ft_mem, std_mem, count * size) == 0)
        printf("Test passed! Both memory blocks are zero-initialized.\n\n");
    else
        printf("Test failed! Memory blocks are different.\n\n");

    // Free allocated memory
    free(ft_mem);
    free(std_mem);
}

int main(void)
{
    // Test cases for different sizes and counts
    test_ft_calloc(5, sizeof(int));   // Normal test: 5 integers
    test_ft_calloc(10, sizeof(char)); // Test for chars
    test_ft_calloc(0, 10);            // Edge case: count = 0
    test_ft_calloc(10, 0);            // Edge case: size = 0
    test_ft_calloc(100, sizeof(float)); // Larger allocation test
    
    return 0;
}
*/
