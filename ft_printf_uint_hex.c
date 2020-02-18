/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:14:45 by jabenjam          #+#    #+#             */
/*   Updated: 2020/02/18 15:02:42 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    ft_padding_uint(char *buffer, s_struct *f)
{
	if (f->precision >= 0)
	{
        f->zero = 1;
        f->width = f->precision - 1;
		ft_width(f, 0);
	}
    ft_putstr_mod(buffer, f->len);
}

void    ft_uint_next(char *buffer, s_struct *f)
{
	if (f->left)
		ft_padding_uint(buffer, f);
	if (f->precision >= 0 && f->precision < f->len) // si ça ne marche pas changer f->precision en size_t
		f->precision = f->len;
	if (f->precision >= 0)
	{
		f->width -= f->precision;
		ft_width(f, 1);
	}
	else
		ft_width(f, 0);
	if (!f->left)
		ft_padding_int(buffer, f);
}

void    ft_uint_hex(unsigned int nb, s_struct *f)
{
	char    *buffer;

    nb = (unsigned int)(nb + 429496725 + 1); // tester sans addition
	if (!f->precision && !nb) // si nb = 0 et aucune precision on print la largeur
		return (ft_width(f, 0));
	buffer = (f->specifier == 'u' ? ft_uitoa(nb) : ft_ulltoa_base((unsigned long long)nb));
	buffer = (f->specifier == 'X' ? ft_toupper(buffer): buffer);
	f->len = ft_strlen(buffer);
	ft_uint_next(buffer, f);
	free(buffer);
}

void    ft_hex(unsigned int nb, s_struct *f)
{
	char    *buffer;

    nb = (unsigned int)(nb + 429496725 + 1); // tester sans addition
	if (!f->precision && !nb) // si nb = 0 et aucune precision on print la largeur
		return (ft_width(f, 0));
	buffer = ft_ulltoa_base(nb);
    buffer = (f->specifier == 'X' ? ft_toupper(buffer) : buffer);
	f->len = ft_strlen(buffer);
	ft_uint_next(buffer, f);
	free(buffer);
}