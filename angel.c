#include <iostream>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#if 0
int main(int argc, char** argv) {
	
	int div = 0;
	float input_angel = 0;
	float real_angel = -52.35;
	float run_angel = 0;
	
	
	run_angel = fabs(input_angel - real_angel);
	
	div = (int)(((run_angel*100)/2)+0.5);

	
	printf("div[%d]",div);
	

	return 0;
}
#endif
