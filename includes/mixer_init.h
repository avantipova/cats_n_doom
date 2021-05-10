/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylak <baylak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:53:04 by mjoss             #+#    #+#             */
/*   Updated: 2021/05/07 05:00:09 by baylak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIXER_INIT_H
# define MIXER_INIT_H

# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "assets_folder_name.h"

# define CHUNK_SIZE 4096
# define CHANNELS 1
# define BACKGROUND_MUSIC ASSETS_FOLDER_NAME "/sounds/E2M3_intermission.mp3"
# define SHOTGUN_SOUND ASSETS_FOLDER_NAME "/sounds/shotgun.wav"
# define NARUTO_SOUND ASSETS_FOLDER_NAME "/sounds/naruto.wav"
# define ANIME_TYAN ASSETS_FOLDER_NAME "/sounds/anime_tyan.wav"
# define PLAY_FOREVER -1

typedef struct s_music
{
	Mix_Music	*background;
	Mix_Chunk	*shotgun;
	Mix_Chunk	*naruto;
	Mix_Chunk	*anime_tyan;
	int			playing_naruto;
	int			playing_tyan;
}				t_music;

void			mixer_init(void);
t_music			*sound_init(void);
void			load_music(t_music *music);
void			play_music(Mix_Music *music, int loops);
void			music_close(t_music *music);
void			load_sound(t_music *music);

#endif
