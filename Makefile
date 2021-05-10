ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME            = libft_malloc_$(HOSTTYPE).so
LIBNAME         = libft_malloc.so

NAME_DB         = libft_malloc_$(HOSTTYPE)_db.so
LIBNAME_DB      = libft_malloc_db.so

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m



#--------------------------Dev/Debug----------------------------#
SRC_FILE += ft_dev.c
SRC_FILE += debug_start_print.c
SRC_FILE += debug_end_print.c

#--------------------------SRCS----------------------------#

SRC_FILE += pthread_caller.c
SRC_FILE += malloc.c
SRC_FILE += init.c
SRC_FILE += free.c
SRC_FILE += do_free.c
SRC_FILE += realloc.c
SRC_FILE += calloc.c
SRC_FILE += tools.c
SRC_FILE += tools_chunk.c
SRC_FILE += handle_errors.c
SRC_FILE += show_alloc_mem.c
SRC_FILE += cfg.c

#--------------------------INCLUDES----------------------------#
INCLUDES += malloc.h


MKDIR		= mkdir -p
CLEANUP 	= rm -rf


OPATH		= objs/
OPATH_DB	= objs_db/
SPATH		= srcs/
IPATH		= includes/

LPATH 		= libft/
LIPATH		= libft/includes/
LIBFT		= $(LPATH)libft.a
CLIBFT		= -Llibft/ -lft

WFLAGS		= -Wall -Werror -Wextra
DYNFLAGS	= -shared -Wl,-soname,$(NAME)
IFLAGS		= -I $(IPATH) -I $(LIPATH)
CFLAGS		= $(WFLAGS) $(IFLAGS)

CC			= clang
COMPILE		= $(CC) $(CFLAGS) -fPIC -c


COMPILE_DB	= $(COMPILE) -g3
LIBFT_DB 	= $(LPATH)libft_db.a
CLIBFT_DB	= -Llibft/ -lft_db
DYNFLAGS_DB	= -shared -Wl,-soname,$(NAME_DB)
#DBFLAGS = -fsanitize=address


SRCS		= $(addprefix $(SPATH), $(SRC_FILE))
OBJS		= $(addprefix $(OPATH), $(SRC_FILE:.c=.o))
OBJS_DB	 	= $(addprefix $(OPATH_DB), $(SRC_FILE:.c=.o))
INCS 		= $(addprefix $(IPATH), $(INCLUDES))



all : $(NAME)

$(NAME) : $(LIBFT) $(OPATH) $(OBJS) Makefile
	$(CC) $(DYNFLAGS) -o $(NAME) $(OBJS) $(CLIBFT)
	ln -s --force $@ $(LIBNAME)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(OPATH)%.o : $(SPATH)%.c $(INCS)
	$(COMPILE) $< -o $@
	printf "$(BLUE)  Compiling $<\n $(NC)"

$(OPATH) :
	$(MKDIR) $@

$(LIBFT) : FORCE
	make -C $(LPATH)


debug: $(LIBFT_DB) $(OPATH_DB) $(OBJS_DB) Makefile
	$(CC) $(DYNFLAGS_DB) -o $(NAME_DB) $(OBJS_DB) $(CLIBFT_DB)
	ln -s --force $(NAME_DB) $(LIBNAME_DB)
	printf "$(GREEN)$(NAME_DB) is ready.\n$(NC)"

$(OBJS_DB) : $(OPATH_DB)%.o : $(SPATH)%.c $(INCS)
	$(COMPILE_DB) $< -o $@
	printf "$(BLUE)  Compiling [DEBUG] $<\n $(NC)"

$(OPATH_DB) :
	$(MKDIR) $@

$(LIBFT_DB) : FORCE
	make -C $(LPATH) debug

clean:
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(OPATH_DB)
	make -C $(LPATH) clean

fclean:
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(OPATH_DB)
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAME_DB)
	$(CLEANUP) $(LIBNAME)
	$(CLEANUP) $(LIBNAME_DB)
	make -C $(LPATH) fclean

re: fclean all




# -fPIC : flag generates position-independent code, which accesses all constant address stored in the Global Offset Table (GOT). This table is used by executable programs to find, during runtime, address of functions  and global variables unknown in compile time. The dynamic loader — which is part of the Operating System — resolves the GOT entries when program starts
#  https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
#
# -shared  : flag generates a shared object which, at the moment to be compiled with another object file, it could be linked to form an executable file. -Wl,options passes options to linker: in this case, -soname, to indicate the binary api compatibility of the library (0, by default). -o flag saves the output library in a file with a given name — libcalc.so


.PHONY: all clean fclean norme re debug FORCE
.SILENT:


