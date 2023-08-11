/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdjebal <akdjebal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:00:35 by akdjebal          #+#    #+#             */
/*   Updated: 2023/08/11 14:00:57 by akdjebal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (perror(""), 0);
	printf("%s\n", cwd);
	return (1);
}
