
NAME = DoomNukem

FLAGS = -Wextra -Wall -Werror

OBJECTS_DIR = objs

SOURCES_DIR = srcs

SRC_NAMES = main.c image_handle.c draw.c interpolate.c linear_algebra.c depth_buffer.c \
				get_next_line/get_next_line.c load_obj.c my_graphics_lib/my_graphics_lib.c\
				render_init.c textures_handling.c clip_triangle_by_planes.c \
				clip_1_outside.c clip_2_outsides.c render_triangle.c read_bsp.c ftoa.c Editor/hash.c Editor/hash_2.c \

OBJ = $(SRC_NAMES:.c=.o)

SOURCES = $(addprefix $(SOURCES_DIR)/,$(SRC_NAMES))

OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(OBJ))

LIBS = -L./libft -lft -lm -framework OpenGL\
	-framework AppKit -framework OpenCL -framework OpenGL

INCLUDES = -I includes -I./libft/ -I./frameworks/SDL2.framework/Headers -I./my_graphics_lib

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

LIBRARY = ./libft/libft.a

all: $(LIBRARY) $(NAME)

$(LIBRARY):
	@make -C libft

$(NAME): $(OBJECTS) $(LIBRARY)
	@clang $(LIBRARY) $(FLAGS) $(LIBS) $(FRAMEWORKS) $^ -o $@ $(INCLUDES)

BUILD_PRINT = \x1b[32;01mbuilding...
CLEAN_PRINT = \x1b[31;01mdeleted all object files
FCLEAN_PRINT = \x1b[31;01mand executable file

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir $(OBJECTS_DIR) 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/get_next_line 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/Editor 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/my_graphics_lib 2> /dev/null || true
	@echo "$(BUILD_PRINT)\n"
	@clang $(FLAGS) -c $< $(INCLUDES) -o $@

clean:
	@echo "$(CLEAN_PRINT)\n"
	@make -C libft clean
	@rm -rf $(OBJECTS)
	@rm -rf $(OBJECTS_DIR)/get_next_line 2> /dev/null || true
	@rm -rf $(OBJECTS_DIR)/Editor 2> /dev/null || true
	@rm -rf $(OBJECTS_DIR)/my_graphics_lib 2> /dev/null || true

fclean: clean
	@echo "$(FCLEAN_PRINT)\n"
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all
