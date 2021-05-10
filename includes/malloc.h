#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdint.h>
# include <pthread.h>

# define TINY_AREA	0
# define SMALL_AREA	1
# define LARGE_AREA	2
# define NOT_FOUND	3

# define FREE 		1
# define NOT_FREE	0

# define SUCCESS	0
# define FAILURE	1

# define F_ERROR	0x10
# define F_BADADD	0x11
# define F_ISFREE	0x12
# define F_MUNMAP	0x14

typedef struct	s_block
{
	size_t			size;
	struct s_block	*next;
	uint8_t			free;
}				t_block;

typedef struct	s_head
{
	uint16_t		nb;
	struct s_head	*next;
	struct s_block	*begin;
	void			*brk;
}				t_head;

typedef struct	s_cfg
{
	t_head			*arraylist[3];
	uint16_t		tiny_size;
	uint16_t		small_size;
	int32_t			page_size;
	size_t			blk_size;
	pthread_mutex_t	mutex;
	uint8_t			debug_mode;
	int32_t			debug_fd;
}				t_cfg;



void			*malloc(size_t size);
void			*ft_malloc(size_t size);

void			free(void *ptr);
void			ft_free(void *ptr);

void			*calloc(size_t nmemb, size_t size);
void			*ft_calloc(size_t nmemb, size_t size);

void			*realloc(void *ptr, size_t size);
void			*ft_realloc(void *ptr, size_t size);

void			show_alloc_mem(void);
void			ft_show_alloc_mem(void);

t_cfg			*give_cfg(void);

void			*call_mmap(int32_t size);
void			insert_t_block(void	*ptr, size_t size, void *next);
size_t			align16(size_t size);
uint32_t		align_largepage(t_cfg *cfg, size_t request);
void			lstpushfront_blk(t_block **begin, t_block *new);
uint8_t			free_large(t_cfg *cfg, t_block *blk_to_free);
uint8_t			free_prealoc(t_cfg *cfg, t_head *head, t_block *blk_to_free);
uint16_t		because_norme(t_cfg *cfg, t_block *blk, uint8_t *area);
void			split_chunk(t_cfg *cfg, t_block *blk, size_t request);
void			*add_chunk(t_cfg *cfg, t_head *head, t_block *blk,
							size_t request);
void			*find_friendly_chunk(t_cfg *cfg, t_head *head, size_t request);
void			*find_chunk(t_block *blk, t_block *blk_to_free, t_block **last);
void			*find_head(t_cfg *cfg, t_block *blk_to_free);
void			*merge_chunk(t_block *first, t_block *nd, size_t tblock);
uint8_t			print_invalid_pointer(char *ft, void *ptr);
uint8_t			print_already_free(void *ptr);
uint8_t			print_munmap_error(void *ptr);
void			*init_mapped_region(size_t size_area, size_t user_size,
					size_t chunk_size);
void			*call_init_map(t_cfg *cfg, uint8_t area);
void			init_cfg(t_cfg *cfg);
void			print_info_sys(int32_t fd);
void			print_info_block(t_block *blk, int32_t fd, uint32_t nb);
void			print_all_info(t_head *head, uint8_t full, int32_t fd);
void			print_all_large(t_block *blk, uint8_t full, int32_t fd);
void			print_all_head(t_head *head, int32_t fd);
void			print_header(t_head *head, int32_t fd);
void			debug_print_cfg(t_cfg *cfg, int32_t fd);
void			debug_end_malloc(t_cfg *cfg, void *add_user, size_t size);
void			debug_start_malloc(t_cfg *cfg, size_t size);
void			debug_start_free(t_cfg *cfg, void *ptr);
void			debug_end_free(t_cfg *cfg);
void			debug_start_realloc(t_cfg *cfg, void *ptr, size_t size);
void			debug_end_realloc(t_cfg *cfg, size_t size);
void			write_ptr_fd(int fd, void *p);

#endif
