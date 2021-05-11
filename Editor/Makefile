
NAME = Editor

FLAGS = -Wextra -Wall -Werror

OBJECTS = editor.o my_graphics_lib.o image_handle.o linear_algebra.o \
				linear_algebra_1.o linear_algebra_2.o linear_algebra_3.o matrix.o \
				ftoa.o helpers.o bsp_helpers.o export.o export_func.o export_main.o export_main_func.o export_main_func1.o export1.o export2.o export3.o \
				export1_2_func.o plus_minus_enter_keys1.o hash.o init.o \
				draw_elements.o draw.o draw_func.o draw_trs_by_bsp.o mouse_handle.o add_elements_to_map.o\
				console_instructions_1.o console_instructions_2.o cursor_on_line_on_point.o \
				new_sector_new_point.o select_sector_by_bsp.o plus_minus_enter_keys.o bsp_recurse.o bsp_recurse_malloc.o \
				reconstruct_circuits.o key_down.o get_cutter.o computing_walls_1.o computing_walls_2.o \
				save_json_1.o save_json_2.o save_json_3.o save_json_3_func.o hash_2.o archiver.o get_next_line.o\

SOURCES = editor.c ../srcs/my_graphics_lib/my_graphics_lib.c ../srcs/image_handle.c ../srcs/math/linear_algebra.c \
				../srcs/math/linear_algebra.c ../srcs/math/linear_algebra_1.c \
				../srcs/math/linear_algebra_2.c ../srcs/math/linear_algebra_3.c ../srcs/math/matrix.c \
				../srcs/helpers/ftoa.c ../srcs/helpers/helpers.c bsp_helpers.c export.c export_func.c export_main.c export_main_func.c  export_main_func1.c export1.c export2.c export3.c \
				export1_2_func.c plus_minus_enter_keys1.c hash.c init.c \
				draw_elements.c draw.c draw_func.c draw_trs_by_bsp.c mouse_handle.c add_elements_to_map.c \
				console_instructions_1.c console_instructions_2.c cursor_on_line_on_point.c \
				new_sector_new_point.c select_sector_by_bsp.c plus_minus_enter_keys.c bsp_recurse.c bsp_recurse_malloc.c \
				reconstruct_circuits.c key_down.c get_cutter.c computing_walls_1.c computing_walls_2.c \
				save_json_1.c save_json_2.c save_json_3.c save_json_3_func.c hash_2.c ../Archiver/archiver.c ../srcs/get_next_line/get_next_line.c\

LIBS = -L ../libft -lft -lm -framework OpenGL\
	-framework AppKit -framework OpenCL -framework OpenGL

INCLUDES = -I ../includes/ -I../libft/ -I ../frameworks/SDL2.framework/Headers -I ../my_graphics_lib -I ../Archiver

FRAMEWORKS = -F ../frameworks -rpath ../frameworks -framework SDL2 \
	-framework SDL2_ttf -framework SDL2_mixer -framework SDL2_image

FTPATH = ../libft

LIBRARY = ./libft/libft.a

all: $(LIBRARY) $(NAME)

$(NAME): $(OBJECTS) $(LIBRARY)
	@gcc $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIBS) $(FRAMEWORKS) -o $(NAME)

$(OBJECTS): $(SOURCES)
	@gcc $(FLAGS) $(INCLUDES) -c $(SOURCES)

$(LIBRARY):
	@make -C ../libft

clean:
	@make -C $(FTPATH) clean
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@make -C $(FTPATH) fclean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re NAME
