
#define set_reg_val(addr,val)   (*(volatile unsigned int *)(addr))=(val)
#define get_reg_val(addr)       (*(volatile unsigned int *)(addr))

void delay_us(unsigned int time)
{    
   unsigned int i=0;  
   while(time--)
   {
      i=10;
      while(i--) ;    
   }
}

void delay(unsigned int  num)
{
  unsigned int i,j;
  for(i=0;i<num;i++)
    for(j=0;j<0x800;j++);
}

void set_reg_bit_all_one(unsigned int addr,unsigned int mask)
{
	unsigned int val;
	val = get_reg_val(addr);
	val |= (mask);
	set_reg_val(addr,val);
}

void sys_int()
{
	//1.开启外部时钟 HSE
	set_reg_bit_all_one(0x40021000,(1 << 16));
	//1.开启外部时钟 HSE
	while ((get_reg_val(0x40021000) & (1 << 17)) == 0) {}
	
	//2. PLLCLK设置
	//设置 PLL 倍频系数 9倍频
	set_reg_bit_all_one(0x40021004,(7 << 18));
	//设置 HSE 作为 PLLCLK 输入源
	set_reg_bit_all_one(0x40021004,(1 << 16));

	//3. 打开 PLL 电路
	set_reg_bit_all_one(0x40021000,(1 << 24));
	//3. 打开 PLL 电路
	while ((get_reg_val(0x40021000) & (1 << 25)) == 0) {}

	//4. 设置 FLASH 时延 让HSE能正常工作
	set_reg_bit_all_one(0x40022000,(1 << 1));

	//5. SYSCLK设置
	//设置 PLL 作为 SYSCLK 输入源
	set_reg_bit_all_one(0x40021004,(1 << 1));
	//等待 SYSCLK 就绪
	while ((get_reg_val(0x40021004) & (1 << 3)) == 0) {}

	//6. 设置 AHP1 预分频系数为2
	set_reg_bit_all_one(0x40021004,(1 << 10));

	//使能PORTB时钟
	set_reg_bit_all_one(0x40021018,(1 << 3));

	//PB.12 推挽输出
	set_reg_bit_all_one(0x40010C04, 0x00030000);

	//PB.12 输出低
	set_reg_bit_all_one(0x40010C0C, 0x00000000);
}

int main(void)
{
    sys_int();
    while(1)
    {
        delay(500);
		//PB.12 输出高
        set_reg_val(0x40010C0C,0x00001000);
        delay(500);
		//PB.12 输出低
        set_reg_val(0x40010C0C,0x00000000);
    }
}