
NAME = DoomNukem

FLAGS = -Wextra -Wall -Werror

OBJECTS_DIR = objs

OBJECTS = main.o image_handle.o draw.o interpolate.o linear_algebra.o depth_buffer.o \
				get_next_line.o load_obj.o my_graphics_lib.o \
				render_init.o textures_handling.o clip_triangle_by_planes.o \
				clip_1_outside.o clip_2_outsides.o render_triangle.o read_bsp.o ftoa.o hash.o hash_2.o \
				mixer_init.o sound_init.o load_music.o play_music.o music_close.o load_sound.o

OBJECTS_S = $(addprefix $(OBJECTS_DIR)/,$(OBJECTS_LIST))

SOURCES = main.c image_handle.c draw.c interpolate.c linear_algebra.c depth_buffer.c \
				get_next_line/get_next_line.c load_obj.c my_graphics_lib/my_graphics_lib.c\
				render_init.c textures_handling.c clip_triangle_by_planes.c \
				clip_1_outside.c clip_2_outsides.c render_triangle.c read_bsp.c ftoa.c Editor/hash.c Editor/hash_2.c \
				sound/mixer_init.c sound/sound_init.c sound/load_music.c sound/play_music.c sound/music_close.c \
				sound/load_sound.c

LIBS = -L./libft -lft -lm

INCLUDES = -I./libft/ -I./my_graphics_lib -I./sound -I./frameworks/SDL2.framework/Headers

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

FTPATH = ./libft

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $(FLAGS) -fsanitize=address $(OBJECTS) $(INCLUDES) $(LIBS) $(FRAMEWORKS) -o $(NAME) -g

$(OBJECTS):
	make -C $(FTPATH)
	gcc -fsanitize=address $(FLAGS) $(INCLUDES) -c $(SOURCES) -g
	

clean:
	make -C $(FTPATH) clean
	/bin/rm -f $(OBJECTS)

fclean: clean
	make -C $(FTPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
