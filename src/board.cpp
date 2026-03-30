void drawboard()
{
	int x1,y1,x2,y2,x3,y3,x,y,i,j,poly[8];
	struct fillsettingstype fillinfo;
	x1=getmaxx()/2-250;
	y1=getmaxy()/2-225;
	x2=getmaxx()/2+250;
	y2=getmaxy()/2+225;
	setcolor(15);
	setfillstyle(1,15);
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			poly[0]=poly[6]=x1+(j*500/8);
			poly[2]=poly[4]=poly[0]+(500/8);
			poly[1]=poly[3]=y1+(i*450/8);
			poly[7]=poly[5]=poly[1]+(450/8);
			fillpoly(4,poly);
			getfillsettings(&fillinfo);
			if(fillinfo.color==6)
				setfillstyle(1,15);
			else
				setfillstyle(1,6);
		}
		if(fillinfo.color==6)
			setfillstyle(1,6);
		else
			setfillstyle(1,15);
	}
	setcolor(8);
	rectangle(x1,y1,x2,y2);
	rectangle(x1-5,y1-5,x2+5,y2+5);
	setfillstyle(1,8);
	floodfill(x1-2,y1-2,8);
	setcolor(0);
	setlinestyle(0,1,2);
	line(x1,y1,x1-5,y1-5);
	line(x2,y1,x2+5,y1-5);
	line(x1,y2,x1-5,y2+5);
	line(x2,y2,x2+5,y2+5);
	setcolor(15);
	rectangle(x1,y1,x2,y2);
}

void drawpawn(int x,int y,int colour)
{
	setcolor(colour);
	setfillstyle(1,colour);
	line(x,y,x+15,y);         //BASE LINE
	line(x,y,x+5,y-10);        //SLANTING LINES
	line(x+15,y,x+10,y-10);
	int x1=(2*x+15)/2;
	int y1=y-15;
	arc(x1,y1,315,240,5);     //ARC
	floodfill(x1,y1,colour);
}

void drawrook(int x,int y,int colour)
{
	setcolor(colour);
	setfillstyle(1,colour);
	line(x,y,x+20,y);    // BASE LINE
	line(x,y,x+4,y-5);        // SLANTING LINES
	line(x+20,y,x+16,y-5);
	line(x+4,y-5,x+4,y-20);     //VERTICAL LINES
	line(x+16,y-5,x+16,y-20);
	line(x+4,y-20,x,y-20);        // HORIZONTAL LINES
	line(x+16,y-20,x+20,y-20);
	line(x,y-20,x,y-30);          //VERTICAL LINES
	line(x+20,y-20,x+20,y-30);
	int i,up=1,x1=x;
	for(i=0;i<=4;i++)
	{
		if(up==1)                  //TOP GROOVES
		{
			line(x1,y-30,x1+4,y-30);
			up=0;
		}
		else
		{
			line(x1,y-27,x1+4,y-27);
			up=1;
		}
		line(x1,y-30,x1,y-27);
		x1 += 4;
	}
	floodfill(x+6,y-3,colour);
}

void drawbishop(int x,int y,int colour)
{
	setcolor(colour);
	setfillstyle(1,colour);
	line(x,y,x+20,y);           //BASE LINE
	line(x,y,x+7,y-10);	    // SLANTING LINES
	line(x+20,y,x+13,y-10);
	line(x+7,y-10,x+7,y-16);     //VERTICAL LINES
	line(x+13,y-10,x+13,y-16);
	int x1=(2*x+20)/2;
	int y1=y-23;
	arc(x1,y1,300,240,7);        //ARC
	floodfill(x1,y1,colour);
	if(colour==3)
		setcolor(0);
	else
		setcolor(3);
	if(colour==3 || colour==0)
	{
		line(x1,y-27,x1,y-18);      //PLUS SIGN
		line(x+6,y1,x+14,y1);
	}
}

void drawknight(int x,int y,int colour)
{
	setcolor(colour);
	setfillstyle(1,colour);
	int x1,y1;
	line(x,y,x+20,y);         //BASE LINE
	line(x,y,x,y-3);          // VERTICAL LINES
	line(x+20,y,x+20,y-3);
	line(x+20,y-3,x+18,y-3);   // BOTTOM SQUARE SLOT
	line(x+18,y-3,x+18,y-5);
	line(x+18,y-5,x+20,y-5);
	line(x,y-3,x+12,y-20);     //KNIGHT's SLANTING NECK
	line(x+20,y-5,x+20,y-20);  //VERTICAL NECK
	line(x+20,y-20,x+23,y-25); //SLANTING BACK HEAD
	line(x+23,y-25,x+23,y-30); //VERTICAL BACK HEAD
	line(x+12,y-20,x+4,y-20);  // BELOW MOUTH
	line(x+23,y-30,x+17,y-30);  //TOP HEAD
	line(x+17,y-30,x+4,y-24);   // SLANTING FACE
	x1=x+4;
	y1=y-22;
	arc(x1,y1,90,270,2);
	floodfill(x1,y1,colour);
}

void drawking(int x,int y,int colour)
{
	int x1,y1;
	setcolor(colour);
	setfillstyle(1,colour);
	line(x,y,x+20,y);       //BASE LINE
	line(x,y,x+6,y-10);    //BOTTOM SLANTING LINES
	line(x+20,y,x+14,y-10);
	line(x+6,y-10,x-1,y-19);    // TOP SLANTING LINES
	line(x+14,y-10,x+20,y-18);
	x1=x+3;                   // SIDE ARCS
	y1=(2*y-45)/2;
	arc(x1,y1,45,225,5);
	x1=x+17;
	arc(x1,y1,315,135,5);
	line(x+7,y1-3,x+7,y1-8);         //BOTTOM TO TOP OF PLUS
	line(x+13,y1-3,x+13,y1-8);
	line(x+7,y1-8,x+4,y1-8);         //RIGHT TO LEFT
	line(x+13,y1-8,x+16,y1-8);       //LEFT TO RIGHT
	line(x+4,y1-8,x+4,y1-12);        //BOTTOM TO TOP
	line(x+16,y1-8,x+16,y1-12);
	line(x+4,y1-12,x+7,y1-12);       //LEFT TO RIGHT
	line(x+16,y1-12,x+13,y1-12);     //RIGHT TO LEFT
	line(x+7,y1-12,x+7,y1-15);       // BOTTOM TO TOP
	line(x+13,y1-12,x+13,y1-15);
	line(x+7,y1-15,x+13,y1-15);     //FLAT TOP
	floodfill(x1,y1,colour);
}

void drawqueen(int x,int y,int colour)
{
	int i,x1,y1,x2,y2;
	setcolor(colour);
	setfillstyle(1,colour);
	line(x,y,x+20,y);    // BASE LINE
	line(x,y,x+6,y-15);    // BOTTOM SLANTING LINES
	line(x+20,y,x+14,y-15);
	line(x+6,y-15,x+3,y-18);    //COLLAR
	line(x+14,y-15,x+17,y-18);
	line(x+3,y-18,x+17,y-18);
	line(x+6,y-18,x+2,y-27);     //TOP SLANTING LINES
	line(x+14,y-18,x+18,y-27);
	line(x+2,y-27,x+2,y-36);     //TOP VERTICAL LINES
	line(x+18,y-27,x+18,y-36);
	int backslash=1;
	x1=x+2;
	y1=y-36;
	for(i=0;i<=3;i++)                //UPPER ZIG ZAGS
	{
		x2=x1+4;
		if(backslash==1)
		{
			backslash=0;
			y2=y-32;
		}
		else
		{
			backslash=1;
			y2=y-36;
		}
		line(x1,y1,x2,y2);
		x1=x2;
		y1=y2;
	}
	floodfill(x+5,y-3,colour);
	floodfill(x+7,y-20,colour);
}

void convert(int row,int col,int &x,int &y)
{
	int initx=getmaxx()/2-250;
	int inity=getmaxy()/2-225;
	x=initx+(col*500/8)+23;
	y=inity+(row*450/8)+45;
}

void movepiece(int who,int pieceid1,int pieceid2,int starter,int row1,int col1,int row2,int col2)
{
	int a=-1,b=-1,x=-1,y=-1,colour1,colour2,colour3,pluscolour;
	convert(row1,col1,a,b);
	convert(row2,col2,x,y);
	if((row1%2!=0 && col1%2!=0) || (row1%2==0 && col1%2==0))
		colour1=15;
	else                       // colour1 is for previous position
		colour1=6;
	if((row2%2!=0 && col2%2!=0) || (row2%2==0 && col2%2==0))
		colour3=15;
	else                       // colour3 is for previous position
		colour3=6;
	if(starter==1)
	{
		pluscolour=0;
		if(who==0)
			colour2=3;
		else
			colour2=0;
	}
	else
	{
		pluscolour=3;
		if(who==0)
			colour2=0;
		else
			colour2=3;
	}
	switch(abs(pieceid2))     // for erasing the piece if present in the new position
	{
		case 1:
			drawpawn(x,y,colour3);
			break;
		case 10:
			setcolor(pluscolour);
			int x1=(2*x+20)/2;
			int y1=y-23;
			line(x1,y-27,x1,y-18);      // ERASE PLUS SIGN
			line(x+6,y1,x+14,y1);
			drawbishop(x,y,colour3);
			break;
		case 5:
			drawknight(x,y,colour3);
			break;
		case 20:
			drawrook(x,y,colour3);
			break;
		case 35:
			drawqueen(x,y,colour3);
			break;
		case 50:
			drawking(x,y,colour3);
	}
	switch(abs(pieceid1))          // for moving the selected piece
	{
		case 1:
			drawpawn(a,b,colour1);
			drawpawn(x,y,colour2);
			break;
		case 10:
			drawbishop(a,b,colour1);
			setcolor(colour1);
			int x1=(2*a+20)/2;
			int y1=b-23;
			line(x1,b-27,x1,b-18);      // ERASE PLUS SIGN
			line(a+6,y1,a+14,y1);
			drawbishop(x,y,colour2);
			break;
		case 5:
			drawknight(a,b,colour1);
			drawknight(x,y,colour2);
			break;
		case 20:
			drawrook(a,b,colour1);
			drawrook(x,y,colour2);
			break;
		case 35:
			drawqueen(a,b,colour1);
			drawqueen(x,y,colour2);
			break;
		case 50:
			drawking(a,b,colour1);
			drawking(x,y,colour2);
	}
}

void drawpieces(int who)
{
	int i,j,x,y,x1,y1,y2,colour;
	x=getmaxx()/2-250;
	y=getmaxy()/2-225;
	y1=y+(6*450/8)+45;           //PAWN
	y2=y+(1*450/8)+45;
	for(i=0;i<=7;i++)
	{
		x1=x+(i*500/8)+23;
		if(who==1)
		{
			drawpawn(x1,y1,0);
			drawpawn(x1,y2,3);
		}
		else
		{
			drawpawn(x1,y1,3);
			drawpawn(x1,y2,0);
		}
	}
	if(who==1)
		colour=3;                  //ROOK
	else
		colour=0;
	for(i=0;i<=7;i+=7)
	{
		for(j=0;j<=7;j+=7)
		{
			x1=x+(j*500/8)+23;
			y1=y+(i*450/8)+45;
			drawrook(x1,y1,colour);
		}
		if(colour==0)
			colour=3;
		else
			colour=0;
	}
	if(who==1)
		colour=3;                  //BISHOP
	else
		colour=0;
	for(i=0;i<=7;i+=7)
	{
		for(j=2;j<=5;j+=3)
		{
			x1=x+(j*500/8)+23;
			y1=y+(i*450/8)+45;
			drawbishop(x1,y1,colour);
		}
		if(colour==0)
			colour=3;
		else
			colour=0;
	}
	if(who==1)
		colour=3;                  //KNIGHT
	else
		colour=0;
	for(i=0;i<=7;i+=7)
	{
		for(j=1;j<=6;j+=5)
		{
			x1=x+(j*500/8)+23;
			y1=y+(i*450/8)+45;
			drawknight(x1,y1,colour);
		}
		if(colour==0)
			colour=3;
		else
			colour=0;
	}
	int pos;
	if(who==1)
	{
		colour=3;                  //KING
		pos=3;
	}
	else
	{
		colour=0;
		pos=4;
	}
	for(i=0;i<=7;i+=7)
	{
		if(i==7 && colour==3)
			colour=0;
		else if(i==7 && colour==0)
			colour=3;
		x1=x+(pos*500/8)+23;
		y1=y+(i*450/8)+45;
		drawking(x1,y1,colour);
	}
	if(who==1)
	{
		colour=3;                  //QUEEN
		pos=4;
	}
	else
	{
		colour=0;
		pos=3;
	}
	for(i=0;i<=7;i+=7)
	{
		if(i==7 && colour==3)
			colour=0;
		else if(i==7 && colour==0)
			colour=3;
		x1=x+(pos*500/8)+23;
		y1=y+(i*450/8)+45;
		drawqueen(x1,y1,colour);
	}
}