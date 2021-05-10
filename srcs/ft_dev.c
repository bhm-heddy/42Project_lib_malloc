#include "malloc.h"
#include "libft.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

void	print_header(t_head *head, int32_t fd)
{
	ft_putstr_fd("\t---------> HEADER <----------\n", fd);
	ft_putstr_fd("\thead     = [", fd);
	write_ptr_fd(fd, head);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\tblk used = [", fd);
	ft_putnbr_fd(head->nb, fd);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\tbegin    = [", fd);
	write_ptr_fd(fd, head->begin);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\tnext     = [", fd);
	write_ptr_fd(fd, head->next);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\tbrk      = [", fd);
	write_ptr_fd(fd, head->brk);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\t------------><----------------\n", fd);
}

void	print_info_block(t_block *blk, int32_t fd, uint32_t nb)
{
	ft_putstr_fd("\t\t--------- BLOCK [", fd);
	ft_putnbr_fd(nb, fd);
	ft_putstr_fd("] ---------\n", fd);
	ft_putstr_fd("\t\tblk address         = [", fd);
	write_ptr_fd(fd, blk);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\t\tuser address = [", fd);
	write_ptr_fd(fd, ((void *)blk) + align16(sizeof(t_block)));
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\t\tsize                = [", fd);
	ft_putnbr_fd(blk->size, fd);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\t\tnext                = [", fd);
	write_ptr_fd(fd, blk->next);
	ft_putstr_fd("]\n", fd);
	ft_putstr_fd("\t\tfree                = [", fd);
	ft_putnbr_fd(blk->free, fd);
	ft_putstr_fd("]\n", fd);
}

void	print_all_large(t_block *blk, uint8_t full, int32_t fd)
{
	int	i;

	i = 1;
	ft_putstr_fd("\n--->>>>>----- [LARGE AREA] -----<<<<<---\n", fd);
	if (!blk)
		ft_putstr_fd("\t<<<<< [EMPTY]\n", fd);
	while (blk)
	{
		ft_putstr_fd("\t-> CHUNK LARGE = [", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("]\n", fd);
		if (full == 3)
			print_info_block(blk, fd, i);
		else
		{
			ft_putstr_fd("\tuser address = [", fd);
			write_ptr_fd(fd, ((void *)blk) + align16(sizeof(t_block)));
			ft_putstr_fd("]", fd);
			ft_putstr_fd("  size = [", fd);
			ft_putnbr_fd(blk->size, fd);
			ft_putstr_fd("]\n", fd);
		}
		blk = blk->next;
		i++;
	}
}

void	print_all_head(t_head *head, int32_t fd)
{
	while (head)
	{
		print_header(head, fd);
		head = head->next;
	}
}

void	print_all_info(t_head *head, uint8_t full, int32_t fd)
{
	t_block		*blk;
	uint32_t	nb;

	if (!head)
		ft_putstr_fd("\t<<<<< [EMPTY]\n", fd);
	while (head)
	{
		nb = 1;
		print_header(head, fd);
		blk = head->begin;
		while (blk)
		{
			if (full > 2)
			{
				if (!blk->free || full == 4)
					print_info_block(blk, fd, nb);
			}
			nb++;
			blk = blk->next;
		}
		ft_putstr_fd("\t -> number of blocks = [", fd);
		ft_putnbr_fd(nb - 1, fd);
		ft_putstr_fd("]\n", fd);
		head = head->next;
	}
}
