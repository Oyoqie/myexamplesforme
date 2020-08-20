#ifdef WIN64 || _WIN32
	#include <windows.h>
#endif

#include <stdio.h>
#include <chrono>
#include <omp.h>

#define S 0x004fffff

typedef unsigned int UINT;

int main() {
	UINT result = 0;
	UINT h = 32 / omp_get_max_threads();

	#pragma omp parallel num_threads(omp_get_max_threads())
	{
		for (UINT j = 0; j < S; ++j) {
			UINT t = omp_get_thread_num();
			//#pragma omp atomic
			result ^= (0x1 << (j % h)) << t * h;
		}
	}

    switch (result) {
    	case 0x55555555:
    		printf("0x55555555 fine.\n");
    		break;
    	case 0xffffffff:
    		printf("0xffffffff fine.\n");
    		break;
    	case 0xaaaaaaaa:
    		printf("0xaaaaaaaa fine.\n");
    		break;
    	case 0:
    		printf("0x0 fine.\n");
    		break;
    	default:
    		printf("Got Race condition %x\n", result);
    		break;
    }

	return 0;
}
