
#define ASSERT_NULL(arg)	if((arg))\
							return NULL;

#define ASSERT_MINUS_ONE(arg)	if((arg))\
								return -1;


#define BEFORE_GET_CHAR	\
		static struct termios oldt, newt;\
		tcgetattr( STDIN_FILENO, &oldt);\
		newt = oldt;\
		newt.c_lflag &= ~(ICANON);\
		tcsetattr( STDIN_FILENO, TCSANOW, &newt);
		
#define AFTER_GET_CHAR \
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);



#define MAX_SONG_SIZE 100
#define SUCCSESS 1
