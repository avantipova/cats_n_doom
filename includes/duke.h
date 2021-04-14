// # include <SDL2/SDL.h>
#ifndef DUKE_H
# define DUKE_H

# define SCREEN_MULTIPLICATOR 1



# define TEXTURE_SCALE 0.3

# define TR_TYPE_WALL 0
# define TR_TYPE_CEIL 1
# define TR_TYPE_FLOOR 2

# define PHISICS_MODE_PLAYER 1
# define PHISICS_MODE_BULLET 2



#define W 720
#define H 720
#define H_2 360
#define W_2 360
#define HxW 518400
#define EPSILON 0.000001

#define CH 1
#define CW 1
#define V_SIZE 1
#define PROJ_PLANE_Z 1

#include "assets_folder_name.h"

#include "my_graphics_lib.h"

#include "data.h"
#include "helpers.h"
#include "linear_algebra.h"
// #include "Editor/editor.h"
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"


void	render_init(t_scene *scene);
void	clipping_planes_init(t_scene *scene);
void	level_init(t_doom *doom, char *foldername);
void	controls_init(t_doom *doom);
SDL_Surface	*create_texture(char *filename, int alpha);
t_anim		load_anim(char *foldername, float speed, int mode);

void	clip_1_outside(t_clip_triangle *cl, t_model *model, int k, int i);
void	clip_2_outsides(t_clip_triangle *cl, t_model *model, int k, int i);


void		clip_triangle(t_triangle *trs, t_plane *planes, t_model *model);

void	render_triangle(int *image_data, t_model *model, t_triangle *tr, t_scene *scene);

t_object	create_object(t_vertex pos, int index);


void put_pixel(int *image_data, int x, int y, int color);
void	interpolate(t_e_i_input in, t_float_array *dst);

void edge_interpolate(t_e_i_input in, t_render *render, t_edge_interpolate *edge);
t_e_i_output get_edge_inter(t_e_i_input in);

void concat(t_float_array *first, t_float_array *second);

//void	draw_line(int *image_data, t_point *p0, t_point *p1, int color);

float *create_z_buffer();
float *clear_z_buffer(float *z_buffer);
char *read_node(t_bsp *node, char *str);
char *add_vt_tr(t_bsp *node, char *str);
char *add_wall(t_bsp *node, char *str);
char	*add_enemy_d(t_doom *doom, char *ptr);
char	*add_object_d(t_doom *doom, char *ptr);
char	*add_ammo_d(t_doom *doom, char *ptr, int *ammo_count);
char	*add_aid_d(t_doom *doom, char *ptr, int *aid_count);
char	*read_enemies(t_doom *doom, char *ptr);
char *read_node(t_bsp *node, char *str);
char *read_vt_trs(t_bsp *node, char *str);
char *read_walls(t_bsp *node, char *str);
char *read_property(t_bsp *node, char *str);
char	*read_aid(t_doom *doom, char *ptr);
char	*read_ammo(t_doom *doom, char *ptr);
char	*read_tv(t_doom *doom, char *ptr);
char	*read_objects(t_doom *doom, char *ptr);
char *read_data_property(t_doom *doom, char *str);
int set_z_buffer(float *z_buffer, int x, int y, float value);
int set_z_buffer_bsp(float *z_buffer, int x, int y, float value);
t_mat4x4 update_instance_transform(t_instance *instance);

// int		get_texel(int *image_data, float u, float v, int pitch);

int get_texel(SDL_Surface *image_data, float u, float v);
int get_texel_n(int **image_data, float u, float v, int pitch);

void	bsp_render_traversal(t_bsp *node, t_scene *scene,
								t_instance *instance, t_model *model);

t_model	*transform_and_clip(t_instance *instance, t_mat4x4 transform,
							t_scene *scene, int mode);

void render_scene(int *image_data, t_scene *scene);
void	pthread_render(int *image_data, t_doom *doom);

float get_inter_d(float i0, float d0, float i1, float d1);

void get_normals(t_vertex *normals, int *count, char *file_name);
void get_uvss(t_model *model, char *file_name);
t_vertex	read_coords(char *line);
void read_obj(t_model *model, char *file_name);
void read_bsp(t_doom *doom, char *filename);
float	ft_atof(char *str);
int classify_point(t_vertex cam, t_vertex line, t_vertex normal);

t_enemy	create_enemy(t_vertex pos, float beta);
void	create_tv(t_doom *doom);


//void read_map(char *name, t_model *model, int **tex, int *texture);

////void create_box(t_model *model, int **new_tex, int *tex);

//t_bsp_node *create_bsp(t_model *model);

int		if_possible_to_move(t_vertex pos, t_bsp *node, int mode, float height);

void		get_floor_seil_traversal(t_bsp *node, t_vertex pos, float *floor, float *ceil);

char *itoa(int value, char *buf);

void clear_bsp(t_bsp *node);

int		check_hash(char *foldername);

void	draw_pixel(t_scene *scene, int *image_data, t_triangle *tr, int y_it);
void	sort_vertex_indexes(t_triangle *triangle, t_point *projected);
void	aid_init(t_doom *doom);
void	ammo_init(t_doom *doom);
void	bullets_init(t_doom *doom);
void	drb_init(t_doom *doom);
void	clean_anim(t_anim *anim);
void	clean_enemies(t_doom *doom);
void	remove_files();
void	draw_hud(t_doom *doom);
void	draw_press_f(t_doom *doom);
void	draw_lose(t_doom *doom);
void	draw_win(t_doom *doom);
void	draw_menu(t_doom *doom);
void	event_hand(SDL_Event *event, void *doom_ptr, int *quit);
void	restart(t_doom *doom);
SDL_Surface* renderText(char *message, char *font_file,
        SDL_Color color, int fontSize);
void	drb_animation_update(t_doom *doom);
void	update_sprites(t_doom *doom, float gamma);
void	update_aid(t_doom *doom);
void	update_ammo(t_doom *doom);
void	animation_update(t_scene *scene, float curr_time);
void	update_bullets(t_doom *doom);
void	update_enemies(t_doom *doom);
void	update(void *doom_ptr, int *pixels);
int		check_leaf(t_bsp *node, t_vertex pos);
int		check_enemy(t_doom *doom, t_vertex pos);
void	fire(t_doom *doom);

#endif
