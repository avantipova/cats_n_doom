#include "duke.h"
#include "mixer_init.h"
#include "SDL_mixer.h"
#include "archiver.h"

int	main(int ac, char **av)
{
	t_mgl		mgl;
	t_doom		doom;
	SDL_Color	color;
	SDL_Texture	*tex;
	SDL_Surface	*temp;
	SDL_Rect	rect;

	doom.music = 0;
	if (ac < 2)
		exit(-2);
	dearchivate(av[1]);
	if (!check_hash(ASSETS_FOLDER_NAME "/"))
	{
		ft_putendl("Файлы повреждены");
		exit(-2);
	}
	puts("OK");
	mgl = mgl_init("Doom_Quaekem", W, H, SCREEN_MULTIPLICATOR);
	doom.music = sound_init();
	doom.screen_nmb = 0;

//загрузка музона



	play_music(doom.music->background, PLAY_FOREVER);
	mgl.show_fps = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom.mgl = &mgl;
	doom.solid = 0;
	doom.g_speed = 0;
	doom.scene.level.instance.model.anim = NULL;
	doom.scene.level.instance.model.new_tex[0] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/1.bmp", 0);
	doom.scene.level.instance.model.new_tex[1] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/2.bmp", 0);
	doom.scene.level.instance.model.new_tex[2] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/3.bmp", 0);
	doom.scene.level.instance.model.new_tex[3] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/4.bmp", 0);
	doom.scene.level.instance.model.new_tex[4] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/5.bmp", 0);
	doom.scene.level.instance.model.new_tex[5] = \
				create_texture(ASSETS_FOLDER_NAME "/textures/6.bmp", 0);
	doom.scene.sprites = malloc(sizeof(t_sprite) * 200);
	doom.scene.sprites_count = 0;
	doom.scene.objects = malloc(sizeof(t_object) * 200);
	doom.scene.objects_count = 0;
	doom.health = 100;
	doom.player_ammo = 10;
	doom.height = 1.7;
	doom.sit = 0;
	doom.run = 0;
	doom.menu_opened = 1;
	doom.difficulty = 0;
	doom.enemy_damage = 10;
	doom.enemy_speed = 0.04;
	doom.kills = 0;
	doom.health_bar = NULL;
	doom.ammo_bar = NULL;
	doom.kills_bar = NULL;
	doom.win = 0;
	doom.lose = 0;
	bullets_init(&doom);
	ammo_init(&doom);
	aid_init(&doom);
	drb_init(&doom);
	level_init(&doom, ASSETS_FOLDER_NAME "/");
	render_init(&doom.scene);
	clipping_planes_init(&doom.scene);
	controls_init(&doom);
	TTF_Init();
	color.r = 0;
	color.g =0;
	color.b = 0;
	doom.flag = 0;
	doom.menu_back = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
	doom.open_menu = SDL_LoadBMP("/Editor/textures/good_trip.bmp");
	if (doom.open_menu == NULL)
		return (1);
	doom.menu.active = 0;
	doom.menu.play = renderText("PLAY", ASSETS_FOLDER_NAME \
								"/fonts/DoomsDay.ttf", color, 100);
	doom.menu.difficulty_1 = renderText("DIFFICULTY LVL 1", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom.menu.difficulty_2 = renderText("DIFFICULTY LVL 2", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom.menu.difficulty_3 = renderText("DIFFICULTY LVL 3", \
			ASSETS_FOLDER_NAME "/fonts/DoomsDay.ttf", color, 100);
	doom.menu.exit_b = renderText("EXIT", ASSETS_FOLDER_NAME \
							"/fonts/DoomsDay.ttf", color, 100);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	doom.press_f = renderText("Press F", ASSETS_FOLDER_NAME \
							"/fonts/DoomsDay.ttf", color, 70);
	doom.win_surface = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
	doom.lose_surface = create_texture(ASSETS_FOLDER_NAME \
									"/textures/menu.bmp", 0);
	rect.x = -200;
	rect.y = -100;
	rect.w = W + 400;
	rect.h = H + 200;
	color.r = 35;
	color.g = 151;
	color.b = 35;
	temp = renderText("WIN", ASSETS_FOLDER_NAME \
						"/fonts/DoomsDay.ttf", color, 300);
	SDL_BlitScaled(temp, &rect, doom.win_surface, NULL);
	color.r = 94;
	color.g = 6;
	color.b = 6;
	SDL_FreeSurface(temp);
	temp = renderText("LOSE", ASSETS_FOLDER_NAME \
						"/fonts/DoomsDay.ttf", color, 300);
	SDL_BlitScaled(temp, &rect, doom.lose_surface, NULL);
	SDL_FreeSurface(temp);
	tex = SDL_CreateTextureFromSurface(doom.mgl->renderer, doom.open_menu);
	SDL_RenderCopy(doom.mgl->renderer, tex, NULL, NULL);
	SDL_RenderPresent(doom.mgl->renderer);
	mgl_run(&mgl, update, event_hand, &doom);
	music_close(doom.music);
	SDL_DestroyTexture(tex);
	mgl_quit(&mgl);
	return (0);
}
