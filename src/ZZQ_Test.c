#include <iostream>
#include <math.h>

	unsigned int DSP_Cmd_ZZQ_Status = 0x0000;
	unsigned int DSP_Cmd_ZZQ_Status_Old = 0x0000;
	
	int AnZzqCh = 0;
	int AnZzqCh2 = 0;
	
	int ZZQ_Last_Pro_Num = 0;
	
	int ZZQ_X_Last_Pro_Dir[13];
	
	int DSP_Cmd_ZZQ_CH1_CMD_Reset = 0;
	int DSP_Cmd_ZZQ_CH2_CMD_Reset = 0;
	
	int ZZQ_CH1_Last_Pro_Dir = 3;
	int ZZQ_CH2_Last_Pro_Dir = 3;

int main(int argc, char** argv)
{	
	int ZZQ_Rdy_Run_Ch1 = 0;	/*@-制止器操作通道1*/
	int ZZQ_Rdy_Run_Ch2 = 0;	/*@-制止器操作通道2*/
	int ZZQ_Run_Dir_Ch1 = 3;	/*@-制止器操作通道1动作方向0:Left  1:Close*/
	int ZZQ_Run_Dir_Ch2 = 3;	/*@-制止器操作通道2动作方向0:Left  1:Close*/
	int ZZQ_DSP_Net_Pro = 0;	/*@DX-制止同时操作数量*/
	
	int temp_CH = 0;
	int temp_dir = 0;
	
	int n;
	int temp1 = 0;
	int temp2 = 0;
	
	unsigned char ZZQ_DSP_Net_ProMax = 2;
	
	for(n=0;n<12;n++)
	ZZQ_X_Last_Pro_Dir[n] = 3;

	while(1)
	{
		ZZQ_Rdy_Run_Ch1 = 0;
		ZZQ_Rdy_Run_Ch2 = 0;
		ZZQ_Run_Dir_Ch1 = 3;
		ZZQ_Run_Dir_Ch2 = 3;
		ZZQ_DSP_Net_Pro = 0;
		
		temp_CH = 0;
		temp_dir = 0;
		
//		printf("sizeof:%d\n",sizeof(DSP_Cmd_ZZQ_Status)); 
//		printf("zzq[%0x]-zzq_old[%0x]\n",DSP_Cmd_ZZQ_Status,DSP_Cmd_ZZQ_Status);
		printf("---------------------------------------------\n"); 
		printf("please input zzq_cmd whith hex!\n");
		
		scanf("%x",&DSP_Cmd_ZZQ_Status);
		
		/*@-制止器命令有更新*/
		if(DSP_Cmd_ZZQ_Status_Old != DSP_Cmd_ZZQ_Status)
		{
			/*@-分解ZZQ需要动作管号(最多同时2个)*/
			for(n=0; n<12; n++)
			{
				/*@-获取新旧2条制止器控制命令*/
				temp1 = (((DSP_Cmd_ZZQ_Status))&(0x01<<n));
				temp2 = (((DSP_Cmd_ZZQ_Status_Old))&(0x01<<n));
				
				//printf("temp1[%d]-temp2[%d]\n",temp1,temp2);
	
				/*@DX-该管制止器命令有更新*/
				if(temp1 != temp2)
				{
					/*@-同时操作数量小于MAX*/
					if(ZZQ_DSP_Net_Pro < ZZQ_DSP_Net_ProMax)
					{
						/*@-同时操作数量自增*/
						ZZQ_DSP_Net_Pro = ZZQ_DSP_Net_Pro + 1;
	
						/*@-制止器通道1*/
						if(ZZQ_DSP_Net_Pro == 1)
						{
							/*@-制止器通道1操作管号*/
							ZZQ_Rdy_Run_Ch1 = n + 1;
	
							/*@-制止器通道1动作方向*/
							if(temp1 != 0)
							{
								ZZQ_Run_Dir_Ch1 = 0;
							}
							if(temp1 == 0)
							{
								ZZQ_Run_Dir_Ch1 = 1;
							}
						}
	
						/*@-制止器通道2*/
						else if(ZZQ_DSP_Net_Pro == 2)
						{
							/*@-制止器通道2操作管号*/
							ZZQ_Rdy_Run_Ch2 = n + 1;
	
							/*@-制止器通道2动作方向*/
							if(temp1 != 0)
							{
								ZZQ_Run_Dir_Ch2 = 0;
							}
							if(temp1 == 0)
							{
								ZZQ_Run_Dir_Ch2 = 1;
							}
						}
					}
					/*@-同时操作数量大于于MAX*/
					else
					{
						/*@DX-故障ID*/
					    printf("pro outof max!\n");
						/*@-需要操作的管号*/
						ZZQ_Rdy_Run_Ch1 = 0;
						ZZQ_Rdy_Run_Ch2 = 0;
						ZZQ_Run_Dir_Ch1 = 3;
						ZZQ_Run_Dir_Ch2 = 3;
					}
				}
	
			}
			
		
		
		printf("Last_Pro:%d\n",ZZQ_Last_Pro_Num);	
		printf("Rdy_Run_Ch1[%d]--Rdy_Run_Ch2[%d]--ZZQ_Pro:%d\n",ZZQ_Rdy_Run_Ch1,ZZQ_Rdy_Run_Ch2,ZZQ_DSP_Net_Pro);
		
		#if 0	
		/*@-初始或超出Pro Max*/
		if(ZZQ_Last_Pro_Num  == 0)
		{
			/*@-本次只更新1个ZZQ动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-初始态ZZQ没有动作过*/
				if((AnZzqCh == 0)&&(AnZzqCh2 == 0))
				{
					printf("Pro_0\n");
					/*@-CH2操作复制CH1*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1清零*/
					ZZQ_Rdy_Run_Ch1 = 0;
					ZZQ_Run_Dir_Ch1 = 3;
				}
			}
			/*@-本次更新2个ZZQ动作不需要干预*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				printf("Pro_1\n");
			}
		}
		/*@-上一次操作1个ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 1)
		{
			/*@-本次只更新1个ZZQ动作,全由CH2动作,CH1保持老动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				if(((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2)) && (AnZzqCh != 0))  
				{
					printf("Pro_3\n");
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH2与更新ZZQ号不一致,由CH1通道执行*/
				else if(ZZQ_Rdy_Run_Ch1 != AnZzqCh2)
				{
					printf("Pro_4\n");
					/*@-CH2保持老动作*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
				}
				/*@-CH2与更新ZZQ号一致,继续由CH2通道执行*/
			    else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
			    {
			    	printf("Pro_5\n");
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
			    }

			}
			/*@-本次只更新2个ZZQ动作*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
			    /*@-更新2通道都与目前动作ZZQ号不一致,等待前面动作执行完毕,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock1\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock2\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock3\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock4\n");
				}

			}
		}
		/*@-上一次操作2个ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 2)
		{
			/*@-本次只更新1个ZZQ动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-CH1与更新ZZQ号一致,继续由CH1通道执行*/
			    if(ZZQ_Rdy_Run_Ch1 == AnZzqCh)
			    {
			    
			    }
				/*@-CH2与更新ZZQ号一致,由CH2通道执行*/
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH1和CH2与更新ZZQ号都不一致,Lock*/
				else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2))
				{
					printf("Lock5\n");
				}
			}
			/*@-本次只更新2个ZZQ动作*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				/*@-CH1和CH2与更新ZZQ号都不一致,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock6\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock7\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock8\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock9\n");
				}
				/*@-CH1和CH2与更新ZZQ号都一致,更新*/
				else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh) && (ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
				{

				}				

			}
		}
		#endif
		
		
		/*@-初始或超出Pro Max*/
		if(ZZQ_Last_Pro_Num  == 0)
		{
			/*@-本次只更新1个ZZQ动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-初始态ZZQ没有动作过*/
				if((AnZzqCh == 0)&&(AnZzqCh2 == 0))
				{
					printf("Pro_0\n");
					/*@-CH2操作复制CH1*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1清零*/
					ZZQ_Rdy_Run_Ch1 = 0;
					ZZQ_Run_Dir_Ch1 = 3;
				}
			}
			/*@-本次更新2个ZZQ动作不需要干预*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				printf("Pro_1\n");
			}
		}
		/*@-上一次操作1个ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 1)
		{
			/*@-本次只更新1个ZZQ动作,全由CH2动作,CH1保持老动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				//当前操作的管号比CH2大 
				if(ZZQ_Rdy_Run_Ch1>AnZzqCh2)
				{
					printf("Pro_3\n");
					
					temp_CH =  AnZzqCh2;
					temp_dir = ZZQ_X_Last_Pro_Dir[AnZzqCh2];
					
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;
					
					/*@-CH1承担原CH2 ZZQ的动作*/
					ZZQ_Rdy_Run_Ch1 = temp_CH;
					ZZQ_Run_Dir_Ch1 = temp_dir;
				}
				//当前操作的管号比CH2小 
				else if(ZZQ_Rdy_Run_Ch1<AnZzqCh2)
				{
					printf("Pro_4\n");
					
					/*@-CH1承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch1 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch1 = ZZQ_Run_Dir_Ch1;
					
					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
					
				}
				//当前操作的管号等于CH2
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					printf("Pro_5\n");
					
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				
				
				#if 0
				if(((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2)) && (AnZzqCh != 0))  
				{
					printf("Pro_3\n");
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH2与更新ZZQ号不一致,由CH1通道执行*/
				else if(ZZQ_Rdy_Run_Ch1 != AnZzqCh2)
				{
					printf("Pro_4\n");
					/*@-CH2保持老动作*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
				}
				/*@-CH2与更新ZZQ号一致,继续由CH2通道执行*/
			    else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
			    {
			    	printf("Pro_5\n");
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
			    }
			    #endif

			}
			/*@-本次只更新2个ZZQ动作*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
			    /*@-更新2通道都与目前动作ZZQ号不一致,等待前面动作执行完毕,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock1\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock2\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock3\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock4\n");
				}

			}
		}
		/*@-上一次操作2个ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 2)
		{
			/*@-本次只更新1个ZZQ动作*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-CH1与更新ZZQ号一致,继续由CH1通道执行*/
			    if(ZZQ_Rdy_Run_Ch1 == AnZzqCh)
			    {
			    
			    }
				/*@-CH2与更新ZZQ号一致,由CH2通道执行*/
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					/*@-CH2承担更新1个ZZQ的动作*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1保持老动作*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH1和CH2与更新ZZQ号都不一致,Lock*/
				else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2))
				{
					printf("Lock5\n");
				}
			}
			/*@-本次只更新2个ZZQ动作*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				/*@-CH1和CH2与更新ZZQ号都不一致,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock6\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock7\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock8\n");
				}
				/*@-更新2通道,其中有一个与目前动作的ZZQ号一致,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock9\n");
				}
				/*@-CH1和CH2与更新ZZQ号都一致,更新*/
				else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh) && (ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
				{

				}				

			}
		}
			
			
		/*@-ZZQ操作通道1管号*/
		if(ZZQ_Rdy_Run_Ch1 != 0)
		{
			AnZzqCh = ZZQ_Rdy_Run_Ch1;

			/*@-通道1制止器动作方向*/
			if(ZZQ_Run_Dir_Ch1 == 0)
			{
				printf("CH1 Set 0!\n"); 
			}
			else if(ZZQ_Run_Dir_Ch1 == 1)
			{
				printf("CH1 Set 1!\n"); 
			}

			/*@-通道1本次控制方向*/
			ZZQ_CH1_Last_Pro_Dir = ZZQ_Run_Dir_Ch1;
            /*@-本次ZZQ X的控制方向*/
			ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1] = ZZQ_Run_Dir_Ch1;

			/*@-通道1需要Reset*/
			DSP_Cmd_ZZQ_CH1_CMD_Reset = 1;
		}
		else if(ZZQ_Rdy_Run_Ch1 == 0)
		{
		  printf("CH1 Reset!\n"); 							
		}
		
		/*@-ZZQ操作通道2管号*/
		if(ZZQ_Rdy_Run_Ch2 != 0)
		{
			AnZzqCh2 = ZZQ_Rdy_Run_Ch2;

			/*@-通道2制止器动作方向*/
			if(ZZQ_Run_Dir_Ch2 == 0)
			{
				printf("CH2 Set 0!\n"); 
			}
			else if(ZZQ_Run_Dir_Ch2 == 1)
			{
				printf("CH2 Set 1!\n"); 
			}

			/*@-通道2本次控制方向*/
			ZZQ_CH2_Last_Pro_Dir = ZZQ_Run_Dir_Ch2;

			 /*@-本次ZZQ X的控制方向*/
			ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2] = ZZQ_Run_Dir_Ch2;

			/*@-通道2需要Reset*/
			DSP_Cmd_ZZQ_CH2_CMD_Reset = 1;
		}
		else if(ZZQ_Rdy_Run_Ch2 == 0)
		{
			printf("CH2 Reset!\n"); 
		}

		/*@DX-保存ZZQ操作命令*/
		DSP_Cmd_ZZQ_Status_Old = DSP_Cmd_ZZQ_Status;


		/*@-本次ZZQ动作数量*/
		if(ZZQ_DSP_Net_Pro == 1)
		ZZQ_Last_Pro_Num = 1;
		else if(ZZQ_DSP_Net_Pro == 2)
		ZZQ_Last_Pro_Num = 2;
	
			
			
			
			
			
			
			
			
			
			

			printf("[ch1:%d]-[ch2:%d]\n",ZZQ_Rdy_Run_Ch1,ZZQ_Rdy_Run_Ch2);
	
			/*@DX-保存ZZQ操作命令*/
			DSP_Cmd_ZZQ_Status_Old = DSP_Cmd_ZZQ_Status;
			
			printf("[zzq1_dir:%x]-[zzq2_dir:%x]\n",ZZQ_Run_Dir_Ch1,ZZQ_Run_Dir_Ch2);
		}
	}

	
	return (1);
}





