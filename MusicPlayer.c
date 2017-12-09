#include "MusicPlayer.h"
#include "MusicPlayerInternal.h"
#include "defines.h"
#include <stdlib.h>

struct _SongList {
	Songs* start_songs;		// Start of list of songs
	Songs* current_song;	// The currently active song
	uint32_t size;
};


SongList* newSongList(char* song_list_file_name){
	SongList* new_song_list = (SongList*)malloc(sizeof(SongList));
	ASSERT_NULL(new_song_list == NULL);
	new_song_list->start_songs = newSongs(song_list_file_name);
	ASSERT_NULL(new_song_list->start_songs == NULL);
	
	new_song_list->current_song = new_song_list->start_songs;
	new_song_list->size = songsGetSize(new_song_list->start_songs);
	return new_song_list;
}

uint32_t playNextSong(SongList* lst){
	// Get next song
	lst->current_song = nextSong(lst->current_song);
	if (lst->current_song == NULL){
		return 0;
	}
	// Start playing song
	stopSong();
	playSong(lst->current_song);
	return 1;
}

uint32_t playPreviousSong(SongList* lst){
	// Get previous song
	lst->current_song = prevSong(lst->start_songs, lst->current_song);
	if (lst->current_song == NULL){
		return 0;
	}
	// Start playing song
	stopSong();
	playSong(lst->current_song);
	return 1;
}

void freeSongList(SongList* lst){
	freeSongs(lst->start_songs);
	free(lst);
}

uint32_t startPlaying(SongList* lst){
	// Stop song playing if there is, and play the first song
	stopSong();
	printf("AA\n");
	get_song_name(lst->current_song);
	return playSong(lst->current_song);
}
