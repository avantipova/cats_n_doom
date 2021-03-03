#include <SDL2/SDL_mixer.h>
#include "mixer_init.h"
#include "../libft/libft.h"

void mixer_init(void)
{
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE) < 0)
	{
		ft_putstr("Mixer open audio error\n");
		exit(EXIT_FAILURE);
	}
}
