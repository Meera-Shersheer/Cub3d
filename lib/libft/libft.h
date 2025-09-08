/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 07:34:40 by aalmahas          #+#    #+#             */
/*   Updated: 2024/09/22 07:34:44 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//# include <stdio.h>
# include <stdlib.h> 
# include <unistd.h>
//# include <string.h>
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
int			ft_isspace(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		*ft_calloc(size_t count, size_t size);
void		test_ft_strjoin(const char *s1, const char *s2);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif
