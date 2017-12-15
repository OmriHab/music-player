#include "MusicPlayer.h"
#include "defines.h"
#include <stdio.h>
#include <unistd.h>		//STDIN_FILENO
#include <signal.h>
#include <time.h>


int main(){
	
	// Signal handler for ctrl^c to stop the music
	signal(SIGINT, stopSongAndQuit);
	
	SongList* lst = newSongList("/home/omri/Music/musicList");
	ASSERT_MINUS(lst != NULL);
	char c = 0;
	uint32_t status = 0;
	startPlaying(lst);
	// Macro to cancel waiting for enter key on getchar
	BEFORE_GET_CHAR;
	
	while((c = getchar()) != 'q'){
		printf("\b \b");	// Erase last character
		switch(c){
		case 'n':
			status = playNextSong(lst);
			break;
		case 'p':
			status = playPreviousSong(lst);
			break;
		default:
			printf("\n---------\nn - next\np - previous\nq - quit\n---------\n");
			break;
		
		}
		// If end of song list or error quit while loop
		if (status == 0) {
			break;
		}
	}
	putchar('\n');
	// Return settings to normal
	AFTER_GET_CHAR;
	
	stopSong();
	return 0;
}
