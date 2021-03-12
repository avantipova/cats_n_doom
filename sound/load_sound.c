#include <SDL2/SDL_mixer.h>
#include "mixer_init.h"
#include "libft.h"

void load_sound(t_music *music)
{
	Mix_Chunk	*shotgun;

	shotgun = Mix_LoadWAV(SHOTGUN_SOUND);
	if (shotgun == NULL)
	{
		ft_putstr("Error load shotgun sound\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	music->shotgun = shotgun;
}
