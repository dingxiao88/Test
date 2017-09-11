#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int stoper() 
{
	
	int ship_num = 999;
	int bomb_num = 4;
	
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	
	unsigned char MK3_HandleControl_Stop[12]; //0:无动作  1:进  2:出
	unsigned int Stoper_Data;
	int i;
	
	
//	temp1 = ((ship_num&0xff00)>>8); 
//	temp2 = (ship_num|bomb_num);

//	temp1 = ((ship_num<<4)&0xff00); 
//	temp2 = (((ship_num<<4)&0xff00)|bomb_num);


//	temp1 = ((ship_num&0x0fff)>>4); 
//	temp2 = (((ship_num&0x000f)<<4)|bomb_num);

//	printf("b1[%x]-b2[%x]",temp1,temp2);
	
	
	Stoper_Data = 0x0003;
	MK3_HandleControl_Stop[0] = 0;
	MK3_HandleControl_Stop[1] = 0;
	MK3_HandleControl_Stop[2] = 0;
	MK3_HandleControl_Stop[3] = 0;
	MK3_HandleControl_Stop[4] = 0;
	MK3_HandleControl_Stop[5] = 0;
	MK3_HandleControl_Stop[6] = 0;
	MK3_HandleControl_Stop[7] = 0;
	MK3_HandleControl_Stop[8] = 0;
	MK3_HandleControl_Stop[9] = 0;
	MK3_HandleControl_Stop[10] = 0;
	MK3_HandleControl_Stop[11] = 0;
	
    for(i=0;i<12;i++)
	{
		//@
		if(MK3_HandleControl_Stop[i]==1)
		{
			Stoper_Data = ((Stoper_Data|0x0000)|(1<<(i)));
		}
		else if((MK3_HandleControl_Stop[i]==2))
		{
			Stoper_Data = ((Stoper_Data&0xffff)&(0<<(i)));
		}
	}
	
	//Stoper_Data = (0xffff&(0xfffe<<1)); 
	
	Stoper_Data = (Stoper_Data&((0xfffe<<(1))|(0xf7ff>>(11-(1)))));
	
	
	printf("Stoper_Data[%x]",Stoper_Data);
	

	return 0;
}
