#include "libft.h"
#include "mixer_init.h"

void	load_music(t_music *music)
{
	Mix_Music	*background;

	background = Mix_LoadMUS(BACKGROUND_MUSIC);
	if (background == NULL)
	{
		ft_putstr("Error load background music\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	music->background = background;
}
