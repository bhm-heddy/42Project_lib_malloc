#include "malloc.h"

void		lstpushfront_blk(t_block **begin, t_block *new)
{
	if (*begin)
		new->next = *begin;
	*begin = new;
}

void		write_ptr_fd(int fd, void *p)
{
	uintptr_t	x;
	char		buf[2 + sizeof(x) + sizeof(x)];
	size_t		i;
	size_t		ptr_size;

	i = 0;
	x = (uintptr_t)p;
	ptr_size = sizeof(x) * 2;
	buf[0] = '0';
	buf[1] = 'x';
	while (i < ptr_size)
	{
		buf[i + 2] = "0123456789abcdef"[(x >> ((ptr_size - 1 - i) * 4)) & 0xf];
		i++;
	}
	write(fd, buf, sizeof(buf));
	return ;
}

size_t		align16(size_t size)
{
	if (size % 16)
		size = (((size >> 4) + 1) << 4);
	return (size);
}

uint32_t	align_largepage(t_cfg *cfg, size_t request)
{
	uint32_t	page;
	uint32_t	chunk;

	chunk = request + cfg->blk_size;
	page = cfg->page_size;
	while (chunk > page)
		page += cfg->page_size;
	return (page);
}

uint16_t	because_norme(t_cfg *cfg, t_block *blk, uint8_t *area)
{
	if (blk->size > cfg->tiny_size)
	{
		*area = SMALL_AREA;
		return (cfg->small_size);
	}
	else
	{
		*area = TINY_AREA;
		return (cfg->tiny_size);
	}
}
