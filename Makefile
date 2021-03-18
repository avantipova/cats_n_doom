
NAME = DoomNukem

FLAGS = -std=c11 -Wextra -Wall -Werror

OBJECTS_DIR = objs

SOURCES_DIR = srcs

SRC_NAMES = main.c image_handle.c draw.c interpolate.c linear_algebra.c depth_buffer.c \
				get_next_line/get_next_line.c load_obj.c my_graphics_lib/my_graphics_lib.c\
				render_init.c textures_handling.c clip_triangle_by_planes.c \
				clip_1_outside.c clip_2_outsides.c render_triangle.c read_bsp.c ftoa.c \

OBJ = $(SRC_NAMES:.c=.o)

SOURCES = $(addprefix $(SOURCES_DIR)/,$(SRC_NAMES))

OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(OBJ))

LIBS = -L./libft -lft -lm -framework OpenGL\
	-framework AppKit -framework OpenCL -framework OpenGL

INCLUDES = -I includes -I./libft/ -I./frameworks/SDL2.framework/Headers

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

LIBRARY = ./libft/libft.a

all: $(LIBRARY) $(NAME) Compile_print Build_print

$(LIBRARY):
	@cd Editor && make
	@make -C libft

$(NAME): $(OBJECTS) $(LIBRARY) 
	@clang Editor/Editor $(LIBRARY) $(FLAGS) $(LIBS) $(FRAMEWORKS) $^ -o $@ $(INCLUDES)

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

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c Compile_print
	@mkdir $(OBJECTS_DIR) 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/get_next_line 2> /dev/null || true
	@mkdir $(OBJECTS_DIR)/my_graphics_lib 2> /dev/null || true
	@clang $(FLAGS) -c $< $(INCLUDES) -o $@

clean: Clean_print
	@make -C libft clean
	@cd Editor && make clean
	@rm -rf $(OBJECTS)
	@rm -rf $(OBJECTS_DIR)/get_next_line 2> /dev/null || true
	@rm -rf $(OBJECTS_DIR)/my_graphics_lib 2> /dev/null || true

fclean: clean Fclean_print
	@make -C libft fclean
	@cd Editor && make fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all

.INTERMEDIATE: Compile_print Clean_print Fclean_print