void delay_ms(unsigned long int x) 
{
    unsigned int i, j;
    for (i = 0; i < x; i++)
        for (j = 0; j < 711; j++);
}