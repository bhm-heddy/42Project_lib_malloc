#include "malloc.h"
#include "libft.h"

static t_block	*find_blk(t_cfg *cfg, t_block *blk_to_rlc)
{
	t_block	*blk;
	t_head	*head;
	t_block	*useless;

	head = find_head(cfg, blk_to_rlc);
	if (head)
		blk = find_chunk(head->begin, blk_to_rlc, &useless);
	else
		blk = find_chunk((t_block *)cfg->arraylist[LARGE_AREA],
				blk_to_rlc, &useless);
	if (!blk || blk->free)
	{
		print_invalid_pointer("realloc", (void *)blk_to_rlc + cfg->blk_size);
		return (NULL);
	}
	return (blk);
}

static void	*do_realloc(t_cfg *cfg, t_block *blk_to_rlc, void *ptr, size_t size)
{
	void	*realc;
	t_block	*new_blk;

	realc = ft_malloc(size);
	if (!realc)
		return (NULL);
	new_blk = realc - cfg->blk_size;
	if (new_blk->size > blk_to_rlc->size)
		ft_memcpy(realc, ptr, blk_to_rlc->size);
	else
		ft_memcpy(realc, ptr, new_blk->size);
	ft_free(ptr);
	return (realc);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_block	*blk_to_rlc;
	t_cfg	*cfg;

	cfg = give_cfg();
	if (cfg->debug_mode)
		debug_start_realloc(cfg, ptr, size);
	if (!size && ptr)
	{
		ft_free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_malloc(size));
	blk_to_rlc = find_blk(cfg, ptr - cfg->blk_size);
	if (!blk_to_rlc)
		abort();
	if (cfg->debug_mode)
		debug_end_realloc(cfg, blk_to_rlc->size);
	if (size <= blk_to_rlc->size)
		return (ptr);
	return (do_realloc(cfg, blk_to_rlc, ptr, size));
}
