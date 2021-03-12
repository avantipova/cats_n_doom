#include "mixer_init.h"

void	music_close(t_music *music)
{
	Mix_FreeMusic(music->background);
	Mix_FreeChunk(music->shotgun);
	free(music);
	Mix_CloseAudio();
}
