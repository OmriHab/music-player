#include "MusicPlayerInternal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "defines.h"


// Linked list of name of songs
struct _Songs {
	SongName song_name;
	struct _Songs *next;
};

// Use for prevSong
time_t song_beggining_time				= 0;
time_t time_passed_since_song_started 	= 0;

Songs* newSongs(char* song_list_file_name) {
	/*--Vars--*/
	FILE*  songList					= NULL;
	Songs* songs					= NULL;
	Songs* head						= NULL;
	char   next_song[MAX_SONG_SIZE]	= { 0 };
	uint32_t songNameLength			= 0;

	/*--Vars initialization--*/
	ASSERT_NULL(song_list_file_name != NULL);
	songList = fopen(song_list_file_name, "r");
	ASSERT_NULL(songList != NULL);
	
	// Make a first temporary node to append to
	songs = newSongsNode(NULL, NULL);
	if (songs == NULL) {
		fclose(songList);
		return NULL;
	}
	head = songs;
	
	/*--Code--*/
	// Append songs from file to songs
	while((getNextSongFromFile(songList, next_song)) != -1) {
		// Append song to song list and go to it
		songs->next = newSongsNode(next_song, NULL);
		ASSERT_NULL(songs->next != NULL);
		songs = songs->next;
		songs->next = NULL;
	}
	ASSERT_NULL(fclose(songList) == 0);
	// Free first temporary node and return second node
	songs = head->next;
	free(head);
	return songs;
}

uint32_t playSong(Songs* song) {
	char songCommand[MAX_MPV_COMMAND_SIZE] = {0};
	// Runs mpv in the background with no-termianal option to keep output and input hidden to the end user
	snprintf(songCommand, MAX_MPV_COMMAND_SIZE, "mpv --no-terminal \"%s\" &", song->song_name);
	system(songCommand);
	// Set song beggining time
	song_beggining_time = time(NULL);
	// Delete current line and print song name
	printf("\33[2K\r");
	printf("%s", song->song_name);
}

void stopSong() {
	// Kills mpv whether there is music playing or not
	// Use this before playing a new song, otherwise the last song will keep playing
	system("killall --quiet mpv");
}

Songs* newSongsNode(SongName _song_name, Songs* next) {
	Songs* songNode			= NULL;
	uint32_t songNameLength	= 0;
	
	songNode = (Songs*)malloc(1 * sizeof(Songs));
	ASSERT_NULL(songNode != NULL);
	
	if(_song_name == NULL)	{
		songNode->song_name = NULL;
	}
	
	// Copy song name
	else {
		songNameLength = strnlen(_song_name, MAX_SONG_SIZE);
		songNode->song_name = (SongName)malloc((songNameLength + 1) * sizeof(char));
		if(songNode->song_name == NULL) {
			free(songNode);
			return NULL;
		}
		strncpy(songNode->song_name, _song_name, songNameLength);
	}
	
	songNode->next = next;
	return songNode;
}

int32_t getNextSongFromFile(FILE* songList, char* songName) {
	char c 					= 0;
	uint32_t songNameLength	= 0;

	ASSERT_MINUS(songList != NULL);
	ASSERT_MINUS(songName != NULL);
	
	// Check for EOF before reading
	if (feof(songList)) {
		return EOF;
	}
	
	// Peak at the next char
	c = getc(songList);
	ungetc(c, songList);
	// Ignore leading white-space characters
	while (c == '\n' || c == ' ' || c == '\t') {
		c = getc(songList);
		if (c == EOF) {
			return EOF;
		}
	}
	
	// Get line with song name written on it
	fgets(songName, MAX_SONG_SIZE, songList);
	
	// If last letter \n, remove it
	songNameLength = strnlen(songName, MAX_SONG_SIZE);
	if (songNameLength > 0 && songName[songNameLength - 1] == '\n') {
		songName[songNameLength - 1] = '\0';
	}
	
	
	return SUCCESS;	// Success
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

uint32_t songsGetSize(Songs* songs) {
	if (songs == NULL){
		return 0;
	}
	return 1 + songsGetSize(songs->next);
}

Songs* nextSong(Songs* song) {
	return song->next;
}

Songs* prevSong(Songs* first_song, Songs* current_song) {
	
	ASSERT_NULL(first_song != NULL);
	ASSERT_NULL(current_song != NULL);
	
	// If less than 1.5 second passed, return current song to start, or on the first song
	time_passed_since_song_started = time(NULL) - song_beggining_time;
	if (time_passed_since_song_started > 1.5 || first_song == current_song){
		return current_song;
	}
	
	// Continue with the list until the first song is one before the current song or reached the end
	while((first_song->next != current_song) && (first_song != NULL)) {
		first_song = first_song->next;
	}
	
	// If first song reached the end, returns NULL
	return first_song;
}

char* get_song_name(Songs* song) {
	return song->song_name;
}

void print_songs_list(Songs* lst) {
	static int cnt = 1;
	if (lst == NULL){
		printf("End\n");
		cnt = 1;
		return;
	}
	
	printf("%d --> %s\n", cnt++, lst->song_name);
	print_songs_list(lst->next);
	
}

void stopSongAndQuit(){
	stopSong();
	exit(1);
}


