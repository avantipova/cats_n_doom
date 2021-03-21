
NAME = DoomNukem

FLAGS = -std=c11 -Wextra -Wall -Werror

OBJECTS_DIR = objs

SOURCES_DIR = srcs

SRC_NAMES = srcs/main.c srcs/image_handle.c srcs/draw.c srcs/interpolate.c srcs/linear_algebra.c srcs/depth_buffer.c \
				srcs/get_next_line/get_next_line.c srcs/load_obj.c srcs/my_graphics_lib/my_graphics_lib.c\
				srcs/render_init.c srcs/textures_handling.c srcs/clip_triangle_by_planes.c \
				srcs/clip_1_outside.c srcs/clip_2_outsides.c srcs/render_triangle.c srcs/read_bsp.c srcs/ftoa.c \
				Editor/hash.c Editor/hash_2.c

OBJ = $(SRC_NAMES:.c=.o)

OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(OBJ))

LIBS = -L./libft -lft -lm -framework OpenGL\
	-framework AppKit -framework OpenCL -framework OpenGL

INCLUDES = -I includes/ -I Editor/includes -I./libft/ -I./frameworks/SDL2.framework/Headers

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

LIBRARY = ./libft/libft.a

all: $(LIBRARY) $(NAME) Build_print

$(LIBRARY):
	@cd Editor && make
	@make -C libft

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
	@mkdir $(OBJECTS_DIR)/Editor 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/get_next_line 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/srcs/my_graphics_lib 2> /dev/null || true
	@clang $(FLAGS) -c $< $(INCLUDES) -o $@

clean: Clean_print
	@make -C libft clean
	@cd Editor && make clean
	@rm -rf $(OBJECTS)

fclean: clean Fclean_print
	@make -C libft fclean
	@cd Editor && make fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean

.INTERMEDIATE: Compile_print Clean_print Fclean_print