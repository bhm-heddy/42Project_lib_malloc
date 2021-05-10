#include "malloc.h"
#include "libft.h"

static	void	print_overflow(void)
{
	ft_putstr_fd("calloc(): error: Overflow detected\n", 2);
}

static size_t	check_isoverflow(size_t a, size_t b)
{
	size_t	ret;

	b = align16(b);
	ret = a * b;
	if (a == ret / b)
		return (ret);
	print_overflow();
	abort();
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	request;
	void	*p;

	if (!nmemb || !size)
		return (NULL);
	request = check_isoverflow(nmemb, size);
	p = ft_malloc(request);
	if (!p)
		return (NULL);
	ft_bzero(p, request);
	return (p);
}
