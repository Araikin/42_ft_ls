/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 11:07:53 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/17 11:07:56 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*new_node(char *name, char *path)
{
	t_file	*new_node;
	char	*tmp;
	int		res;

	if (!(new_node = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (path)
	{
		tmp = (path[ft_strlen(path) - 1] == '/') ? ft_strjoin(path, name) :
			ft_strcjoin(path, '/', name);
		res = lstat(tmp, &new_node->info);
		free(tmp);
	}
	else
		res = lstat(name, &new_node->info);
	if (res == -1)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = ft_strdup(name);
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	set_dirinfo(unsigned int flags, t_file **file, char *arg)
{
	DIR			*dir;
	t_dirent	*dp;

	dir = opendir(arg);
	while ((dp = readdir(dir)))
		if (check_dir(flags, dp))
			*file = (flags & T_LOW) ? insert_time(*file, new_node(dp->d_name, arg)) :
				insert_ascii(*file, new_node(dp->d_name, arg));
	closedir(dir);
}

void	process_args(unsigned int flags, t_file *d, char *path, int n)
{
	t_file	*new;

	new = NULL;
	if (d != NULL)
	{
		process_args(flags, d->left, path, n + 1);
		n > 0 ? ft_printf("\n") : ft_printf("");
		ft_printf("%s:\n", d->name);
		set_dirinfo(flags, &new, d->name);
		print_ls(flags, new, NULL);
		process_args(flags, d->right, path, n + 1);
	}
}

t_file	*insert_time(t_file *root, t_file *new_node)
{
	if (root == NULL)
		return (new_node);	
	if (root->info.st_mtime < new_node->info.st_mtime)
		root->left = insert_time(root->left, new_node);
	else
		root->right = insert_time(root->right, new_node);
	return (root);	
}

t_file	*insert_ascii(t_file *root, t_file *new_node)
{
	if (root == NULL)
		return (new_node);
	if (ft_strcmp(root->name, new_node->name) > 0)
		root->left = insert_ascii(root->left, new_node);
	else
		root->right = insert_ascii(root->right, new_node);
	return (root);
}
