#ifndef MUSIC_PLAYER_INTERNAL_H
#define MUSIC_PLAYER_INTERNAL_H

#include <stdio.h>
#include <stdint.h>
#include "MusicPlayer.h"

typedef struct _Songs Songs;
typedef char* SongName;

/**
* Gets file name to a file containing all wanted songs on a line alone
* Allocates memory and returns a songs list with all songs in the file in the list or --- NULL --- in case of failure
*/
Songs* newSongs(char* song_list_file_name);

/**
* Allocates memory and returns a songs node
*/
Songs* newSongsNode(SongName _song_name, Songs* next);

/***
* Gets song list file and reads song written on each row by its own and returns it through songName
* Return value: 1 for succsess -1 for end of file or failure
*/
int32_t getNextSongFromFile(FILE* songList, char* songName);

/**
* Gets Songs list and returns size of list
*/
uint32_t songsGetSize(Songs* songs);

/**
* Gets Songs and frees it and all its data
*/
void freeSongs(Songs* songs);

/**
* Gets song name and plays song
* Return value: 1 for found and played, 0 for not found
*/
uint32_t playSong(Songs* song);

/**
* Stops song playing weather there is a song playing or not
*/
void stopSong();

/**
* Stops song playing weather there is a song playing or not and quit program
*/
void stopSongAndQuit();

/**
* Returns next song in the list or NULL if song is the last song
*/
Songs* nextSong(Songs* song);

/**
* first_song - first song in the playlist
* current_song - the song you wish to get the previous of
* Return value: previous song in the list or NULL the song is the first song or any other error
*/
Songs* prevSong(Songs* first_song, Songs* current_song);

/**
* Returns song name
*/
char* get_song_name(Songs* song);

/**
* Prints song list
*/
void print_songs_list(Songs* lst);

#endif //! MUSIC_PLAYER_INTERNAL_H













