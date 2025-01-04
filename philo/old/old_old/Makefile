# **************************************************************************** #
#                                                                              #
#                                                          ::::::::            #
#    Makefile                                            :+:    :+:            #
#                                                       +:+                    #
#    By: mde-beer <mde-beer@student.codam.nl>          +#+                     #
#                                                     +#+                      #
#    Created: 2024/12/17 14:22:04 by mde-beer       #+#    #+#                 #
#    Updated: 2024/12/19 15:59:53 by mde-beer       ########   odam.nl         #
#                                                                              #
# **************************************************************************** #


SRCFILES		=	main.c
SRCDIR			=	source

OBJFILES		=	$(SRC:.c=.o)
OBJDIR			=	bin

LIBFILES		=	libft.a libftprintf.a
LIBDIRS			=	libft libftprintf
LIBSUPERDIR		=	lib
LIBS			=	$(addprefix $(LIBSUPERDIR)/,$(LIBDIRS))
LIBINCL			=	$(addsuffix /include, $(LIBS))

INCLDIR			=	include
INCLUDE			=	$(addprefix -I ,$(INCLDIR) $(LIBINCL))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
VPATH			=	$(SRCDIR) $(OBJDIR) $(LIBS)

NAME			=	philo

all				:	$(NAME)

$(NAME)			:	$(OBJFILES)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $@ $^

$(OBJDIR)/%.o	: %.c $(LIBS) | $(OBJDIR)
			$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

$(OBJDIR)		: ; mkdir $(OBJDIR)

clean			:
			rm -rf $(OBJDIR)
			$(foreach dir, $(LIBS), $(MAKE) -C $(dir) clean;)

fclean			:	clean
			rm -f $(NAME)
			$(foreach dir, $(LIBS), $(MAKE) -C $(dir) fclean;)

# Special variables
.PHONY			: clean fclean

# Canceling the implicit rule
%.o				:	%.c
