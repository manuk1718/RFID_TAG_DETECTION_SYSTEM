#include<reg51.h>
#include<string.h>
sbit EN=P3^4;
sbit LED=P3^1;
sbit RW=P3^6;
sbit RS=P3^5;

void delay_ms(unsigned long int x) 
{
    unsigned int i, j;
    for (i = 0; i < x; i++)
        for (j = 0; j < 711; j++);
}

void lcdwrite(unsigned char lcddata)
{
	P1=lcddata;
	EN=1;
	delay_ms(10);
	EN=0;
	delay_ms(10);
}

int main ()
{

	unsigned char	rx_string[20];
	unsigned char top_line[]=" RFID DETECTOR";
	unsigned char correct_tag[]="ACCESS ALLOWED";
	unsigned char unknown_tag[]="ACCESS DENIED";
	unsigned char cmd[]={0x38,0x0E,0x06,0x01,0x80};
	
	int i,j;
	unsigned char* tags[]={"09008206C944","09008206A825","840085A99038"};

	/*set BAUD rate*/
	delay_ms(20);
	
	SCON = 0x50;
	TMOD = 0x20;
	TR1 = 1;
	TH1 =0xFD;
	
	/* LED is always on */
	LED=1;
	
	RW=0;
	//COMMAND MODE lcd initilisation 
	RS=0;
	for (j=0;j<5;j++)
	{
		lcdwrite(cmd[j]);
	}
				//datamode
	RS=1;
	for (j=0;top_line[j]!='\0';j++)
	{
		lcdwrite(top_line[j]);
	}
	
	while (1)
	{
		unsigned char result=1;
		/*read input*/
		for (j=0;j<12;j++)
		{
			while(RI==0)
			{
			}
			rx_string[j]=SBUF;
			RI=0;
		}
		
		rx_string[12]='\0';
		
		for (i=0;i<3;i++)
		{ 
			while(!strcmp(rx_string,tags[i]))
			{
				result=0;
				break;
			}
		}
			if (!result)
			{
				LED=0;
				delay_ms(1000);
				LED=1;
				RW=0;
				//COMMAND MODE 
				RS=0;
				lcdwrite(0xC0);
				//datamode
				RS=1;
				for (j=0;j<16;j++)
				{
					lcdwrite(' ');
				}
				RS=0;
				lcdwrite(0xC0);
				RS=1;
				for (j=0;correct_tag[j]!='\0';j++)
				{
					lcdwrite(correct_tag[j]);
				}
			}
			else
			{
				RW=0;
				//COMMAND MODE 
				RS=0;
				lcdwrite(0xC0);
				//datamode
				RS=1;
				for (j=0;j<16;j++)
				{
					lcdwrite(' ');
				}
				RS=0;
				lcdwrite(0xC0);
				RS=1;
				for (j=0;unknown_tag[j]!='\0';j++)
				{
					lcdwrite(unknown_tag[j]);
				}
				delay_ms(1000);
			}
	}
}
