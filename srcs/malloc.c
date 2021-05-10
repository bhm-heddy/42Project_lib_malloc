#include "libft.h"
#include "malloc.h"

static void	*create_large_area(size_t blk, size_t request)
{
	void		*new;

	new = call_mmap(request);
	if (!new)
		return (NULL);
	insert_t_block(new, request - blk, 0);
	return (new);
}

static void	*add_large(t_cfg *cfg, size_t request)
{
	void	*new;

	request = align_largepage(cfg, request);
	new = create_large_area(cfg->blk_size, request);
	if (!new)
		return (NULL);
	((t_block *)new)->free = NOT_FREE;
	lstpushfront_blk((t_block **)(&cfg->arraylist[LARGE_AREA]), new);
	if (cfg->debug_mode)
		debug_end_malloc(cfg, new + cfg->blk_size, ((t_block *)new)->size);
	return (new + cfg->blk_size);
}

static void	*find_area(t_cfg *cfg, size_t request)
{
	if (request <= cfg->tiny_size)
	{
		if (!(cfg->arraylist[TINY_AREA]))
			cfg->arraylist[TINY_AREA] = call_init_map(cfg, TINY_AREA);
		return (cfg->arraylist[TINY_AREA]);
	}
	else
	{
		if (!(cfg->arraylist[SMALL_AREA]))
			cfg->arraylist[SMALL_AREA] = call_init_map(cfg, SMALL_AREA);
		return (cfg->arraylist[SMALL_AREA]);
	}
}

void	*ft_malloc(size_t size)
{
	t_head	*head;
	t_cfg	*cfg;
	void	*add_user;

	if (size == 0)
		return (0);
	cfg = give_cfg();
	if (cfg->debug_mode)
		debug_start_malloc(cfg, size);
	size = align16(size);
	if (size > cfg->small_size)
		return (add_large(cfg, size));
	head = find_area(cfg, size);
	if (!head)
		return (NULL);
	add_user = find_friendly_chunk(cfg, head, size);
	if (cfg->debug_mode)
		debug_end_malloc(cfg, add_user, size);
	return (add_user);
}
