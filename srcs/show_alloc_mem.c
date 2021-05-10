#include "malloc.h"
#include "libft.h"

static int32_t	print(t_block *blk, size_t block)
{
	int32_t		total;

	total = 0;
	while (blk)
	{
		if (!blk->free)
		{
			write_ptr_fd(1, (void *)blk + block);
			ft_putstr(" ~ ");
			write_ptr_fd(1, (void *)blk + blk->size + block);
			ft_putstr(" : ");
			ft_putnbr(blk->size);
			ft_putstr(" octets\n");
			total += blk->size;
		}
		blk = blk->next;
	}
	return (total);
}

static uint32_t	loop_print(t_cfg *cfg, t_head *head, char *area)
{
	uint32_t	total;

	total = 0;
	ft_putstr(area);
	if (!head)
	{
		ft_putstr("Empty\n");
		return (total);
	}
	write_ptr_fd(1, head);
	ft_putstr("\n");
	while (head)
	{
		total += print(head->begin, cfg->blk_size);
		head = head->next;
	}
	return (total);
}

static uint32_t	especial_large(t_cfg *cfg, t_block *blk)
{
	uint32_t	total;

	total = 0;
	ft_putstr("LARGE : ");
	if (!blk)
	{
		ft_putstr("Empty\n");
		return (total);
	}
	write_ptr_fd(1, blk);
	ft_putstr("\n");
	total = print(blk, cfg->blk_size);
	return (total);
}

void			ft_show_alloc_mem(void)
{
	t_head	*head;
	t_cfg	*cfg;
	int32_t	total;

	cfg = give_cfg();
	total = 0;
	head = cfg->arraylist[TINY_AREA];
	total += loop_print(cfg, head, "TINY : ");
	head = cfg->arraylist[SMALL_AREA];
	total += loop_print(cfg, head, "SMALL : ");
	head = cfg->arraylist[LARGE_AREA];
	total += especial_large(cfg, (t_block *)head);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
}
