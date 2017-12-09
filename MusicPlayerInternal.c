#include "MusicPlayerInternal.h"
#include <string.h>
#include <stdlib.h>
#include "defines.h"


// Linked list of name of songs
struct _Songs {
	SongName song_name;
	struct _Songs *next;
};

Songs* newSongs(char* song_list_file_name) {
	/*--Vars--*/
	FILE* songList = fopen(song_list_file_name, "r");
	ASSERT_NULL(songList == NULL);
	Songs* songs = newSongsNode(NULL, NULL);
	Songs* head = songs;
	char next_song[MAX_SONG_SIZE] = {0};
	
	/*--Code--*/
	// Append songs from file to songs
	while((getNextSong(songList, next_song)) != -1){
		songs->next = (Songs*)malloc(sizeof(Songs));
		songs = songs->next;
		songs->song_name = next_song;
		songs->next = NULL;
	}
	fclose(songList);
	songs = head->next;
	free(head);
	return songs;
}

uint32_t playSong(Songs* song) {
	char songCommand[120] = {0};
	// Runs mpv in the background with no-termianal option to keep output and input hidden to the end user
	snprintf(songCommand, 120, "mpv --no-terminal %s &", song->song_name);
	system(songCommand);
}

void stopSong() {
	// Kills mpv weather there is music playing or not
	// Use this before playing a new song, otherwise the last song will keep playing
	system("killall --quiet mpv");
}

Songs* newSongsNode(SongName _song_name, Songs* next){
	Songs* songNode = (Songs*)malloc(1 * sizeof(Songs));
	ASSERT_NULL(songNode == NULL);
	if(_song_name == NULL)	{
		songNode->song_name = NULL;
	}
	else {	
	songNode->song_name = (SongName)malloc((strnlen(_song_name, MAX_SONG_SIZE) + 1) * sizeof(char));
	if(songNode->song_name == NULL){
		free(songNode);
		return NULL;
	}
	strncpy(songNode->song_name, _song_name, MAX_SONG_SIZE);
	}
	songNode->next = next;
	return songNode;
}

int32_t getNextSong(FILE* songList, char* songName) {
	char c = 0;
	// Check for EOF and empty songName
	ASSERT_MINUS_ONE(feof(songList));
	ASSERT_MINUS_ONE(songName == NULL);
	// Peak at the next char
	c = getc(songList);
	ungetc(c, songList);
	// Ignore leading white-space characters
	while (c == '\n' || c == ' ' || c == '\t') {
		c = getc(songList);
	}
	// Check again for EOF
	ASSERT_MINUS_ONE(feof(songList));
	
	// Get line with song name written on it
	fgets(songName, MAX_SONG_SIZE, songList);
	
	return SUCCSESS;	// Succsess
}

void freeSongs(Songs* songs) {
	if (songs == NULL) {
		return;
	}
	free(songs->song_name);
	Songs* tmp = songs->next;
	free(songs);
	freeSongs(tmp);
}

uint32_t songsGetSize(Songs* songs){
	if (songs == NULL){
		return 0;
	}
	return 1 + songsGetSize(songs->next);
}

Songs* nextSong(Songs* song) {
	return song->next;
}

Songs* prevSong(Songs* first_song, Songs* current_song){
	ASSERT_NULL(first_song == NULL);
	ASSERT_NULL(current_song == NULL);
	ASSERT_NULL(first_song == current_song);
	if (first_song->next == current_song){
		return first_song;
	}
	return prevSong(first_song->next, current_song);
}

char* get_song_name(Songs* song){
	printf("%s", song->song_name);
}






