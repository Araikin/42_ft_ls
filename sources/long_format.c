/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:45:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/02/07 12:27:35 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	long_format(uint16_t opt, t_file *file, t_wid *wid)
{
	print_st_mode(file, file->info.st_mode);
	ft_printf("%*d ", wid->links, file->info.st_nlink);
	if (!(opt & G_LOW))
		ft_printf("%-*s  ", wid->uid, (getpwuid(file->info.st_uid))->pw_name);
	ft_printf("%-*s  ", wid->gid, (getgrgid(file->info.st_gid))->gr_name);
	if (wid->chr_blk > 0)
	{
		if (S_ISCHR(file->info.st_mode) || S_ISBLK(file->info.st_mode))
			ft_printf("%*d, %*d ", wid->major, major(file->info.st_rdev),
					wid->minor, minor(file->info.st_rdev));
		else
			ft_printf("%*d ", wid->major + wid->minor + 2,
					file->info.st_size);
	}
	else
		ft_printf("%*d ", wid->size, file->info.st_size);
	print_time(file->info.st_mtime);
	print_name(opt, file);
}

void	print_st_mode(t_file *file, mode_t st_mode)
{
	char	c;
	char	s_uid;
	char	s_gid;
	char	st_bit;

	st_bit = st_mode & S_ISVTX ? 't' : 'x';
	s_uid = st_mode & S_ISUID ? 's' : 'x';
	s_gid = st_mode & S_ISGID ? 's' : 'x';
	c = S_ISDIR(st_mode) ? 'd' : '-';
	c = S_ISLNK(st_mode) ? 'l' : c;
	c = S_ISBLK(st_mode) ? 'b' : c;
	c = S_ISCHR(st_mode) ? 'c' : c;
	c = S_ISSOCK(st_mode) ? 's' : c;
	c = S_ISFIFO(st_mode) ? 'p' : c;
	ft_printf("%c%c%c%c%c%c%c%c%c%c", c, st_mode & S_IRUSR ? 'r' : '-',
		st_mode & S_IWUSR ? 'w' : '-', st_mode & S_IXUSR ? s_uid : '-',
		st_mode & S_IRGRP ? 'r' : '-', st_mode & S_IWGRP ? 'w' : '-',
		st_mode & S_IXGRP ? s_gid : '-', st_mode & S_IROTH ? 'r' : '-',
		st_mode & S_IWOTH ? 'w' : '-', st_mode & S_IXOTH ? st_bit : '-');
	print_acl_extattr(file);
}

void	print_time(time_t mod_time)
{
	int		flag;
	int		i;
	char	*mtime;

	flag = (time(NULL) - mod_time > 15552000) ? 1 : 0;
	mtime = ctime(&mod_time);
	i = 3;
	while (++i < 11)
		write(1, &mtime[i], 1);
	if (flag)
	{
		i += 8;
		write(1, " ", 1);
		while (++i < 24)
			write(1, &mtime[i], 1);
	}
	else
		while (i < 16)
			write(1, &mtime[i++], 1);
	write(1, " ", 1);
}

void	print_link(uint16_t opt, t_file *file)
{
	char	link[255];

	link[readlink(file->path, link, 254)] = '\0';
	if (opt & G_UPP)
		write(1, "\x1b[35m", 5);
	ft_printf("%s", file->name);
	write(1, "\x1b[0m", 5);
	if ((opt & F_UPP) && (opt & L_LOW))
		print_type(file->info);
	ft_printf(" -> %s\n", link);
}
