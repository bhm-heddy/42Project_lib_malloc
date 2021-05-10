#include "malloc.h"


void	*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&give_cfg()->mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&give_cfg()->mutex);
	return (ptr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&give_cfg()->mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&give_cfg()->mutex);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&give_cfg()->mutex);
	ptr = ft_calloc(nmemb, size);
	pthread_mutex_unlock(&give_cfg()->mutex);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*ptr2;

	pthread_mutex_lock(&give_cfg()->mutex);
	ptr2 = ft_realloc(ptr, size);
	pthread_mutex_unlock(&give_cfg()->mutex);
	return (ptr2);
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&give_cfg()->mutex);
	ft_show_alloc_mem();
	pthread_mutex_unlock(&give_cfg()->mutex);
}
