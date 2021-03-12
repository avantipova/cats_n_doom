#ifndef CATS_N_DOOM_MIXER_INIT
# define CATS_N_DOOM_MIXER_INIT

# include <SDL2/SDL_mixer.h>

# define CHUNK_SIZE 4096
# define CHANNELS 1
# define BACKGROUND_MUSIC "sounds/E2M3_intermission.mp3"
# define SHOTGUN_SOUND "sounds/shotgun.wav"
# define PLAY_FOREVER -1

typedef struct	s_music
{
	Mix_Music	*background;
	Mix_Chunk	*shotgun;
}				t_music;

void			mixer_init(void);
t_music			*sound_init(void);
void			load_music(t_music *music);
void			play_music(Mix_Music *music, int loops);
void			music_close(t_music *music);
void			load_sound(t_music *music);

#endif
