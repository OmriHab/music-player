mp: MusicPlayer.o MusicPlayerInternal.o main.o
	gcc -o mp MusicPlayer.o MusicPlayerInternal.o main.o
MusicPlayer.o: MusicPlayer.c MusicPlayer.h
	gcc -c MusicPlayer.c
MusicPlayerInternal.o: MusicPlayerInternal.c MusicPlayerInternal.h
	gcc -c -lvlc MusicPlayerInternal.c
main.o: main.c
	gcc -c main.c
clean:
	rm MusicPlayerInternal.o MusicPlayer.o main.o
