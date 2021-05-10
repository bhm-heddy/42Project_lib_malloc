#include "malloc.h"
#include "libft.h"
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void	print_info_sys(int32_t fd)
{
	struct utsname	buf1;

	if (uname(&buf1) != 0)
	{
		ft_putstr_fd("uname doesn't return 0, so there is an error", 2);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("**************[ SYS ]**************\n", fd);
	ft_putstr_fd("* System Name = [", fd);
	ft_putstr_fd(buf1.sysname, fd);
	ft_putstr_fd("]            *\n", fd);
	ft_putstr_fd("* Node Name   = [", fd);
	ft_putstr_fd(buf1.nodename, fd);
	ft_putstr_fd("]             *\n", fd);
	ft_putstr_fd("* Version     = [", fd);
	ft_putstr_fd(buf1.version, fd);
	ft_putstr_fd("]   *\n", fd);
	ft_putstr_fd("* Release     = [", fd);
	ft_putstr_fd(buf1.release, fd);
	ft_putstr_fd("] *\n", fd);
	ft_putstr_fd("* Machine     = [", fd);
	ft_putstr_fd(buf1.machine, fd);
	ft_putstr_fd("]           *\n", fd);
	ft_putstr_fd("***********************************\n", fd);
}

void	debug_print_cfg(t_cfg *cfg, int32_t fd)
{
	ft_putstr_fd("********[ CFG ]*********\n", fd);
	ft_putstr_fd("* PAGE SIZE  = [", fd);
	ft_putnbr_fd(cfg->page_size, fd);
	ft_putstr_fd("]  *\n", fd);
	ft_putstr_fd("* TINY SIZE  = [", fd);
	ft_putnbr_fd(cfg->tiny_size, fd);
	ft_putstr_fd("]   *\n", fd);
	ft_putstr_fd("* SMALL SIZE = [", fd);
	ft_putnbr_fd(cfg->small_size, fd);
	ft_putstr_fd("]  *\n", fd);
	ft_putstr_fd("* BLK SIZE   = [", fd);
	ft_putnbr_fd(cfg->blk_size, fd);
	ft_putstr_fd("]    *\n", fd);
	ft_putstr_fd("* DEBUG LVL  = [", fd);
	ft_putnbr_fd(cfg->debug_mode, fd);
	ft_putstr_fd("]     *\n", fd);
	ft_putstr_fd("************************\n", fd);
}

static int32_t	create_debug_file(char *env)
{
	int32_t	fd;

	fd = open(env, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("DEBUG MODE can't open file :  ", 2);
		ft_putstr_fd(env, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	init_cfg(t_cfg *cfg)
{
	char	*debug_path;

	ft_bzero(cfg, sizeof(t_cfg));
	pthread_mutex_init(&cfg->mutex, 0);
	cfg->page_size = getpagesize();
	if (sizeof(t_block) % 16)
		cfg->blk_size = (((sizeof(t_block) >> 4) + 1) << 4);
	else
		cfg->blk_size = sizeof(t_block);
	cfg->tiny_size = ((cfg->page_size << 3) >> 7) - cfg->blk_size;
	cfg->small_size = ((cfg->page_size << 6) >> 7) - cfg->blk_size;
	cfg->debug_mode = ft_atoi(getenv("M_DEBUG"));
	debug_path = getenv("M_PATH");
	if (debug_path)
		cfg->debug_fd = create_debug_file(debug_path);
	else
		cfg->debug_fd = 2;
	if (cfg->debug_mode)
	{
		print_info_sys(cfg->debug_fd);
		debug_print_cfg(cfg, cfg->debug_fd);
	}
}

t_cfg	*give_cfg(void)
{
	static t_cfg	cfg;

	if (!(cfg.page_size))
		init_cfg(&cfg);
	return (&cfg);
}
