# **************************************************************************** #
#                                                                              #
#                                                          ::::::::            #
#    Makefile                                            :+:    :+:            #
#                                                       +:+                    #
#    By: mde-beer <mde-beer@student.codam.nl>          +#+                     #
#                                                     +#+                      #
#    Created: 2024/12/24 06:44:38 by mde-beer       #+#    #+#                 #
#    Updated: 2024/12/24 07:07:15 by mde-beer       ########   odam.nl         #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all re clean fclean run

SRCFILES		=	error.c init.c main.c philo.c stately_affairs.c verb.c
SRCDIR			=	src

OBJFILES		=	$(SRCFILES:%.c=$(OBJDIR)/%.o)
OBJDIR			=	bin

HEADERS			=	philo.h
INCLDIR			=	inc
INCLUDE			=	$(addprefix -I, $(INCLDIR))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
VPATH			=	$(SRCDIR) $(OBJDIR) $(INCLDIR)
MAKEFLAGS		+=	-j$(shell nproc) --output-sync=target --no-print-directory
.DEFAULT_GOAL	=	all

NAME			=	philo

all				:	$(NAME)
$(OBJDIR)		: ;	mkdir $(OBJDIR)
clean			: ;	rm -rf $(OBJDIR)
fclean			:	clean ;	rm -f $(NAME)
re				:	fclean $(NAME)
run				:	$(NAME) ;	./$(NAME) $(PARAMS)

$(NAME)			:	$(OBJFILES)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJDIR)/%.o	:	%.c $(HEADERS) | $(OBJDIR)
			$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

# Canceling implicit rules
#%.o				:	%.c
