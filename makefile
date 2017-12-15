mp: MusicPlayer.o MusicPlayerInternal.o main.o
	gcc -o mp MusicPlayer.o MusicPlayerInternal.o main.o
MusicPlayer.o: MusicPlayer.c MusicPlayer.h defines.h
	gcc -c MusicPlayer.c
MusicPlayerInternal.o: MusicPlayerInternal.c MusicPlayerInternal.h defines.h
	gcc -c MusicPlayerInternal.c
main.o: main.c defines.h
	gcc -c main.c
clean:
	rm MusicPlayerInternal.o MusicPlayer.o main.o
