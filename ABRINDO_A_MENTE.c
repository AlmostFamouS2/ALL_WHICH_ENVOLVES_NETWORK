#define print(x) (printf(#x))
#define JUNTA(x,y) (x##y)

#include <stdio.h>

int main(){
	print(VITOR GUSMAO);
	printf("\n%d\n", JUNTA(1,3));
}


#ifdef _WIN32
#include <Windows.h>
#elif defined __linux__
#include <unistd.h>
#include <sys/mman.h>
#endif

#ifdef __GNUC__
#define NOINLINE __attribute__((noinline))
#elif defined _MSC_VER
#define NOINLINE __declspec(noinline)
#endif
