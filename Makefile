##
## EPITECH PROJECT, 2024
## My_rpg
## File description:
## rpg for epitech
##

CC = gcc

CFLAGS = -L./lib/my/ -Wall -Wextra -std=c99 -I./include/

LIB = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

DEBUGCFLAGS = -g

SRC_FILES = main.c	\
	json/json_object.c	\
	json/json_get.c	\
	json/json_convert.c	\
	json/json_find.c	\
	json/json_line.c	\
	json/json_array.c	\
	others/shape.c	\
	others/is_char_in_str.c	\
	others/get_substr.c	\
	others/get_file_content.c	\
	others/find_struct.c	\
	others/pos.c	\
	game_data/game_data.c	\
	game_data/textures.c	\
	game_data/sprites.c	\
	game_data/window.c	\
	game_data/displays.c	\
	game_data/buttons.c	\
	others/array.c	\
	cmd/cmd.c	\
	actions/add_button_action.c	\
	init_buttons_action.c	\
	draw/draw.c	\
	draw/draw_stats.c	\
	event/process_events.c	\
	game_data/menus.c	\
	event/add_event.c	\
	init_keys_action.c	\
	actions/change_show.c	\
	actions/exit_action.c	\
	actions/check_box.c	\
	actions/show_menu.c	\
	actions/fullscreen.c	\
	others/get_struct.c	\
	my_rpg/return_menu.c	\
	my_rpg/set_starting_screen_actions.c	\
	my_rpg/fighting_action_button.c 	\
	game_data/musics.c	\
	game_data/entities.c	\
	my_rpg/exploration.c	\
	event/keyevents.c	\
	event/music_actions.c	\
	game_data/settings.c	\
	others/convert.c	\
	my_rpg/devcommand.c	\
	others/grid.c	\
	others/count_multiple.c	\
	update/update.c	\
	others/my_split_str.c	\
	game_data/map.c	\
	others/convert_line_map.c	\
	my_rpg/fight.c	\
	my_rpg/volume.c	\
	draw/devmode_draw.c	\
	draw/draw_potion.c	\
	draw/draw_text.c

SRC_DIR = src/

SRC = $(foreach file, $(SRC_FILES), $(addprefix $(SRC_DIR), $(file)))

OBJ = $(SRC:.c = .o)

NAME = my_rpg

DEBUGNAME = my_rpg_dev

all: $(NAME)
	@echo "my_rpg successfully build"

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIB)
	@make -C ./ clean

debug: $(DEBUGNAME)

$(DEBUGNAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(DEBUGCFLAGS) -o $(DEBUGNAME) $(LIB)
	@make -C ./ clean

clean:
	@rm -f *.o
	@rm -f vgcore.*

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)
	@echo "$(NAME) successfully re-build"

.PHONY: all clean fclean re
