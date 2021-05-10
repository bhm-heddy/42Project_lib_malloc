#include "malloc.h"
#include "libft.h"

uint8_t	print_invalid_pointer(char *ft, void *ptr)
{
	if (ptr)
	{
		ft_putstr_fd(ft, 2);
		ft_putstr_fd("(): error: address: [", 2);
		write_ptr_fd(2, ptr);
		ft_putstr_fd("] invalid pointer\n", 2);
	}
	return (F_ERROR | F_BADADD);
}

uint8_t	print_already_free(void *ptr)
{
	print_invalid_pointer("free", ptr);
	ft_putstr_fd("free(): error: double free detected\n", 2);
	return (F_ERROR | F_ISFREE);
}

uint8_t	print_munmap_error(void *ptr)
{
	ft_putstr_fd("free(): error: call munmap failled\n", 2);
	print_invalid_pointer("free", ptr);
	return (F_ERROR | F_MUNMAP);
}
