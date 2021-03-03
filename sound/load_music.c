#include "libft.h"
#include "mixer_init.h"

Mix_Music *load_music(void)
{
	Mix_Music	*background;

	background = Mix_LoadMUS(BACKGROUND_SOUND);
	if (background == NULL)
	{
		ft_putstr("Error load background music\n");
		ft_putstr(Mix_GetError());
		exit(EXIT_FAILURE);
	}
	return (background);
}
