#ifndef CATS_N_DOOM_MIXER_INIT
# define CATS_N_DOOM_MIXER_INIT

# include <SDL2/SDL_mixer.h>

# define CHUNK_SIZE 4096
# define CHANNELS 1
# define BACKGROUND_SOUND "sounds/E2M3_intermission.mp3"
# define PLAY_FOREVER -1

typedef struct	s_music
{
	Mix_Music	*background;
}				t_music;

void			mixer_init(void);
t_music			*sound_init(void);
Mix_Music		*load_music(void);
void			play_music(Mix_Music *music, int loops);
void			music_close(t_music *music);

#endif
