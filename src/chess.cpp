#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
#include "board.cpp"
#include "legalmov.cpp"
#include "looknfee.cpp"

void initiate(int board[8][8])
{
	int i,j;
	for(i=0;i<=7;i++)
		for(j=0;j<=7;j++)
			board[i][j]=0; //0 INDICATES AN EMPTY POSITION
}

void setboard(int board[8][8],int who)
{
	int i,j;
	for(i=0;i<=7;i++)           //PAWNS
	{
		board[1][i]=-1;
		board[6][i]=1;
	}
	board[0][0]=board[0][7]=-20; // ROOK
	board[7][0]=board[7][7]=20;
	board[0][1]=board[0][6]=-5; //knight
	board[7][1]=board[7][6]=5;
	board[0][2]=board[0][5]=-10; //bishop
	board[7][2]=board[7][5]=10;
	if(who==1)
	{
		board[0][3]=-50;     //king
		board[7][3]=50;
		board[0][4]=-35;     //queen
		board[7][4]=35;
	}
	else
	{
		board[0][3]=-35;        //queen
		board[7][3]=35;
		board[0][4]=-50;      //king
		board[7][4]=50;
	}
}

void kingcheck(int who,int board[8][8],int &check)
{
	int i,j,kingrow,kingcol,seekfor,done=0;
	check=0;
	if(who==0)
		seekfor=50;
	else
		seekfor=-50;
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(board[i][j]==seekfor)
			{
				kingrow=i;
				kingcol=j;
				done=1;
				break;
			}
		}
		if(done==1)
			break;
	}
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if((board[i][j]<0 && who==0) || (board[i][j]>0 && who==1))
				verify(!who,board,i,j,kingrow,kingcol,check);
			if(check==1)
				break;
		}
		if(check==1)
			break;
	}
}

void think(int who,int depth,int board[8][8],int best[5],int &score,int use,int pass)
{
	if(depth==5)
	{
		if(depth%2!=0)
			score=-score;
		return;
	}
	int i,j,k,l,check=0,legal=0,lostpiece=0,mate=1,temp=0,newscore=0;
	for(i=0;i<=7;i++)
	for(j=0;j<=7;j++)
		for(k=0;k<=7;k++)
		for(l=0;l<=7;l++)
		{
			if((who==0 && board[i][j]>0 && board[k][l]<=0) || (who==1 && board[i][j]<0 && board[k][l]>=0))
				verify(who,board,i,j,k,l,legal);
			if(legal==1)
			{
				lostpiece=board[k][l];
				if(board[k][l]==5)
					temp=score+10;
				else if(board[k][l]==-5)
					temp=score-10;
				else
					temp=score+board[k][l];
				board[k][l]=board[i][j];
				board[i][j]=0;
				kingcheck(who,board,check);
				if(check==1)
				{
					check=legal=0;
					board[i][j]=board[k][l];
					board[k][l]=lostpiece;
					continue;
				}
				else
					mate=0;
				think(!who,depth+1,board,best,temp,-pass,-use);
				newscore=-temp;
				if(newscore>pass)
				{
					pass=newscore;
					if(depth==0)
					{
						best[0]=i;
						best[1]=j;
						best[2]=k;
						best[3]=l;
						best[4]=-pass;
					}
				}
				if(pass>=use)
				{
					score=pass;
					board[i][j]=board[k][l];
					board[k][l]=lostpiece;
					return;
				}
				board[i][j]=board[k][l];
				board[k][l]=lostpiece;
				legal=0;
			}
			else
				continue;
		}
		if(mate==1)
		{
			if(depth%2==0)
				score=score-100;
			else
				score=-(score+100);
		}
		else
			score=pass;
}

void play(int board[8][8],int who,int starter)
{
	if(who==-1)
	{
		char ans;
		settextstyle(3,0,3);
		outtextxy(0,0,"Want to play Black or White(B/W)? :");
		while(!kbhit())
			blink(getmaxx()-150,0);
		deblink(getmaxx()-150,0);
		ans=getch();
		if(ans=='b' || ans=='B')
		{
			who=1;
			starter=0;
			outtextxy(getmaxx()-150,0,"Black");
		}
		else
		{
			who=0;
			starter=1;
			outtextxy(getmaxx()-150,0,"White");
		}
		getch();
		setcolor(0);
		outtextxy(0,0,"Want to play Black or White(B/W)? :");
		drawboard();
		drawpieces(who);
		setboard(board,who);
	}
	if(who==0)
	{
		int x1,y1,x,y,pieceid1,pieceid2,row=7,col=4,permrow=-1,permcol=-1,perm=0,deleted=0,ok=0,check=0;
		char ch;
		while(1)
		{
			selectsquare(row,col,ch,permrow,permcol,perm);
			ch=getch();
			while(ch!=83)   // when delete is not pressed
			{
				if(ch==27)
					exit(0);
				if(ch!=82)
					redrawrect(row,col);
				if(ch==82 && deleted==1)      //when insert pressed
				{
					if(board[row][col]<=0) //inserted square is either free or contains opp's pieces
						verify(who,board,permrow,permcol,row,col,ok);
					if(ok==1)
					{
						pieceid1=board[permrow][permcol];
						pieceid2=board[row][col];
						board[row][col]=board[permrow][permcol];
						board[permrow][permcol]=0;
						kingcheck(who,board,check);
						if(check==0)
						{
							movepiece(who,pieceid1,pieceid2,starter,permrow,permcol,row,col);
							redrawrect(row,col);
							redrawrect(permrow,permcol);
							break;
						}
						else
						{
							ok=0;
							board[permrow][permcol]=pieceid1;
							board[row][col]=pieceid2;
							redrawrect(row,col);
							row=permrow;
							col=permcol;
						}
					}
					else
					{
						redrawrect(row,col);
						row=permrow;
						col=permcol;
					}
				}
				if(ch==75)
				{
					col--;
					if(col<0)
						col=7;
				}
				if(ch==72)
				{
					row--;
					if(row<0)
						row=7;
				}
				if(ch==77)
				{
					col++;
					if(col>7)
						col=0;
				}
				if(ch==80)
				{
					row++;
					if(row>7)
						row=0;
				}
				selectsquare(row,col,ch,permrow,permcol,perm);
				ch=getch();
			} // end of inner while
			if(ok==1)
				break;
			if(deleted==1)
				redrawrect(permrow,permcol); // dehighlite the previously highlited rectangle
			if(board[row][col]==0 || board[row][col]<0)
			{
				perm=0;
				deleted=0;
				continue;
			}
			else
			{
				permrow=row; // once deleted this row will be highlited always
				permcol=col; //  "      "      "   col "      "         "
				perm=1;     // signal sent to selectsquare to highlite always
				deleted=1;
				continue;
			}
		}  // end of outer while
	} // end of if
	if(who==1)
	{
		int depth=0,best[5],score=0,pieceid1,pieceid2;
		int use=500,pass=-500;
		char ch;
		best[0]=best[1]=best[2]=best[3]=-1;
		best[4]=0;
		think(who,depth,board,best,score,use,pass);
		pieceid1=board[best[0]][best[1]];
		pieceid2=board[best[2]][best[3]];
		board[best[2]][best[3]]=board[best[0]][best[1]];
		board[best[0]][best[1]]=0;
		//cout<<best[4]<<endl;
		sound(200);
		selectsquare(best[0],best[1],ch,best[2],best[3],1);
		redrawrect(best[0],best[1]);
		redrawrect(best[2],best[3]);
		nosound();
		movepiece(who,pieceid1,pieceid2,starter,best[0],best[1],best[2],best[3]);
	}
	play(board,!who,starter);
}

void main()
{
	int gd=DETECT,gm,board[8][8];
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	initiate(board);
	play(board,-1,-1);      // -1 to start the game
	getch();
	closegraph();
}
