#include "mixer_init.h"
#include "libft.h"
#include <stdlib.h>

t_music	*sound_init(void)
{
	t_music	*music;

	if ((music = (t_music*)malloc(sizeof(t_music))) == NULL)
	{
		ft_putstr("malloc returns NULL\n");
		exit(EXIT_FAILURE);
	}
	mixer_init();
	load_sound(music);
	load_music(music);
	return (music);
}
