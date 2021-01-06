#include "../sharedLibs/sharedFunctions.h"
#include "segmentFunction.h"
void setSegment(int check[]){
	for (int i=0;i<=5;i++)
	{
		if (check[i]==0)
		{
			CLEAR_BIT(PORTC,i);
			}else{
			SET_BIT(PORTC,i);
		}
	}
	if (check[6]==0)
	{
		CLEAR_BIT(PORTD,4);
		}else{
		SET_BIT(PORTD,4);
	}
	return;
}
void segment (int z){
	int zero[7]={1,1,1,1,1,1,0};
	int one[7]={0,0,1,1,0,0,0};
	int two[7]={1,1,0,1,1,0,1};
	int three[7]={0,1,1,1,1,0,1};
	int four[7]={0,0,1,1,0,1,1};
	int five[7]={0,1,1,0,1,1,1};
	int six[7]={1,1,1,0,1,1,1};
	int seven[7]={0,0,1,1,1,0,0};
	int aight[7]={1,1,1,1,1,1,1};
	int nine[7]={0,1,1,1,1,1,1};
	int err [7]={1,1,0,0,1,1,1};
	switch(z){
		case 0:
		setSegment(zero);
		break;
		case 1:
		setSegment(one);
		break;
		case 2:
		setSegment(two);
		break;
		case 3:
		setSegment(three);
		break;
		case 4:
		setSegment(four);
		break;
		case 5:
		setSegment(five);
		break;
		case 6:
		setSegment(six);
		break;
		case 7:
		setSegment(seven);
		break;
		case 8:
		setSegment(aight);
		break;
		case 9:
		setSegment(nine);
		break;
		default:
		setSegment(err);
		break;
	}
}