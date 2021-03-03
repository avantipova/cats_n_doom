#include "mixer_init.h"

void music_close(t_music *music)
{
	Mix_FreeMusic(music->background);
	free(music);
	Mix_CloseAudio();
}
