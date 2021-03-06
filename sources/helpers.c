/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:06:11 by asultanb          #+#    #+#             */
/*   Updated: 2020/02/07 13:18:40 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		is_dir(char *arg)
{
	t_stat	checkdir;

	if (lstat(arg, &checkdir) == -1)
		return (0);
	if (!(S_ISDIR(checkdir.st_mode)))
		return (0);
	return (1);
}

int		is_file(char *arg)
{
	t_stat	checkfile;

	if (lstat(arg, &checkfile) == -1)
		return (-1);
	if (!(S_ISDIR(checkfile.st_mode)))
		return (1);
	return (0);
}

int		check_dir(uint16_t opt, t_dirent *dp)
{
	if (opt & A_UPP && !(opt & A_LOW) && !(opt & F_LOW))
	{
		if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
			return (0);
		return (1);
	}
	else if (!(opt & A_LOW) && !(opt & F_LOW))
	{
		if (dp->d_name[0] == '.')
			return (0);
		return (1);
	}
	return (1);
}

void	destroy_file(t_file *file)
{
	if (file != NULL)
	{
		destroy_file(file->left);
		destroy_file(file->right);
		free(file->name);
		free(file->path);
		free(file);
	}
}

void	ls_output(int mode, char *arg)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = NULL;
	k = 0;
	if (mode == 1)
	{
		ft_printf("ls: illegal option -- %c\n", arg[0]);
		ft_printf("usage: ./ft_ls [-1AFGRSafglrt] [file ...]\n");
		exit(EXIT_FAILURE);
	}
	else if (mode == 2)
		ft_printf("ls: %s: No such file or directory\n", arg);
	else if (mode == 3)
	{
		i = -1;
		while (arg[++i])
			if (arg[i] == '/')
				k = i + 1;
		tmp = k > 0 ? ft_strdup(&arg[k]) : ft_strdup(arg);
		ft_printf("ls: %s: Permission denied\n", tmp);
		free(tmp);
	}
}
