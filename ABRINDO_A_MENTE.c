#define print(x) (printf(#x))
#define JUNTA(x,y) (x##y)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))   // Array size macro
#define num(x) (sizeof (x) / sizeof (*x))   // This one gets number of ANY TYPE OF ARRAY

#include <stdio.h>

int main(){
	print(VITOR GUSMAO);
	printf("\n%d\n", JUNTA(1,3));
	
	int a = 4, b = 2;
	    if(a^b) // Instead of if(a!=b) save 1 character.
                if(a-b) // Instead of if(a!=b) also save 1 character.
	     puts("SAO DIFERENTES!");

	printf("%d is bigger",(a>b)?a:b);
	
	#define P printf(
	P"Hello World");
	
	printf("%d", r = 123);

	int c = -2;
	(c < 0 ? a : b) = 1;

// If c < 0 then a = 1
// If c > 0 then b = 1
}

// ------------------------- FINAL -----------------------------------------------


#  define GL(line) do {                      \
       line;                                 \
       assert(glGetError() == GL_NO_ERROR);  \
   } while(0)    // while(0) == Do it whenever processor isn't doing anything else
#else
#  define GL(line) line
#endif

GL(glClear(GL_COLORS_MASK));
GL(pos_loc = glGetAttribLocation(prog, "pos"));

// Use *a instead of a[0] for accessing the first element of an array.


// A func that expects a pointer to three int values.
void func(const int *arg);

// Instead of using a local variable.
int tmp[] = {10, 20, 30};
func(tmp);

// We can write.
func( (const int[]){10, 20, 30} )

// Can be useful with a helper macro.
#define VEC(...) ((const int[]){__VA_ARGS__})
func(VEC(10, 20, 30));

// (Also works with struct or any other type).

 -----------------------------------------------------------------------------------
// Let say we have this struct
struct obj {
    const char *name;
    float pos[2];
    float color[4];
};

// We can write a macro like this one
#define OBJ(_name, ...)             \
    (struct obj) {                  \
        .name = _name,              \
        .color = {1, 1, 1, 1},      \
        __VA_ARGS__                 \
    };

// Now we can use the macro to create new objects.
// This one with color defaulted to {1, 1, 1, 1}.
struct obj o1 = OBJ("o1", .pos = {0, 10});
// This one with pos defaulted to {0, 0}.
struct obj o2 = OBJ("o2", .color = {1, 0, 0, 1});


// Instead of:

int iter(int state) {
    switch (state) {
    case 0:
        printf("step 0\n");
        return 1;
    case 1:
        printf("step 1\n");
        return 2;
    case 2:
        printf("step 2\n");
        return 3;
    case 3:
        return -1;
    }
}

// We can define:
#define START switch(state) { case 0:
#define END return -1; }
#define YIELD return __LINE__; case __LINE__:;

// And now the function can be written
int iter(int state) {
    START
    printf("step 0\n");
    YIELD
    printf("step 1\n");
    YIELD
    printf("step 2\n");
    END
}

// --------------- SMART RNG ------------------------------

#include <time.h>

// At the beginning of main, or at least before you use rand()
srand(time(NULL));


------------------- Adding Two numbers without using + operator -----------
	int Add(int x, int y)
{
	if (y == 0)
		return x;
	else
		return Add( x ^ y, (x & y) << 1);
}
//        Isso acima pode ser usado em Ofuscação


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
