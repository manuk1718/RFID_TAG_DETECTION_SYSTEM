#include<reg51.h>
#include<string.h>
sbit LED=P1^1;

void delay_ms(unsigned long int x) 
{
    unsigned int i, j;
    for (i = 0; i < x; i++)
        for (j = 0; j < 1275; j++);
}

int main ()
{
	unsigned char result;
	unsigned char	rx_string[20];
	int i;
	unsigned char	rx_string1[20]="aaaaaaaaaaaa";

	/*set BAUD rate*/
	
	SCON = 0x50;
	TMOD = 0x20;
	TR1 = 1;
	TH1 =0xFD;
	
	while (1)
	{
		/* LED is always on */
		LED=1;
		for (i=0;i<12;i++)
		{
			while(RI==0)
			{
			}
			rx_string[i]=SBUF;
			RI=0;
		}
		rx_string[12]='\0';
		result=strcmp(rx_string,rx_string1);
		if (!result)
		{
			LED=0;
			delay_ms(1000);
		}
	}
}