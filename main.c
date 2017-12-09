#include "MusicPlayer.h"
#include "defines.h"
#include <stdio.h>
#include <termios.h>	//termios, TCSANOW, ECHO, ICANON
#include <unistd.h>		//STDIN_FILENO

int main(){
	SongList* lst = newSongList("/home/omri/Music/musicList");
	char c = 0;
	uint32_t status = 0;
	startPlaying(lst);
	printf("1\n");
	// Macro to cancel waiting for enter key on getchar
	BEFORE_GET_CHAR;
	
	while((c = getchar()) != 'q'){
		switch(c){
		
		case 'n':
			status = playNextSong(lst);
			break;
		case 'p':
			status = playPreviousSong(lst);
			break;
		default:
			printf("n - next\np - previous\nq - quit\n");
		
		}
	}
	// Return settings to normal
	AFTER_GET_CHAR;
	
	stopSong();
	return 0;
}
