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

SRCFILES		=	init.c guest.c stately_affairs.c main.c
SRCDIR			=	src

OBJFILES		=	$(SRCFILES:%.c=$(OBJDIR)/%.o)
OBJDIR			=	bin

INCLDIR			=	inc
INCLUDE			=	$(addprefix -I, $(INCLDIR))

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
VPATH			=	$(SRCDIR) $(OBJDIR)

NAME			=	philo

all				:	$(NAME)

$(NAME)			:	$(OBJFILES)
			$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

$(OBJDIR)/%.o	:	%.c | $(OBJDIR)
			$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
$(OBJDIR)		: ;	mkdir $(OBJDIR)

clean			:
			rm -rf $(OBJDIR)
fclean			:	clean
			rm -f $(NAME)

# Special variables
.PHONY			: clean fclean

# Canceling implicit rules
#%.o				:	%.c
