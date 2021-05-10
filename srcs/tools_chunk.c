#include "malloc.h"
#include "libft.h"

void	*find_chunk(t_block *blk, t_block *blk_to_free, t_block **last)
{
	while (blk && blk != blk_to_free)
	{
		*last = blk;
		blk = blk->next;
	}
	return (blk);
}

void	*merge_chunk(t_block *first, t_block *nd, size_t tblock)
{
	first->next = nd->next;
	first->size += nd->size + tblock;
	ft_bzero(nd, tblock);
	return (first);
}

void	split_chunk(t_cfg *cfg, t_block *blk, size_t request)
{
	void	*new_head;
	size_t	new_size;

	new_head = (void *)blk + cfg->blk_size + request;
	new_size = blk->size - request - cfg->blk_size;
	insert_t_block(new_head, new_size, blk->next);
	blk->size = request;
	blk->next = new_head;
}

void	*add_chunk(t_cfg *cfg, t_head *head, t_block *blk, size_t request)
{
	size_t	min_size;

	if (request > cfg->tiny_size)
		min_size = cfg->tiny_size + request + cfg->blk_size;
	else
		min_size = 16 + request + cfg->blk_size;
	if (blk->size >= min_size)
		split_chunk(cfg, blk, request);
	blk->free = NOT_FREE;
	head->nb++;
	return (((void *)blk) + cfg->blk_size);
}

void	*find_friendly_chunk(t_cfg *cfg, t_head *head, size_t request)
{
	t_head		*last;
	t_block		*blk;

	while (head)
	{
		last = head;
		blk = head->begin;
		while (blk && (request > blk->size || !blk->free))
			blk = blk->next;
		if (blk)
			break ;
		head = head->next;
	}
	if (!blk)
	{
		if (request <= cfg->tiny_size)
			last->next = call_init_map(cfg, TINY_AREA);
		else
			last->next = call_init_map(cfg, SMALL_AREA);
		head = last->next;
		blk = head->begin;
	}
	return (add_chunk(cfg, head, blk, request));
}
