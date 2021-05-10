#include "libft.h"
#include "malloc.h"

void	*find_head(t_cfg *cfg, t_block *blk_to_free)
{
	t_head	*head;
	int		i;

	i = TINY_AREA;
	while (i < LARGE_AREA)
	{
		head = cfg->arraylist[i];
		while (head)
		{
			if ((uintptr_t)blk_to_free > (uintptr_t)head
				&& (uintptr_t)blk_to_free < (uintptr_t)head->brk)
				return (head);
			head = head->next;
		}
		i++;
	}
	return (NULL);
}

static uint8_t	ft_gearing(t_cfg *cfg, t_block *blk_to_free)
{
	t_head	*head;

	head = find_head(cfg, blk_to_free);
	if (head)
		return (free_prealoc(cfg, head, blk_to_free));
	return (free_large(cfg, blk_to_free));
}

void	ft_free(void *ptr)
{
	t_cfg	*cfg;
	t_block	*blk_to_free;

	if (!ptr)
		return ;
	cfg = give_cfg();
	if (cfg->debug_mode)
		debug_start_free(cfg, ptr);
	blk_to_free = ptr - cfg->blk_size;
	if (ft_gearing(cfg, blk_to_free) != SUCCESS)
		abort();
	if (cfg->debug_mode)
		debug_end_free(cfg);
	return ;
}
