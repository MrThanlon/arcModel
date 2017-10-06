/*
本程序可以让环绕的LED按照规律跑马
对应的io由io.txt中所示
板子上的连接如下
*********************************************
*外圈1,3,5,6,8,10,12,13,15,17,19,20自动常亮 *
*LED序号    00,02,04,07,09,11,14,16,18跑马  *
*对应芯片io 60,13,26,51,53,55,57,58,59      *
*对应ar io  30,16,13,41,37,35,33,32,31      *
************************************************************
*内圈全部io控制21~50                                       *
*常亮       22,24,26,28,31,33,35,37,40,42,44,46,(48,49,50) *
*对应芯片io 07,24,35,38,41,43,63,70,74,76,78,02            *
*对应ar io	04,11,49,46,43,21,15,39,26,24,22,05            *
************************************************************
*内圈跑马   21,23,25,27,29,30,32,34,36,38,39,41,43,45,47   *
*对饮芯片io	06,23,25,37,39,40,42,44,64,71,73,75,77,01,03   *
*对应ar io	03,10,12,47,45,44,43,20,14,29,27,25,23,05,02   *
************************************************************
*/

#define OSPEED 200//外圈速度,更改200即可改变速度大小,1到1000
#define ISPEED 200//内圈速度,同上

#define uint unsigned
#define uchar unsigned char
#define ulong unsigned long
#define pm pinMode
#define dw digitalWrite

const uint ledOutside[9]=     {30,16,13,41,37,35,33,32,31};//外圈LED
const uint ledInsideLight[12]={ 4,11,49,46,43,21,15,39,26,24,22, 5};//内圈常亮LED
const uint ledInsideFlash[15]={ 3,10,12,47,45,44,43,20,14,29,27,25,23,05,02};

const ulong Odelay=1000/OSPEED;
const ulong Idelay=1000/ISPEED;//由速度定义延迟

int i1=0,i2=0,i3=0;//分别对应三个数组

void setup()
{
	//让上面所以的io处于output状态
	for(i1=8 ;i1!=0;i1-=1)
	{
		pm(ledOutside[i1]	,OUTPUT);
		dw(ledOutside[i1],LOW);//初始化拉低电平
	}
	for(i3=14;i3!=0;i3-=1)
	{
		pm(ledInsideFlash[i3],OUTPUT);
		dw(ledInsideFlash[i3],LOW);//初始化拉低电平
	}
	for(i2=11;i2!=0;i2-=1)
	{
		pm(ledInsideLight[i2],OUTPUT);
		dw(ledInsideLight[i2],HIGH);//常亮拉高电平
	}

	i1=8;
	i3=0;
}

void loop()
{
	//使用millis%delay来确定触发时刻
	if(millis()%Odelay==0)//外圈触发
	{
		//外圈逆时针跑,i1从8到0循环
		dw(ledOutside[i1-1],HIGH);//点亮上一盏
		dw(ledOutside[i1],LOW);//关闭这一盏
		i1-=1;//i1降1
		if(i1==-1) {i1=8;}//i1到-1的时候回到8
	}

	if(millis()%Idelay==0)
	{
		//内圈顺时针跑马,i3从0到14循环
		dw(ledInsideLight[i3+1],HIGH);//点亮下一盏
		dw(ledInsideLight[i3],LOW);//关闭这一盏
		i3+=1;//i3升1
		if(i3==15){i3=0;}//i3到15的时候回到0
	}
}
