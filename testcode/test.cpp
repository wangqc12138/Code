#include<stdio.h>
#include<stdlib.h>
#include<iostream>

class A{
public:
	A(int xx,int yy):x(xx),y(yy) {}
public:
	int x;
	int y;
public:
	virtual int print_fun()
	{
		puts("================a");
		return 0;
	}

};

class B :public A
{
public:
	B(int c,int d):A(c,d)
	{
		this->x = c;
		this->y = d;
	}
public:
	int print_fun()
	{
		puts("================b");
		return 0;
	}
};

class C 
{
public:
	C()
	{
		for(int i =0 ;i < 2;i++)
			for(int j = 0; j < 2;j ++ )
		{
			m_global[i][j] = NULL;
		}
	}
public:
	int pass(A* ptr)
	{
		m_global[0][0] = ptr;
		return 0;
	}
	int init()
	{
		B xB(3,4);
		pass(&xB);
		return 0;
	}
	
	int print()
	{
		for(int i = 0; i < 2;i++)
			for(int j = 0; j < 2; j++)
		{
			printf("==============[%d][%d]\n",i,j);
			if(m_global[i][j] != NULL)
			{
				printf("---------========------%d\n",i);
				A* ptr = m_global[i][j];
				ptr->print_fun();
			}
			else 
			{
				printf("---------========[%d][%d]\n",i,j);
			}
		}
		return 0;
	}
public:
	A*  m_global[2][2];
};

int main()
{
	C cc;
	cc.init();
	cc.print();
	return 0;
}

