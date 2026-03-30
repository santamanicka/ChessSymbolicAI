#include<math.h>

void scan(int board[8][8],int firstrow,int firstcol,int nextrow,int nextcol,int &cleanpath,int option) // to find the presence of any hurdles along the path of a bishop,rook,queen
{
	int i,j,clear=1;
	if(option==1)
	{
		if(firstrow>nextrow)
		{
			if(firstcol>nextcol)
				for(i=firstrow-1,j=firstcol-1;i>nextrow && j>nextcol;i--,j--)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
			else
				for(i=firstrow-1,j=firstcol+1;i>nextrow && j<nextcol;i--,j++)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
		}
		else
		{
			if(firstcol>nextcol)
				for(i=firstrow+1,j=firstcol-1;i<nextrow && j>nextcol;i++,j--)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
			else
				for(i=firstrow+1,j=firstcol+1;i<nextrow && j<nextcol;i++,j++)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
		}// end of else of second if
		cleanpath=clear;
		return;
	} //end of option if
	if(option==2)
	{
		clear=1;
		if(firstrow==nextrow)
		{
			if(firstcol>nextcol)
				for(i=firstrow,j=firstcol-1;j>nextcol;j--)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
			else
				for(i=firstrow,j=firstcol+1;j<nextcol;j++)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
		}
		else if(firstcol==nextcol)
		{
			if(firstrow>nextrow)
				for(i=firstrow-1,j=firstcol;i>nextrow;i--)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
			else
				for(i=firstrow+1,j=firstcol;i<nextrow;i++)
				{
					if(board[i][j]!=0)
					{
						clear=0;
						break;
					}
				}
		}
		cleanpath=clear;
		return;
	} // end of second option if
}

void verify(int who,int board[8][8],int firstrow,int firstcol,int nextrow,int nextcol,int &ok)
{
	int cleanpath=0;
	if(abs(board[firstrow][firstcol])==1)    //in case of a pawn
	{
		if(((firstrow-nextrow)==1 && who==0) || ((firstrow-nextrow)==-1 && who==1)) //single front move
		{
			if(board[nextrow][nextcol]==0 && firstcol==nextcol)     //1 front jump
				ok=1;
			else if(abs(firstcol-nextcol)==1 && ((board[nextrow][nextcol]<0 && who==0) || (board[nextrow][nextcol]>0 && who==1))) //both side crosses
				ok=1;
		}
		else if(board[nextrow][nextcol]==0 && (((firstrow==6 && who==0 && board[5][firstcol]==0) || (firstrow==1 && who==1 && board[2][firstcol]==0)) && abs(firstrow-nextrow)==2 && firstcol==nextcol)) //double front jump
			ok=1;
		else
			ok=0;
		return;
	}
	if(abs(board[firstrow][firstcol])==10 || abs(board[firstrow][firstcol])==35)     //in case of a bishop or a queen with diagonal moves
	{
		if(abs(firstrow-nextrow)==abs(firstcol-nextcol))
		{
			scan(board,firstrow,firstcol,nextrow,nextcol,cleanpath,1);
			ok=cleanpath;
			return;
		}
	}
	if(abs(board[firstrow][firstcol])==20 || abs(board[firstrow][firstcol])==35)  //in case of a rook or a queen with non-diagonal moves
	{
		if(firstrow==nextrow || firstcol==nextcol)
		{
			scan(board,firstrow,firstcol,nextrow,nextcol,cleanpath,2);
			ok=cleanpath;
			return;
		}
	}
	if(abs(board[firstrow][firstcol])==5) // in case of a knight
	{
		if((abs(firstrow-nextrow)==2 && abs(firstcol-nextcol)==1) || (abs(firstrow-nextrow)==1 && abs(firstcol-nextcol)==2))
			ok=1;
		return;
	}
	if(abs(board[firstrow][firstcol])==50) // in case of a king
	{
		if((firstrow==nextrow && abs(firstcol-nextcol)==1) || (firstcol==nextcol && abs(firstrow-nextrow)==1) || (abs(firstrow-nextrow)==1 && abs(firstcol-nextcol)==1))
			ok=1;
		return;
	}
}











