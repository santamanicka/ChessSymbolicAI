void blink(int x,int y)
{
	if(getcolor()==15)
		setcolor(0);
	else
		setcolor(15);
	outtextxy(x,y,"_");
	delay(100);
}

void deblink(int x,int y)
{
	setcolor(0);
	outtextxy(x,y,"_");
	setcolor(15);
}

void selectsquare(int row,int col,char &ch,int permrow,int permcol,int perm)
{
	int initx,inity,x1,y1,x2,y2,x3,y3,x4,y4,color;
	initx=getmaxx()/2-250;
	inity=getmaxy()/2-225;
	x1=initx+(col*500/8)+5;
	y1=inity+(row*450/8)+5;
	x2=x1+(500/8)-10;
	y2=y1+(450/8)-10;
	setcolor(0);
	rectangle(x1,y1,x2,y2);
	if(perm==1)
	{
		x3=initx+(permcol*500/8)+5;
		y3=inity+(permrow*450/8)+5;
		x4=x3+(500/8)-10;
		y4=y3+(450/8)-10;
		rectangle(x3,y3,x4,y4);
	}
	setlinestyle(0,1,1);
	while(!kbhit())
	{
		color=rand()%16;
		setcolor(color);
		rectangle(x1,y1,x2,y2);
		if(perm==1)
			rectangle(x3,y3,x4,y4);
	}
	setlinestyle(0,1,1);
	setcolor(0);
	rectangle(x1,y1,x2,y2);
	setcolor(15);
	rectangle(x1,y1,x2,y2);
	ch=getch();
}

void redrawrect(int row,int col)
{
	int initx,inity,x1,y1,x2,y2;
	initx=getmaxx()/2-250;
	inity=getmaxy()/2-225;
	x1=initx+(col*500/8)+5;
	y1=inity+(row*450/8)+5;
	x2=x1+(500/8)-10;
	y2=y1+(450/8)-10;
	setcolor(0);
	rectangle(x1,y1,x2,y2);
	if((row%2==0 && col%2==0) || (row%2!=0 && col%2!=0))
		setcolor(15);
	else
		setcolor(6);
	rectangle(x1,y1,x2,y2);
}
