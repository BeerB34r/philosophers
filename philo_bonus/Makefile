# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: mde-beer <mde-beer@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2024/12/31 13:34:20 by mde-beer     #+#    #+#                   #
#    Updated: 2024/12/31 14:28:24 by mde-beer     ########   odam.nl           #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all re clean fclean run

SRCFILES		=
SRCDIR			=	src

OBJFILES		=	$(SRCFILES:%.c=%.o)
OBJDIR			=	bin

HEADERS			=
INCLDIR			=	inc
INCLUDE			=	$(addprefix -I, $(INCLDIR))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
VPATH			=	$(SRCDIR) $(OBJDIR) $(INCLDIR)
MAKEFLAGS		+=	-j$(shell nproc) --output-sync=target --no-print-directory
.DEFAULT_GOAL	=	all

NAME			=	philo_bonus

all				:	$(NAME)
$(OBJDIR)		: ;	mkdir $(OBJDIR)
clean			: ;	rm -rf $(OBJDIR)
fclean			:	clean ;	rm -f $(NAME)
re				:	fclean $(NAME)
run				:	$(NAME) ;	./$(NAME)

$(NAME)			:	$(OBJFILES)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJDIR)/%.o	:	%.c $(HEADERS) | $(OBJDIR)
			$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

