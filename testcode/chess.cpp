#include "chess.h"

ChessBoard::ChessBoard()
{
	for(int i = 0;i < 8;i++)
		for(int j =0;j < 8 ;j++)
		{
			board[i][j] = NULL;
		}
}

void ChessBoard::initialize()
{
	//初始化一个棋盘的开局状态，使用placePiece放置棋子
	Rook whiteRookLeft(this,ChessPiece::WHITE);
	Rook whiteRookRight(this,ChessPiece::WHITE);
	whiteRookLeft.setStrCode("\u2656");
	whiteRookRight.setStrCode("\u2656");
	placePiece(&whiteRookLeft,"a1");
	placePiece(&whiteRookRight,"h1");
	
	Knight whiteKnightLeft(this,ChessPiece::WHITE);
	Knight whiteKnightRight(this,ChessPiece::WHITE);
	whiteKnightLeft.setStrCode("\u2658");
	whiteKnightRight.setStrCode("\u2658");
	placePiece(&whiteKnightLeft,"b1");
	placePiece(&whiteKnightRight,"g1");
	
	Bishop whiteBishopLeft(this,ChessPiece::WHITE);
	Bishop whiteBishopRight(this,ChessPiece::WHITE);
	whiteBishopLeft.setStrCode("\u2657");
	whiteBishopRight.setStrCode("\u2657");	
	placePiece(&whiteBishopLeft,"c1");
	placePiece(&whiteBishopRight,"f1");
	
	Queen whiteQueen(this,ChessPiece::WHITE);
	whiteQueen.setStrCode("\u2655");
	placePiece(&whiteQueen,"d1");
	
	King whiteKing(this,ChessPiece::WHITE);
	whiteKing.setStrCode("\u2654");
	placePiece(&whiteKing,"e1");
	
	Pawn whitePawn(this,ChessPiece::WHITE);
	whitePawn.setStrCode("\u2659");
	placePiece(&whitePawn,"a2");	
	Pawn whitePawn1 = whitePawn;
	placePiece(&whitePawn1,"b2");	
	Pawn whitePawn2 = whitePawn;
	placePiece(&whitePawn2,"c2");
	puts("++++++++++++++++++++++++++++++++++==============================");
	vector<string> vecResult;
	ChessPiece* ptr = &whitePawn2;
	ptr->legalMoves(vecResult);
	puts("+++++++++++++++++++++++++++++++++++");
	vecResult.clear();
	board[6][2]->print();
	Pawn whitePawn3 = whitePawn;
	placePiece(&whitePawn3,"d2");
	Pawn whitePawn4 = whitePawn;
	placePiece(&whitePawn4,"e2");
	Pawn whitePawn5 = whitePawn;
	placePiece(&whitePawn5,"f2");
	Pawn whitePawn6 = whitePawn;
	placePiece(&whitePawn6,"g2");
	Pawn whitePawn7 = whitePawn;
	placePiece(&whitePawn7,"h2");
	
	Rook blackRookLeft(this,ChessPiece::BLACK);
	Rook blackRookRight(this,ChessPiece::BLACK);
	blackRookLeft.setStrCode("\u265C");
	blackRookRight.setStrCode("\u265C");
	placePiece(&blackRookLeft,"a8");
	placePiece(&blackRookRight,"h8");
	
	Knight blackKnightLeft(this,ChessPiece::BLACK);
	Knight blackKnightRight(this,ChessPiece::BLACK);
	blackKnightLeft.setStrCode("\u265E");
	blackKnightRight.setStrCode("\u265E");
	placePiece(&blackKnightLeft,"b8");
	placePiece(&blackKnightRight,"g8");
	
	Bishop blackBishopLeft(this,ChessPiece::BLACK);
	Bishop blackBishopRight(this,ChessPiece::BLACK);
	blackBishopLeft.setStrCode("\u265D");
	blackBishopRight.setStrCode("\u265D");	
	placePiece(&blackBishopLeft,"c8");
	placePiece(&blackBishopRight,"f8");
	
	Queen blackQueen(this,ChessPiece::BLACK);
	blackQueen.setStrCode("\u265B");
	placePiece(&blackQueen,"d8");
	
	King blackKing(this,ChessPiece::BLACK);
	blackKing.setStrCode("\u265A");
	placePiece(&blackKing,"e8");
	
	Pawn blackPawn(this,ChessPiece::BLACK);
	blackPawn.setStrCode("\u265F");
	placePiece(&blackPawn,"a7");	
	Pawn blackPawn1 = blackPawn;
	placePiece(&blackPawn1,"b7");	
	Pawn blackPawn2 = blackPawn;
	placePiece(&blackPawn2,"c7");
	Pawn blackPawn3 = blackPawn;
	placePiece(&blackPawn3,"d7");
	Pawn blackPawn4 = blackPawn;
	placePiece(&blackPawn4,"e7");
	Pawn blackPawn5 = blackPawn;
	placePiece(&blackPawn5,"f7");
	Pawn blackPawn6 = blackPawn;
	placePiece(&blackPawn6,"g7");
	Pawn blackPawn7 = blackPawn;
	placePiece(&blackPawn7,"h7");
	board[6][2]->print();
	//printBoard();
	//move("c2", "c4");
}

//在给定的位置放置给定的棋子 成功返回true
//如果有自己的棋子 则返回false
//如果有对方的棋子 则捕获对方棋子并返回true
bool ChessBoard::placePiece(ChessPiece* piece, Position position)
{
	if(position == "c2")
	{
		puts("-----------------1");
	}
	mapPosToVirtualIndex::iterator itr = globalMapPosToVirtualIndex.find(position);
	if(itr == globalMapPosToVirtualIndex.end())
		return false;
	if(position == "c2")
	{
		puts("-----------------2");
	}
	SPieceIndex sTmp = itr->second;
	if(board[sTmp.row][sTmp.column] == NULL)
	{
		board[sTmp.row][sTmp.column] = piece;
		piece->setRow(sTmp.row);
		piece->setColumn(sTmp.column);
		if(position == "c2")
		{
			puts("-----------------3");
			printf("===%d=====%d\n",sTmp.row,sTmp.column);
			puts("-wgfsina");
			vector<string> vecResult;
			piece->legalMoves(vecResult);
			vecResult.clear();
			printf("=====[%p]\n",piece);
			board[sTmp.row][sTmp.column]->print();
			board[6][2]->print();
			piece->print();
		}
		
		return true;
	}
	
	ChessPiece* ptr = board[sTmp.row][sTmp.column];
	vector<string> vecResult;
	ptr->legalMoves(vecResult);
	if(ptr->getColor() == piece->getColor())
	{
		vector<string> vecResult;
		piece->legalMoves(vecResult);
		return false;
	}
	else
	{//要问下这个捕获是什么意思  直接替换掉对方的棋子还是按照规则才能替换对方棋子
		board[sTmp.row][sTmp.column] = piece;
		piece->setRow(sTmp.row);
		piece->setColumn(sTmp.column);
		vector<string> vecResult;
		piece->legalMoves(vecResult);
		return true;
	}
	return false;
}

ChessPiece* ChessBoard::getPiece(Position position)
{
	if(globalMapPosToVirtualIndex.find(position) != globalMapPosToVirtualIndex.end())
	{
		SPieceIndex sTmp = globalMapPosToVirtualIndex[position];
		return board[sTmp.row][sTmp.column];
	}
	return NULL;
}

bool ChessBoard::move(Position fromPosition, Position toPosition)
{
	//从位置定位到具体棋子
	cout<<"-----------------"<<endl;
	board[6][2]->print();
	mapPosToVirtualIndex::iterator itr = globalMapPosToVirtualIndex.find(fromPosition);
	if(itr == globalMapPosToVirtualIndex.end())
	{
		//位置范围在a1....a8  h1.....h8 在globalMapPosToVirtualIndex已经映射了 不在这里的位置都不合法
		printf("illegal Position %s\n",fromPosition.c_str());
		return false;
	}
	SPieceIndex sPieceIndex = itr->second;
	ChessPiece* ptr = board[sPieceIndex.row][sPieceIndex.column];
	board[sPieceIndex.row][sPieceIndex.column]->print();
	printf("%d=====%d\n",sPieceIndex.row,sPieceIndex.column);
	if( ptr == NULL)
	{
		//在相应的位置没有棋子 不能执行移动操作
		printf("Position %s does not have a piece,can not move\n",fromPosition.c_str());
		return false;
	}
	else 
	{
		vector<string> vecResult;
		puts("=======================0");
		printf("wgfsina=====[%p]\n",ptr);
		ptr->legalMoves(vecResult);
		puts("=======================1");
		if(vecResult.size() == 0)
		{
			printf("%s can not move,no appropriate Position\n",fromPosition.c_str());
			return false;
		}
		else 
		{	
			int iCount = 0;
			for( ; iCount < vecResult.size(); iCount++)
			{
				if(vecResult[iCount] == toPosition)
				{//可以移动
					break;
				}
			}
			puts("=======================2");
			if(iCount == vecResult.size())
			{//如果遍历到最后都没有发现能移动的 那么iCount大小等于vecResult的大小
				printf("%s can not move,no appropriate Position\n",fromPosition.c_str());
				vecResult.clear();
				return false;
			}
			else 
			{
				puts("=======================3");
				printf("%s can mv,before move the chess board is\n",fromPosition.c_str());
				printBoard();
				printf("after move the chess board is\n");
				SPieceIndex sPieceIndexTmp = globalMapPosToVirtualIndex[toPosition];
				//用fromPostion的棋子替换toPostion的棋子
				board[sPieceIndexTmp.row][sPieceIndexTmp.column] = ptr;
				//替换后修改ptr代表的棋子的坐标
				ptr->setRow(sPieceIndexTmp.row);
				ptr->setColumn(sPieceIndexTmp.column);
				//清除fromPostion位置上的棋子
				board[sPieceIndex.row][sPieceIndex.column] = NULL;
				printBoard();
				vecResult.clear();
				return true;
			}
		}
	}

	return false;
}

void ChessBoard::printBoard()
{
	board[6][2]->print();
	char szTemp[16] = {0};
	for(int i =0 ;i <= BLOCK_SIZE*CHESS_SIZE ; i++)
	{
		for(int j = 0;j<= BLOCK_SIZE*CHESS_SIZE;j++)
		{
			sprintf(szTemp,"%d_%d",i,j);
			if(globalMapRealIndexToPos.find(szTemp) != globalMapRealIndexToPos.end())
			{
				string strPos = globalMapRealIndexToPos[szTemp];
				SPieceIndex sPieceIndex = globalMapPosToVirtualIndex[strPos];
				if(board[sPieceIndex.row][sPieceIndex.column] !=  NULL)
				{
					printf("%s",(board[sPieceIndex.row][sPieceIndex.column]) ->getStrCode().c_str());
				}
				else 
				{
					printf(" ");
				}
			}
			else if( i%BLOCK_SIZE == 0&& j%BLOCK_SIZE == 0)
            {
                    printf("+");
            }
            else if(i%BLOCK_SIZE == 0 && j%BLOCK_SIZE != 0)
            {
                    printf("-");
            }
            else if(j % BLOCK_SIZE == 0 && i % BLOCK_SIZE != 0)
            {
                    printf("|");
            }
            else
            {
                    printf(" ");
            }
		}
		printf("\n");
	}	
}

//判断棋子状态
int ChessPiece::judgePieceStat(int row,int column)
{
	ChessBoard* curChessBoard = getChessBoard();
	if(curChessBoard->board[row][column] == NULL)
	{//此物无棋子可以移动到这里
		return 0;
	}
	
	ChessPiece* ptr = curChessBoard->board[row][column];
	if(ptr->getColor() == getColor())
	{//自己的棋子不能吃
		return 1;
	}
	else
	{//对方的棋子可以移动到这里吃掉
		return 2;
	}
	
	return -1;
}

int Rook::legalMoves(vector<string>& vecResult)
{puts("================Rook");
	//车的行进方向是直行 上下左右四个方向都要判断	
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0};
	
	//先计算row
	for(int i = row + 1 ; i < CHESS_SIZE; i++ )
	{
		iRet = judgePieceStat(i,column);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,column);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	for(int i = row - 1 ; i >= 0 ; i-- )
	{
		iRet = judgePieceStat(i,column);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,column);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	//计算column
	for(int i = column + 1 ; i < CHESS_SIZE; i++ )
	{
		iRet = judgePieceStat(row,i);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",row,i);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	for(int i = column - 1 ; i >= 0 ; i-- )
	{
		iRet = judgePieceStat(row,i);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",row,i);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	return 0;	
}

int Bishop::legalMoves(vector<string>& vecResult)
{puts("================Bishop");
	//象的行走方向是斜着走
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0}; 
	
	//往右上走  行增加  列增加
	for(int i = row + 1 ,j= column + 1;i < CHESS_SIZE && j < CHESS_SIZE; i++,j++)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,j);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
		puts("wgfsina=======================2");
	}
	
	//往左上走  行增加  列变小
	for(int i = row + 1 ,j= column - 1;i < CHESS_SIZE && j >= 0; i++,j--)
	{puts("wgfsina=======================3");
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,j);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	//往左下走  行变小  列变小
	for(int i = row - 1 ,j= column - 1;i >= 0 && j >= 0; i--,j--)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,j);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	//往右下走  行变小  列增大
	for(int i = row - 1 ,j= column + 1;i >= 0 && j < CHESS_SIZE; i--,j++)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{//说明此处没有棋子可以移动到这里
			sprintf(szTemp,"%d_%d",i,j);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{//能移动到这里吃掉对方的棋子 吃掉后就不能继续移动了
				break;
			}
		}
		else 
		{
			break;
		}
	}
	return 0;
}

int Pawn::legalMoves(vector<string>& vecResult)
{
	puts("===================Pawn");
	//兵卒的行进方向是只能直行 并且一次只能走一格 如果在初始位置 则可以走两格
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	SPieceIndex sPieceIndex;
	char szTemp[16] = {0};
	if(getColor() == WHITE)
	{//说明是白方棋子 从下往上走
		//1、判断只走一步是不是能走
		puts("===================come1");
		iRet = judgePieceStat(row + 1,column);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row + 1,column);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 0 && row == 1 /*1是兵卒的初始位置*/)
			{//按照规则 如果在初始位置 且前面没有棋子 则可以继续走二步
				iRet = judgePieceStat(row + 2,column);
				if(iRet == 0 || iRet == 2)
				{
					sprintf(szTemp,"%d_%d",row + 2,column);
					vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
				}
			}
		}		
	}
	else 
	{
		puts("===================come2");
		//说明是黑方棋子 从上往下走
		//1、判断只走一步是不是能走
		iRet = judgePieceStat(row - 1,column);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row - 1,column);
			vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
			if(iRet == 0 && row == 6 /*1是兵卒的初始位置*/)
			{//按照规则 如果在初始位置 且前面没有棋子 则可以继续走二步
				iRet = judgePieceStat(row - 2,column);
				if(iRet == 0 || iRet == 2)
				{
					sprintf(szTemp,"%d_%d",row -2,column);
					vecResult.push_back(globalMapVirtualIndexToPos[szTemp]);
				}
			}
		}
	}
	
	return 0;
}

int Knight::legalMoves(vector<string>& vecResult)
{puts("===================Knight");
	vecResult.clear();
	return 0;
}

int Queen::legalMoves(vector<string>& vecResult)
{puts("===================Queen");
	vecResult.clear();
	return 0;
}

int King::legalMoves(vector<string>& vecResult)
{
	puts("===================King");
	vecResult.clear();
	return 0;
}

int main(int argc,char* argv[])
{
	//由于打印的时候是从左上角开始 人为做映射把棋盘和坐标对应起来 
	globalMapPosToVirtualIndex.clear();
	globalMapVirtualIndexToPos.clear();
	globalMapRealIndexToPos.clear();
	char szTemp[16] = {0};
	char szTemp1[16] = {0};
	SPieceIndex sPieceIndexTemp;
	for(int i= CHESS_SIZE;i > 0; i--)
	{
		for(int j = 'a'; j < 'i'; j++)
		{
			sprintf(szTemp,"%c%d",j,i);
			sPieceIndexTemp.row = CHESS_SIZE - i;
			sPieceIndexTemp.column = j -'a';
			globalMapPosToVirtualIndex.insert(mapPosToVirtualIndex::value_type(szTemp,sPieceIndexTemp));
			sprintf(szTemp1,"%d_%d",CHESS_SIZE - i,j -'a');
			globalMapVirtualIndexToPos.insert(mapVirtualIndexToPos::value_type(szTemp1,szTemp));
			int iRealRow = (CHESS_SIZE - i)*BLOCK_SIZE + BLOCK_SIZE/2;
			int iRealColumn = ( j - 'a')*BLOCK_SIZE + BLOCK_SIZE/2;
			sprintf(szTemp1,"%d_%d",iRealRow,iRealColumn);
			globalMapRealIndexToPos.insert(mapRealIndexToPos::value_type(szTemp1,szTemp));
		}
	}
	
	ChessBoard board;
	board.initialize();
	board.move("c2", "c4");
	
	globalMapPosToVirtualIndex.clear();
	globalMapVirtualIndexToPos.clear();
	globalMapRealIndexToPos.clear();
	return 0;
}
