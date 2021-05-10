#include "libft.h"
#include "malloc.h"

void	debug_print_more(t_cfg *cfg)
{
	ft_putstr_fd("\n--->>>>>----- [TINY AREA] -----<<<<<---\n", cfg->debug_fd);
	print_all_info(cfg->arraylist[TINY_AREA], cfg->debug_mode, cfg->debug_fd);
	ft_putstr_fd("\n--->>>>>----- [SMALL AREA] -----<<<<<---\n", cfg->debug_fd);
	print_all_info(cfg->arraylist[SMALL_AREA], cfg->debug_mode, cfg->debug_fd);
	print_all_large((t_block *)cfg->arraylist[LARGE_AREA],
		cfg->debug_mode, cfg->debug_fd);
}

void	debug_end_realloc(t_cfg *cfg, size_t size)
{
	ft_putstr_fd(" -> current size = [", cfg->debug_fd);
	ft_putnbr_fd(size, cfg->debug_fd);
	ft_putstr_fd("]\n", cfg->debug_fd);
}

void	debug_end_free(t_cfg *cfg)
{
	if (cfg->debug_mode > 1)
		debug_print_more(cfg);
	ft_putstr_fd("\n###############################"
				"######################################\n", cfg->debug_fd);
}

void	debug_end_malloc(t_cfg *cfg, void *add_user, size_t size)
{
	ft_putstr_fd("return = [", cfg->debug_fd);
	write_ptr_fd(cfg->debug_fd, add_user);
	ft_putstr_fd("]   -> size = [", cfg->debug_fd);
	ft_putnbr_fd(size, cfg->debug_fd);
	ft_putstr_fd("]\n", cfg->debug_fd);
	if (cfg->debug_mode > 1)
		debug_print_more(cfg);
	ft_putstr_fd("\n###############################"
				"######################################\n", cfg->debug_fd);
}
