#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<iostream>

using namespace std;

//棋盘中每个棋子的大小 这里设定为3 表示每个棋子占用一个3X3的方格
#define BLOCK_SIZE 3
//棋盘的大小
#define CHESS_SIZE 8

class ChessPiece;
typedef string Position;

typedef struct SPieceIndex{
	int row;
	int column;
}SPieceIndex;

typedef map<Position,SPieceIndex> mapPosToVirtualIndex ;
typedef map<string,string> mapVirtualIndexToPos;
typedef map<string,string> mapRealIndexToPos;

//globalMapPosToVirtualIndex存储的是 a1 h8等到(0,0) (8,8)等虚拟坐标的映射 
//这个虚拟坐标的单位对应BLOCK_SIZE 也就是说 一个格子的长度相当于BLOCK_SIZE个实际打印长度
mapPosToVirtualIndex globalMapPosToVirtualIndex; 

//globalMapvirtualIndexToPos 存储的是(0,0) (8,8)等虚拟坐标到a1 h8等的映射
mapVirtualIndexToPos globalMapVirtualIndexToPos;

//globalMapRealIndexToPos  存储的是每个棋子实际的坐标
mapRealIndexToPos globalMapRealIndexToPos;

class ChessBoard{
public:
	//无参构造函数初始化一个8x8的数组 每个元素都是个棋盘格
	ChessBoard();
public:
	//初始化一个棋盘的开局状态，使用placePiece放置棋子
	void initialize();
	//获得固定位置的棋子
	ChessPiece* getPiece(Position position);
	//在给定的位置放置给定的棋子 成功返回true
	//如果有自己的棋子 则返回false
	//如果有对方的棋子 则捕获对方棋子并返回true
	 bool placePiece(ChessPiece* piece, Position position);
	 
	 //从一个位置到另外一个位置
	 bool move(Position fromPosition, Position toPosition);
	 
	 //打印棋盘
	 void printBoard();
	 string toString();
public: 
	ChessPiece* board[8][8];
};

class ChessPiece{
public:
	enum Color {WHITE, BLACK};
public:
	//设置棋盘属性和颜色
	ChessPiece(ChessBoard* pBoard, Color _color) : board(pBoard),color(_color) 	{}
public:
	//returns the row
	int getRow(){return row;}
	
	//returns the column
	int getColumn(){return column;}
	
	//set the row
	void setRow(int i) { row = i;}
	
	//set the column
	void setColumn(int i) {column = i;}
	
	//get piece color no need for a setColor method because a piece cannot change color.
	Color getColor() {return color;}
	 
	//returns the position of the piece in the format single letter (a..h) followed by a single digit (1..8).
	string getPosition();
	 
	//sets the position of the piece to the appropriate row and column based on the argument 
	//which in the format single letter (a..h) followed by a single digit (1..8)  
	void setPosition(Position position);
	 
	 //will be implemented in the concrete subclasses corresponding to each chess piece
	 //This method returns a string composed of a single character that corresponds to which piece it is
/*
character     piece
----------   -----------
  "\u2654"   white king
  "\u2655"   white queen
  "\u2656"   white rook
  "\u2657"   white bishop
  "\u2658"   white knight
  "\u2659"   white pawn
  "\u265A"   black king
  "\u265B"   black queen
  "\u265C"   black rook
  "\u265D"   black bishop
  "\u265E"   black knight
  "\u265F"   black pawn
*/
	 virtual string toString(){return string("");};
	 
	 //This method will be implemented in the concrete subclasses corresponding to each chess piece. 
	 //This method returns all the legal moves that piece can make based on the rules described above in the assignment
	 virtual int legalMoves(vector<string>& vecResult)
	 {
	 	puts("================base");
	 	vecResult.clear();
	 	return 0;
	 };
	 
	 void setStrCode(string str) {strCode = str;}
	 
	 string getStrCode() {return strCode;}
	
	 ChessBoard* getChessBoard() {return board;}
	 //判断棋盘上给定坐标棋子状态 0 无棋子  1有自己的棋子 2对方的棋子
	 int judgePieceStat(int row,int column);
	 virtual void print(){
		cout<<"ChessPiece"<<endl;
	}
protected:
	ChessBoard* board; // the board it belongs to, default null
	int row; // the index of the horizontal rows 0..7
	int column; // the index of the vertical column 0..7
	Color color; // the color of the piece
	string strCode;
};

//Concrete classes Rook, Knight, Bishop, Queen, King, and Pawn
//Implement each class to extend ChessPiece and override the methods toString and legalMoves. 
//Note that the legalMoves methods of King, Knight, and Queen return an empty vector<string>.

//车 每方2个
class Rook :public ChessPiece{
public:
	Rook(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString(){};
	int legalMoves(vector<string>& vecResult);
};

//象 每方2个
class Bishop :public ChessPiece{
public:
	Bishop(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString();
	int legalMoves(vector<string>& vecResult);	
};

//兵卒 每方8个
class Pawn :public ChessPiece{
public:
	Pawn(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString();
	int legalMoves(vector<string>& vecResult);
	virtual void print(){
		cout<<"Pawn"<<endl;
	}
};

//骑士 马 每方2个
class Knight :public ChessPiece{
public:
	Knight(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString();
	int legalMoves(vector<string>& vecResult);
};

//王后 每方1个
class Queen :public ChessPiece{
public:
	Queen(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString();
	int legalMoves(vector<string>& vecResult);
};

//国王 每方1个
class King :public ChessPiece{
public:
	King(ChessBoard* pBoard,Color _color):ChessPiece(pBoard,_color)
	{
		this->board = pBoard;
		this->color = _color;
	}
public:
	//string toString();
	virtual int legalMoves(vector<string>& vecResult);	
	
};