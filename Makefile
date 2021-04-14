
NAME = DoomNukem

FLAGS = -std=c11 -Wextra -Wall -Werror

OBJECTS_DIR = objs

SOURCES_DIR = srcs

SRC_NAMES = srcs/main.c srcs/image_handle.c \
				srcs/bullet_helpers.c \
				srcs/check_enemies.c \
				srcs/some_func.c \
				srcs/traversal.c \
				srcs/updates/drb_animation_update.c \
				srcs/updates/update.c \
				srcs/updates/update_aid.c \
				srcs/updates/update_ammo.c \
				srcs/updates/update_animations.c \
 				srcs/updates/update_bullets.c \
				srcs/updates/update_enemies.c \
				srcs/updates/update_sprites.c \
				srcs/draw/draw.c srcs/draw/transforms.c srcs/draw/render_scene.c \
				srcs/draw/pthread.c srcs/draw/draw_hud.c srcs/draw/draw_smth.c\
				srcs/math/interpolate.c srcs/math/linear_algebra.c \
				srcs/math/linear_algebra_1.c srcs/math/linear_algebra_2.c \
				srcs/math/linear_algebra_3.c srcs/math/matrix.c \
				srcs/depth_buffer.c \
				srcs/get_next_line/get_next_line.c \
				srcs/load_obj/load_obj.c srcs/load_obj/get_smth.c \
				srcs/my_graphics_lib/my_graphics_lib.c\
				srcs/render/render_init.c srcs/render/render_init_1.c \
				srcs/render/render_triangle.c \
				srcs/render/draw_pixel.c srcs/render/vertex.c \
				srcs/render/render_text.c \
				srcs/textures_handling.c \
				srcs/clips/clip_triangle_by_planes.c \
				srcs/clips/clip_1_outside.c srcs/clips/clip_2_outsides.c \
				srcs/read_bsp/read_bsp.c srcs/read_bsp/add_smth.c srcs/read_bsp/add_smth_1.c \
				srcs/read_bsp/read_smth.c srcs/read_bsp/read_smth_1.c srcs/read_bsp/read_property.c \
				srcs/read_bsp/read_data_property.c srcs/read_bsp/add_walls.c\
				srcs/helpers/ftoa.c srcs/helpers/ft_atof.c\
				Editor/hash.c Editor/hash_2.c \
				srcs/sound/mixer_init.c srcs/sound/sound_init.c srcs/sound/load_music.c \
				srcs/sound/play_music.c srcs/sound/music_close.c \
                srcs/sound/load_sound.c Archiver/dearchiver.c\
				srcs/init/aid_init.c srcs/init/ammo_init.c srcs/init/bullets_init.c srcs/init/drb_init.c \
				srcs/creates/create_enemies.c srcs/creates/create_objects.c srcs/creates/create_tv.c \
				srcs/events/event_handle.c srcs/events/restart.c \
				srcs/clear/clean_objects.c \


OBJ = $(SRC_NAMES:.c=.o)

OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(OBJ))

LIBS = -L./libft -lft -lm -framework OpenGL\
	-framework AppKit -framework OpenCL -framework OpenGL

INCLUDES = -I includes -I Editor -I./libft/ -I./frameworks/SDL2.framework/Headers -I./my_graphics_lib \
			-I./frameworks/SDL2_mixer.framework/Headers -I./srcs/sound -I./Archiver

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

LIBRARY = ./libft/libft.a

all: $(LIBRARY) $(NAME) Build_print

$(LIBRARY):
	cd Editor && make
	make -C libft

$(NAME): $(OBJECTS) $(LIBRARY) 
	@clang $(LIBRARY) $(FLAGS) $(LIBS) $(FRAMEWORKS) $^ -o $@ $(INCLUDES)

COMPILE_PRINT = \x1b[32;01m Compiling...
BUILD_PRINT = \x1b[32;01m Executable file created
CLEAN_PRINT = \x1b[31;01mdeleted all object files
FCLEAN_PRINT = \x1b[31;01mand executable file

Compile_print:
	@printf "$(COMPILE_PRINT)\n"

Build_print:
	@printf "$(BUILD_PRINT)\n"

Clean_print:
	@printf "$(CLEAN_PRINT)\n"

Fclean_print:
	@printf "$(FCLEAN_PRINT)\n"

$(OBJECTS_DIR)/%.o: %.c Compile_print
	@mkdir $(OBJECTS_DIR) 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/init 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/Editor 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/Archiver 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/get_next_line 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/my_graphics_lib 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/sound 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/render 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/math 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/helpers 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/clips 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/read_bsp 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/load_obj 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/draw 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/clear 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/creates 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/events 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/updates 2> /dev/null || true

	@clang $(FLAGS) -c $< $(INCLUDES) -o $@

clean: Clean_print
	@make -C libft clean
	@cd Editor && make clean
	@rm -rf $(OBJECTS_DIR)

fclean: clean Fclean_print
	@make -C libft fclean
	@cd Editor && make fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean

.INTERMEDIATE: Compile_print Clean_print Fclean_print