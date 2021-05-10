#include "malloc.h"
#include "libft.h"
#include <sys/mman.h>

void	insert_t_block(void *ptr, size_t size, void *next)
{
	t_block	new;

	new.size = size;
	new.next = next;
	new.free = FREE;
	ft_memcpy(ptr, &new, sizeof(t_block));
}

void	insert_t_head(void *ptr, void *begin, void *brk)
{
	t_head	new;

	new.nb = 0;
	new.begin = begin;
	new.brk = brk;
	new.next = NULL;
	ft_memcpy(ptr, &new, sizeof(t_head));
}

void	*call_mmap(int32_t size)
{
	void	*ptr;

	ptr = mmap(NULL, size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ptr == (void *)-1)
		return (NULL);
	return (ptr);
}

void	*init_mapped_region(size_t area, size_t user, size_t chunk)
{
	void	*ptr;
	void	*brk;
	void	*next;
	void	*first;

	ptr = call_mmap(area);
	if (!ptr)
		return (NULL);
	brk = ptr + area;
	first = ptr + chunk;
	insert_t_head(ptr, first, brk);
	while (first != brk)
	{
		next = first + chunk;
		insert_t_block(first, user, next);
		first = next;
	}
	((t_block *)(((void *)first) - chunk))->next = NULL;
	return (ptr);
}

void	*call_init_map(t_cfg *cfg, uint8_t area)
{
	void				*ret;

	if (area == TINY_AREA)
		ret = init_mapped_region(cfg->page_size << 3, cfg->tiny_size,
				cfg->tiny_size + cfg->blk_size);
	else
		ret = init_mapped_region(cfg->page_size << 5, cfg->small_size,
				cfg->small_size + cfg->blk_size);
	return (ret);
}
