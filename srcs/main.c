#include "duke.h"
#include "mixer_init.h"
#include "SDL_mixer.h"

void	init_p1(t_doom *doom, t_mgl *mgl)
{
	doom->menu_back = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
	doom->open_menu = SDL_LoadBMP("/Editor/textures/good_trip.bmp");
	doom->mgl = mgl;
	doom->solid = 0;
	doom->g_speed = 0;
	doom->scene.level.instance.model.anim = NULL;
	doom->scene.level.instance.model.new_tex[0] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/1.bmp", 0);
	doom->scene.level.instance.model.new_tex[1] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/2.bmp", 0);
	doom->scene.level.instance.model.new_tex[2] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/3.bmp", 0);
	doom->scene.level.instance.model.new_tex[3] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/4.bmp", 0);
	doom->scene.level.instance.model.new_tex[4] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/5.bmp", 0);
	doom->scene.level.instance.model.new_tex[5] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/6.bmp", 0);
}

void	init_p2(t_doom *doom)
{
	SDL_Color	color;

	color = (SDL_Color){0, 0, 0, 0};
	doom->flag = 0;
	doom->menu.active = 0;
	doom->menu.play = renderText("PLAY", ASSETS_FOLDER_NAME \
								"/fonts/DoomsDay.ttf", color, 100);
	doom->menu.difficulty_1 = renderText("DIFFICULTY LVL 1", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom->menu.difficulty_2 = renderText("DIFFICULTY LVL 2", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom->menu.difficulty_3 = renderText("DIFFICULTY LVL 3", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom->menu.exit_b = renderText("EXIT", ASSETS_FOLDER_NAME \
							"/fonts/DoomsDay.ttf", color, 100);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	doom->press_f = renderText("Press F", ASSETS_FOLDER_NAME \
							"/fonts/DoomsDay.ttf", color, 70);
	doom->win_surface = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
	doom->lose_surface = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
}

static void	prepare_2(t_doom *doom)
{
	doom->health = 100;
	doom->player_ammo = 10;
	doom->height = 1.7;
	doom->sit = 0;
	doom->run = 0;
	doom->menu_opened = 1;
	doom->difficulty = 0;
	doom->enemy_damage = 10;
	doom->enemy_speed = 0.04;
	doom->kills = 0;
	doom->health_bar = NULL;
	doom->ammo_bar = NULL;
	doom->kills_bar = NULL;
	doom->win = 0;
	doom->lose = 0;
}

void	prepare(t_doom *doom)
{
	bullets_init(doom);
	ammo_init(doom);
	aid_init(doom);
	drb_init(doom);
	level_init(doom, ASSETS_FOLDER_NAME "/");
	render_init(&doom->scene);
	clipping_planes_init(&doom->scene);
	controls_init(doom);
	TTF_Init();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->music = sound_init();
	doom->screen_nmb = 0;
	doom->scene.sprites = malloc(sizeof(t_sprite) * 200);
	doom->scene.sprites_count = 0;
	doom->scene.objects = malloc(sizeof(t_object) * 200);
	doom->scene.objects_count = 0;
	prepare_2(doom);
}

int	main(int ac, char **av)
{
	t_mgl		mgl;
	t_doom		doom;
	SDL_Texture	*tex;

	check_arguments(ac, av);
	mgl = mgl_init("Doom_Quaekem", W, H, SCREEN_MULTIPLICATOR);
	mgl.show_fps = 1;
	prepare(&doom);
	play_music(doom.music->background, PLAY_FOREVER);
	init_p1(&doom, &mgl);
	if (doom.open_menu == NULL)
		return (1);
	init_p2(&doom);
	render_text(&doom);
	welcome_screen(&doom, &tex);
	mgl_run(&mgl, update, event_hand, &doom);
	music_close(doom.music);
	SDL_DestroyTexture(tex);
	mgl_quit(&mgl);
	return (0);
}
