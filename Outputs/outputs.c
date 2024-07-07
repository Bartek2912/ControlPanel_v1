#include "outputs.h"

void outputInit(void)
{
	OUT1_DDR |= OUT1;
	OUT2_DDR |= OUT2;
	OUT3_DDR |= OUT3;
	OUT4_DDR |= OUT4;
	OUT1_LO, OUT2_LO, OUT3_LO, OUT4_LO;

}

void outputChangeState(char out)
{
	if(out == 1) OUT1_REV;
		
	if(out == 2) OUT2_REV;
		
	if(out == 3) OUT3_REV;
		
	if(out == 4) OUT4_REV;	
	
}

