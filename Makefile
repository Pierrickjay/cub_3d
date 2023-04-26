# COLOR

CLEAR		:= \e[0K

SRED		:= \033[0;31m
SGREEN		:= \033[0;32m
SYELLOW		:= \033[0;33m
SCYAN		:= \033[0;36m
SPURPLE		:= \033[0;35m
SOFF		:= \033[0m

RED			:= '\033[0;31m'
GREEN		:= '\033[0;32m'
YELLOW		:= '\033[0;33m'
CYAN		:= '\033[0;36m'
PURPLE		:= '\033[0;35m'
OFF			:= '\033[0m'

# VARIABLES

NAME			:= cub3D

NAME_BONUS		:= cub3D_bonus

# SRCS

#  LIBFT


SRCS_LIBFT_DIR	:= srcs/libft/

SRCS_LIBFT		:= char/ft_isalnum.c char/ft_isalpha.c char/ft_isascii.c char/ft_isdigit.c \
				char/ft_isprint.c char/ft_tolower.c char/ft_toupper.c char/ft_all_isdigit.c \
				conversion/ft_atoi.c conversion/ft_atoi_long.c conversion/ft_itoa.c \
				malloc/ft_calloc.c malloc/ft_split.c malloc/ft_strdup.c malloc/ft_strjoin.c malloc/ft_strjoin_all.c malloc/ft_strmapi.c \
				malloc/ft_strtrim.c malloc/ft_substr.c mem/ft_bzero.c mem/ft_memchr.c mem/ft_memcmp.c \
				mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c \
				print/ft_putchar_fd.c print/ft_putendl_fd.c print/ft_putnbr_fd.c print/ft_putstr_fd.c \
				string/ft_strchr.c string/ft_striteri.c string/ft_strlcat.c string/ft_strlcpy.c \
				string/ft_strlen.c string/ft_strcmp.c string/ft_strncmp.c string/ft_strnstr.c string/ft_strrchr.c \
				liste_chaine/ft_lstnew.c gnl/get_next_line.c gnl/get_next_line_utils.c\
				liste_chaine/ft_lstadd_front.c liste_chaine/ft_lstsize.c liste_chaine/ft_lstlast.c \
				liste_chaine/ft_lstadd_back.c liste_chaine/ft_lstdelone.c liste_chaine/ft_lstclear.c \
				liste_chaine/ft_lstiter.c liste_chaine/ft_lstmap.c liste_chaine/ft_lstprint_type.c \
				liste_chaine/ft_lstjoin.c math/ft_min.c string/ft_print_strs.c

SRCS_LIBFT		:= ${addprefix ${SRCS_LIBFT_DIR},${SRCS_LIBFT}}

#  MINISHELL

INC_DIR := includes/

SRCS_DIR	:= srcs/cub_3d/

SRCS		+= main.c parsing/check_parsing.c parsing/init_map.c parsing/init_data.c parsing/init_map_utils.c \
			free.c parsing/cell.c parsing/map_check.c parsing/parse_line.c parsing/load_image.c parsing/frexit.c\
			parsing/color.c \
			game/game.c game/hook.c game/change_pos.c  game/render_3d_utils.c\
			game/draw_lines.c game/h_intersect.c game/v_intersect.c game/draw.c game/point_utils.c \
			parsing/del_cats.c \
			game/distance.c game/render_3d.c

SRCS_BONUS	+= main_bonus.c parsing/check_parsing.c parsing/init_map.c parsing/init_data.c parsing/init_map_utils.c \
			free.c parsing/cell.c parsing/map_check_bonus.c parsing/parse_line.c parsing/load_image.c parsing/frexit.c parsing/color.c parsing/init_cat.c\
			game/game.c  game/set_move_player_bonus.c game/cat_bonus.c\
			 game/hook_bonus.c  game/mouse_move_hook_bonus.c game/render_3d_utils.c\
			game/draw_lines.c game/h_intersect.c game/v_intersect.c game/point_utils.c \
			game/distance.c game/draw_bonus.c game/render_3d_bonus.c game/change_pos_bonus.c parsing/cats_map.c parsing/del_cats.c game/list_cat.c\

SRCS_BONUS	:= ${addprefix ${SRCS_DIR},${SRCS_BONUS}}

SRCS		:= ${addprefix ${SRCS_DIR},${SRCS}}

# OBJS & DEPS & LIB

LIB_DIR			:= ./lib/

OBJS_DIR		:= ./objs/

OBJS_LIBFT		:= ${SRCS_LIBFT:.c=.o}

OBJS_LIBFT		:= $(addprefix $(OBJS_DIR),$(OBJS_LIBFT))

OBJS			:= $(SRCS:.c=.o)

OBJS			:= $(addprefix $(OBJS_DIR),$(OBJS))

OBJS_BONUS		:= $(SRCS_BONUS:.c=.o)

OBJS_BONUS		:= $(addprefix $(OBJS_DIR),$(OBJS_BONUS))

DEPS			:= ${OBJS:.o=.d} ${OBJS_LIBFT:.o=.d} ${OBJS_BONUS:.o=.d}

MLX_PATH		:= minilibx-linux/

MLX				:= $(MLX_PATH)/libmlx.a

# PROGRESS BAR

NB_OBJS			= ${words ${OBJS}, ${OBJS_LIBFT}}

COUNTER			= 1

PROGRESS		= 0

DONE 			= 100

SPACE		 	= 0

FILL			= 0

EMPTY			= 0

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJS)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /█/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /█/g'))
	printf "\r${CLEAR}${SYELLOW}Compile : ${SGREEN}${FILL}${SRED}${EMPTY} ${SGREEN}%3d%%${SOFF} %s.c" ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

# COMMANDS

AR				:= ar rcs

CC				:= cc

CFLAGS			:= -Wall -Wextra -Werror -MMD -g3

RM				:= rm -rf

MKDIR			:= mkdir -p

# RULES

all		: ${NAME} ${NAME_BONUS}

bonus	: ${NAME_BONUS}

${NAME}	: ${OBJS_LIBFT} ${OBJS} $(MLX)
		@${MKDIR} ${LIB_DIR}
		@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
		@${CC} ${CFLAGS} ${OBJS} $(MLX) -I $(INC_DIR) -o ${NAME} -L/usr/include -lXext -lX11 -lm ${LIB_DIR}libft.a
		@printf "\r${CLEAR}${SCYAN}${NAME}${SOFF} ${SGREEN}✔${SOFF}\n"

${NAME_BONUS} : ${OBJS_LIBFT} ${OBJS_BONUS} $(MLX)
		@${MKDIR} ${LIB_DIR}
		@${AR} ${LIB_DIR}libft.a ${OBJS_LIBFT}
		@${CC} ${CFLAGS} ${OBJS_BONUS} $(MLX) -I $(INC_DIR) -o ${NAME_BONUS} -L/usr/include -lXext -lX11 -lm ${LIB_DIR}libft.a
		@printf "\r${CLEAR}${SCYAN}${NAME_BONUS}${SOFF} ${SGREEN}✔${SOFF}\n"

$(MLX) :
		make -C $(MLX_PATH)

clean	:
		@${RM} ${OBJS_DIR} ${LIB_DIR}
		@printf "${SCYAN}All objects and library ${SRED}delete ${SOFF}\n"

fclean	: clean
		@${RM} ${NAME} ${NAME_BONUS}
		@printf "${SCYAN}${NAME}${SRED} delete${SOFF}\n"

re		: fclean all

.PHONY	: all clean fclean re test

# RECETTE

$(OBJS_DIR)%.o	: %.c
				@${MKDIR} $(@D)
				${CC} ${CFLAGS} -c $< -I $(INC_DIR) -o $@
#				@$(call PROGRESS_BAR, $(basename $(notdir $<)))



-include $(DEPS)
