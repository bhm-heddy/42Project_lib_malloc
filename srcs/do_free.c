#include "malloc.h"
#include <sys/mman.h>

static uint8_t	call_munmap(t_block *blk, size_t blk_size)
{
	if (munmap(blk, blk->size + blk_size))
		return (print_munmap_error((void *)blk + sizeof(t_block)));
	return (SUCCESS);
}

static void	free_chunk(t_head *head, t_block *blk)
{
	blk->free = FREE;
	head->nb--;
}

static uint8_t	free_area(t_head *head)
{
	t_head	*next;
	uint8_t	head_empty;

	next = NULL;
	head_empty = 0;
	while (head->next)
	{
		next = head->next;
		if (head->nb < 32)
			head_empty = 1;
		if (next->nb == 0 && head_empty)
		{
			head->next = next->next;
			if (munmap(next, (uintptr_t)next->brk - (uintptr_t)next))
				return (print_munmap_error(NULL));
		}
		else
			head = head->next;
	}
	return (SUCCESS);
}

uint8_t	free_prealoc(t_cfg *cfg, t_head *head, t_block *blk_to_free)
{
	t_block	*last;
	t_block	*next;
	t_block	*blk;
	size_t	user_size;
	uint8_t	area;

	last = NULL;
	blk = find_chunk(head->begin, blk_to_free, &last);
	if (!blk)
	{
		return (print_invalid_pointer(
		"free", ((void *)blk_to_free) + cfg->blk_size));
	}
	if (blk->free == FREE)
		return (print_already_free(blk + cfg->blk_size));
	free_chunk(head, blk);
	user_size = because_norme(cfg, blk, &area);
	next = blk->next;
	if (last && last->free
		&& last->size + blk->size + cfg->blk_size <= user_size)
		blk = merge_chunk(last, blk, cfg->blk_size);
	if (next && next->free
		&& next->size + blk->size + cfg->blk_size <= user_size)
		merge_chunk(blk, next, cfg->blk_size);
	return (free_area(cfg->arraylist[area]));
}

uint8_t	free_large(t_cfg *cfg, t_block *blk_to_free)
{
	t_block	*last;
	t_block	*blk;

	last = NULL;
	blk = find_chunk((t_block *)cfg->arraylist[LARGE_AREA], blk_to_free, &last);
	if (!blk)
	{
		return (print_invalid_pointer("free",
				(void *)blk_to_free + cfg->blk_size));
	}
	if (last)
		last->next = blk->next;
	else
		cfg->arraylist[LARGE_AREA] = (t_head *)blk->next;
	return (call_munmap(blk, cfg->blk_size));
}
