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
	int ZZQ_Rdy_Run_Ch1 = 0;	/*@-��ֹ������ͨ��1*/
	int ZZQ_Rdy_Run_Ch2 = 0;	/*@-��ֹ������ͨ��2*/
	int ZZQ_Run_Dir_Ch1 = 3;	/*@-��ֹ������ͨ��1��������0:Left  1:Close*/
	int ZZQ_Run_Dir_Ch2 = 3;	/*@-��ֹ������ͨ��2��������0:Left  1:Close*/
	int ZZQ_DSP_Net_Pro = 0;	/*@DX-��ֹͬʱ��������*/
	
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
		
		/*@-��ֹ�������и���*/
		if(DSP_Cmd_ZZQ_Status_Old != DSP_Cmd_ZZQ_Status)
		{
			/*@-�ֽ�ZZQ��Ҫ�����ܺ�(���ͬʱ2��)*/
			for(n=0; n<12; n++)
			{
				/*@-��ȡ�¾�2����ֹ����������*/
				temp1 = (((DSP_Cmd_ZZQ_Status))&(0x01<<n));
				temp2 = (((DSP_Cmd_ZZQ_Status_Old))&(0x01<<n));
				
				//printf("temp1[%d]-temp2[%d]\n",temp1,temp2);
	
				/*@DX-�ù���ֹ�������и���*/
				if(temp1 != temp2)
				{
					/*@-ͬʱ��������С��MAX*/
					if(ZZQ_DSP_Net_Pro < ZZQ_DSP_Net_ProMax)
					{
						/*@-ͬʱ������������*/
						ZZQ_DSP_Net_Pro = ZZQ_DSP_Net_Pro + 1;
	
						/*@-��ֹ��ͨ��1*/
						if(ZZQ_DSP_Net_Pro == 1)
						{
							/*@-��ֹ��ͨ��1�����ܺ�*/
							ZZQ_Rdy_Run_Ch1 = n + 1;
	
							/*@-��ֹ��ͨ��1��������*/
							if(temp1 != 0)
							{
								ZZQ_Run_Dir_Ch1 = 0;
							}
							if(temp1 == 0)
							{
								ZZQ_Run_Dir_Ch1 = 1;
							}
						}
	
						/*@-��ֹ��ͨ��2*/
						else if(ZZQ_DSP_Net_Pro == 2)
						{
							/*@-��ֹ��ͨ��2�����ܺ�*/
							ZZQ_Rdy_Run_Ch2 = n + 1;
	
							/*@-��ֹ��ͨ��2��������*/
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
					/*@-ͬʱ��������������MAX*/
					else
					{
						/*@DX-����ID*/
					    printf("pro outof max!\n");
						/*@-��Ҫ�����Ĺܺ�*/
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
		/*@-��ʼ�򳬳�Pro Max*/
		if(ZZQ_Last_Pro_Num  == 0)
		{
			/*@-����ֻ����1��ZZQ����*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-��ʼ̬ZZQû�ж�����*/
				if((AnZzqCh == 0)&&(AnZzqCh2 == 0))
				{
					printf("Pro_0\n");
					/*@-CH2��������CH1*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1����*/
					ZZQ_Rdy_Run_Ch1 = 0;
					ZZQ_Run_Dir_Ch1 = 3;
				}
			}
			/*@-���θ���2��ZZQ��������Ҫ��Ԥ*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				printf("Pro_1\n");
			}
		}
		/*@-��һ�β���1��ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 1)
		{
			/*@-����ֻ����1��ZZQ����,ȫ��CH2����,CH1�����϶���*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				if(((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2)) && (AnZzqCh != 0))  
				{
					printf("Pro_3\n");
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH2�����ZZQ�Ų�һ��,��CH1ͨ��ִ��*/
				else if(ZZQ_Rdy_Run_Ch1 != AnZzqCh2)
				{
					printf("Pro_4\n");
					/*@-CH2�����϶���*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
				}
				/*@-CH2�����ZZQ��һ��,������CH2ͨ��ִ��*/
			    else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
			    {
			    	printf("Pro_5\n");
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
			    }

			}
			/*@-����ֻ����2��ZZQ����*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
			    /*@-����2ͨ������Ŀǰ����ZZQ�Ų�һ��,�ȴ�ǰ�涯��ִ�����,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock1\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock2\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock3\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock4\n");
				}

			}
		}
		/*@-��һ�β���2��ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 2)
		{
			/*@-����ֻ����1��ZZQ����*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-CH1�����ZZQ��һ��,������CH1ͨ��ִ��*/
			    if(ZZQ_Rdy_Run_Ch1 == AnZzqCh)
			    {
			    
			    }
				/*@-CH2�����ZZQ��һ��,��CH2ͨ��ִ��*/
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH1��CH2�����ZZQ�Ŷ���һ��,Lock*/
				else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2))
				{
					printf("Lock5\n");
				}
			}
			/*@-����ֻ����2��ZZQ����*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				/*@-CH1��CH2�����ZZQ�Ŷ���һ��,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock6\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock7\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock8\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock9\n");
				}
				/*@-CH1��CH2�����ZZQ�Ŷ�һ��,����*/
				else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh) && (ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
				{

				}				

			}
		}
		#endif
		
		
		/*@-��ʼ�򳬳�Pro Max*/
		if(ZZQ_Last_Pro_Num  == 0)
		{
			/*@-����ֻ����1��ZZQ����*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-��ʼ̬ZZQû�ж�����*/
				if((AnZzqCh == 0)&&(AnZzqCh2 == 0))
				{
					printf("Pro_0\n");
					/*@-CH2��������CH1*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1����*/
					ZZQ_Rdy_Run_Ch1 = 0;
					ZZQ_Run_Dir_Ch1 = 3;
				}
			}
			/*@-���θ���2��ZZQ��������Ҫ��Ԥ*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				printf("Pro_1\n");
			}
		}
		/*@-��һ�β���1��ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 1)
		{
			/*@-����ֻ����1��ZZQ����,ȫ��CH2����,CH1�����϶���*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				//��ǰ�����Ĺܺű�CH2�� 
				if(ZZQ_Rdy_Run_Ch1>AnZzqCh2)
				{
					printf("Pro_3\n");
					
					temp_CH =  AnZzqCh2;
					temp_dir = ZZQ_X_Last_Pro_Dir[AnZzqCh2];
					
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;
					
					/*@-CH1�е�ԭCH2 ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch1 = temp_CH;
					ZZQ_Run_Dir_Ch1 = temp_dir;
				}
				//��ǰ�����Ĺܺű�CH2С 
				else if(ZZQ_Rdy_Run_Ch1<AnZzqCh2)
				{
					printf("Pro_4\n");
					
					/*@-CH1�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch1 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch1 = ZZQ_Run_Dir_Ch1;
					
					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
					
				}
				//��ǰ�����Ĺܺŵ���CH2
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					printf("Pro_5\n");
					
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				
				
				#if 0
				if(((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2)) && (AnZzqCh != 0))  
				{
					printf("Pro_3\n");
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH2�����ZZQ�Ų�һ��,��CH1ͨ��ִ��*/
				else if(ZZQ_Rdy_Run_Ch1 != AnZzqCh2)
				{
					printf("Pro_4\n");
					/*@-CH2�����϶���*/
					ZZQ_Rdy_Run_Ch2 = AnZzqCh2;
					ZZQ_Run_Dir_Ch2 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2];
				}
				/*@-CH2�����ZZQ��һ��,������CH2ͨ��ִ��*/
			    else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
			    {
			    	printf("Pro_5\n");
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
			    }
			    #endif

			}
			/*@-����ֻ����2��ZZQ����*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
			    /*@-����2ͨ������Ŀǰ����ZZQ�Ų�һ��,�ȴ�ǰ�涯��ִ�����,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock1\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock2\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock3\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock4\n");
				}

			}
		}
		/*@-��һ�β���2��ZZQ*/
		else if(ZZQ_Last_Pro_Num  == 2)
		{
			/*@-����ֻ����1��ZZQ����*/
			if(ZZQ_DSP_Net_Pro  == 1)
			{
				/*@-CH1�����ZZQ��һ��,������CH1ͨ��ִ��*/
			    if(ZZQ_Rdy_Run_Ch1 == AnZzqCh)
			    {
			    
			    }
				/*@-CH2�����ZZQ��һ��,��CH2ͨ��ִ��*/
				else if(ZZQ_Rdy_Run_Ch1 == AnZzqCh2)
				{
					/*@-CH2�е�����1��ZZQ�Ķ���*/
					ZZQ_Rdy_Run_Ch2 = ZZQ_Rdy_Run_Ch1;
					ZZQ_Run_Dir_Ch2 = ZZQ_Run_Dir_Ch1;

					/*@-CH1�����϶���*/
					ZZQ_Rdy_Run_Ch1 = AnZzqCh;
					ZZQ_Run_Dir_Ch1 = ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1];
				}
				/*@-CH1��CH2�����ZZQ�Ŷ���һ��,Lock*/
				else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch1 != AnZzqCh2))
				{
					printf("Lock5\n");
				}
			}
			/*@-����ֻ����2��ZZQ����*/
			else if(ZZQ_DSP_Net_Pro  == 2)
			{
				/*@-CH1��CH2�����ZZQ�Ŷ���һ��,Lock*/
				if((ZZQ_Rdy_Run_Ch1 != AnZzqCh) && (ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
				{
					printf("Lock6\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 != AnZzqCh2))
			    {
					printf("Lock7\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 != AnZzqCh)&&(ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
			    {
					printf("Lock8\n");
				}
				/*@-����2ͨ��,������һ����Ŀǰ������ZZQ��һ��,Lock*/
			    else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh2))
			    {
					printf("Lock9\n");
				}
				/*@-CH1��CH2�����ZZQ�Ŷ�һ��,����*/
				else if((ZZQ_Rdy_Run_Ch1 == AnZzqCh) && (ZZQ_Rdy_Run_Ch2 == AnZzqCh2))
				{

				}				

			}
		}
			
			
		/*@-ZZQ����ͨ��1�ܺ�*/
		if(ZZQ_Rdy_Run_Ch1 != 0)
		{
			AnZzqCh = ZZQ_Rdy_Run_Ch1;

			/*@-ͨ��1��ֹ����������*/
			if(ZZQ_Run_Dir_Ch1 == 0)
			{
				printf("CH1 Set 0!\n"); 
			}
			else if(ZZQ_Run_Dir_Ch1 == 1)
			{
				printf("CH1 Set 1!\n"); 
			}

			/*@-ͨ��1���ο��Ʒ���*/
			ZZQ_CH1_Last_Pro_Dir = ZZQ_Run_Dir_Ch1;
            /*@-����ZZQ X�Ŀ��Ʒ���*/
			ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch1] = ZZQ_Run_Dir_Ch1;

			/*@-ͨ��1��ҪReset*/
			DSP_Cmd_ZZQ_CH1_CMD_Reset = 1;
		}
		else if(ZZQ_Rdy_Run_Ch1 == 0)
		{
		  printf("CH1 Reset!\n"); 							
		}
		
		/*@-ZZQ����ͨ��2�ܺ�*/
		if(ZZQ_Rdy_Run_Ch2 != 0)
		{
			AnZzqCh2 = ZZQ_Rdy_Run_Ch2;

			/*@-ͨ��2��ֹ����������*/
			if(ZZQ_Run_Dir_Ch2 == 0)
			{
				printf("CH2 Set 0!\n"); 
			}
			else if(ZZQ_Run_Dir_Ch2 == 1)
			{
				printf("CH2 Set 1!\n"); 
			}

			/*@-ͨ��2���ο��Ʒ���*/
			ZZQ_CH2_Last_Pro_Dir = ZZQ_Run_Dir_Ch2;

			 /*@-����ZZQ X�Ŀ��Ʒ���*/
			ZZQ_X_Last_Pro_Dir[ZZQ_Rdy_Run_Ch2] = ZZQ_Run_Dir_Ch2;

			/*@-ͨ��2��ҪReset*/
			DSP_Cmd_ZZQ_CH2_CMD_Reset = 1;
		}
		else if(ZZQ_Rdy_Run_Ch2 == 0)
		{
			printf("CH2 Reset!\n"); 
		}

		/*@DX-����ZZQ��������*/
		DSP_Cmd_ZZQ_Status_Old = DSP_Cmd_ZZQ_Status;


		/*@-����ZZQ��������*/
		if(ZZQ_DSP_Net_Pro == 1)
		ZZQ_Last_Pro_Num = 1;
		else if(ZZQ_DSP_Net_Pro == 2)
		ZZQ_Last_Pro_Num = 2;
	
			
			
			
			
			
			
			
			
			
			

			printf("[ch1:%d]-[ch2:%d]\n",ZZQ_Rdy_Run_Ch1,ZZQ_Rdy_Run_Ch2);
	
			/*@DX-����ZZQ��������*/
			DSP_Cmd_ZZQ_Status_Old = DSP_Cmd_ZZQ_Status;
			
			printf("[zzq1_dir:%x]-[zzq2_dir:%x]\n",ZZQ_Run_Dir_Ch1,ZZQ_Run_Dir_Ch2);
		}
	}

	
	return (1);
}





