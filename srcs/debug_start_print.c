#include "libft.h"
#include "malloc.h"

void	debug_start_malloc(t_cfg *cfg, size_t size)
{
	ft_putstr_fd("\n#########################################"
"############################\n", cfg->debug_fd);
	ft_putstr_fd(">>>>>>----- [[[ CALL MALLOC ]]] -> size = [", cfg->debug_fd);
	ft_putnbr_fd(size, cfg->debug_fd);
	ft_putstr_fd("] -----<<<<<<\n", cfg->debug_fd);
}

void	debug_start_free(t_cfg *cfg, void *ptr)
{
	ft_putstr_fd("\n#########################################"
"############################\n", cfg->debug_fd);
	ft_putstr_fd(">>>>>>----- [[[ CALL FREE ]]] -> ptr = [", cfg->debug_fd);
	write_ptr_fd(cfg->debug_fd, ptr);
	ft_putstr_fd("] -----<<<<<<\n", cfg->debug_fd);
}

void	debug_start_realloc(t_cfg *cfg, void *ptr, size_t size)
{
	ft_putstr_fd("\n#########################################"
"############################\n", cfg->debug_fd);
	ft_putstr_fd(">>>>>>----- [[[ CALL REALLOC ]]]\n -> requested size = [",
		cfg->debug_fd);
	ft_putnbr_fd(size, cfg->debug_fd);
	ft_putstr_fd("]  ptr = [", cfg->debug_fd);
	write_ptr_fd(cfg->debug_fd, ptr);
	ft_putstr_fd("] -----<<<<<<\n", cfg->debug_fd);
}
