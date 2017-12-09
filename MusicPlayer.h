#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "MusicPlayerInternal.h"


typedef struct _SongList SongList;
typedef char* SongName;



/**
* Gets file path to a file listing song paths
* File synthax: Each song on a new line containing nothing but its path
* Return value: a song list or NULL in case of failure
*/
SongList* newSongList(char* song_list_file_name);

/**
* Gets song list and plays next song
* Return value: 1 for found and played, 0 for end of song list or error
*/
uint32_t playNextSong(SongList* lst);

/**
* Gets song list and plays previous song
* Return value: 1 for found and played, 0 for start of song list or error
*/
uint32_t playPreviousSong(SongList* lst);

/**
* Gets song list and shuffles order
* Return value: 1 for success, 0 for error
*/
uint32_t shuffle(SongList* lst);

/**
* Goes to random song without changing song order
* Return value: 1 for success, 0 for error
*/
uint32_t getRandom(SongList* lst);

/**
* Gets song list and song name and return if song was found in list
*/
uint32_t isSongInList(SongList* lst, SongName song);

/**
* Gets song list and orders it by alphabetical order
* Return value: 1 for success, 0 for error
*/
uint32_t orderSongListByABC(SongList* lst);

/**
* Gets song list and frees it and all its values
*/
void freeSongList(SongList* lst);

/**
* Gets song list and starts Playing
*/
uint32_t startPlaying(SongList* lst);

#endif //! MUSIC_PLAYER_H






















