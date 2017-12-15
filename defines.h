#include <termios.h>	//termios, TCSANOW, ECHO, ICANON - Used for BEFORE_GET_CHAR and AFTER_GET_CHAR


#define ASSERT_NULL(arg) 				\
	if(!(arg)){							\
		INFO(arg);						\
		return NULL;					\
	}


#define ASSERT_MINUS(arg)	if(!(arg))	\
	if(!(arg)){							\
		INFO(arg);						\
		return -1;						\
	}

#define INFO(arg) \
		fflush(stdout); \
		fprintf(stderr, "arg(%s) failed\nLINE:%d, function: %s\nFile: %s\n\n", TO_STRING(arg), __LINE__, __func__, __FILE__);


#define TO_STRING(arg) #arg

#define BEFORE_GET_CHAR	\
		static struct termios oldt, newt;\
		tcgetattr( STDIN_FILENO, &oldt);\
		newt = oldt;\
		newt.c_lflag &= ~(ICANON);\
		tcsetattr( STDIN_FILENO, TCSANOW, &newt);
		
#define AFTER_GET_CHAR \
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

#define TEST(n) \
		fflush(stdout); \
		printf("Test %d\n", n);


#define MAX_SONG_SIZE 100
#define SUCCESS 1
#define MAX_MPV_COMMAND_SIZE (20 + (MAX_SONG_SIZE))
