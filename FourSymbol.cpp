//  只能输入 一位数的数字、

#include <iostream>
#include <fstream>
#define TABLE_FILE "order.txt"
#define N 10 			// 这个是符号优先级table的大小。
using namespace std;
#define MAX_LEN 100    	// 栈最大容量
typedef int SEleType;	// 栈里面的基本元素类型。
#include "STACK.h"

char table[N][N];  // 这张表用来放符号之间的优先级。

int SymbolNum(char c)  // 返回一个符号对应的序号，table[1][1] 意思是 table[+][+]的运算优先级关系。
{
	for(int i = 1; i <= (int)table[0][0]; i++)
	{
		if(table[0][i] == c)
		{
			return i;
		}
	}
	return 0;
}
void InitSymbolOrder(void)   // 从文件里面读入 符号的优先级的表。
{
	ifstream in(TABLE_FILE);
	if(!in.is_open())
	{
		cout << "can't open " << TABLE_FILE << endl;
		exit(0); 
	}
	string symbol,buff;
	getline(in,symbol);
	table[0][0] = symbol.length();
	for(int i = 1; i <= symbol.length(); i++ )
	{
		table[0][i] = symbol[i-1];
		table[i][0] = symbol[i-1];
		getline(in,buff);
		for(int j = 1; j<=symbol.length(); j++)
			table[i][j] = buff[j-1];
	}

	cout << "symbol order: " << endl;
	cout << (int)table[0][0];
	for(int i = 0; i <= symbol.length(); i++)
	{
		for(int j= 0; j <= symbol.length(); j++)
			cout << table[i][j];
		cout << endl;
	}
	cout << endl;
	in.close();
}
char judge(char a, char b)
{
	return table[SymbolNum(a)][SymbolNum(b)];
}

int calculate(int a, char sy, int b)
{
	cout << "calculate: " << a << sy << b << endl;
	switch(sy)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			cout << "function: calculate: can't work with >" << sy << "< " << endl;
			exit(1);
	}
}

bool isnum(char c)
{
	if(c >='0' && c <= '9')
		return true;
	return false;
}

int dodo(void)
{
	
	// cout << SymbolNum('+');
	// cout << SymbolNum('-');
	// cout << SymbolNum('*');
	// cout << SymbolNum('#');
	// cout << SymbolNum('/');
	
	// cout << judge('+','+') << endl;
	// cout << judge('+','-') << endl;
	// cout << judge('+','*') << endl;
	// cout << judge('+','/') << endl;
	// cout << judge('+','#') << endl;

	cout << "enter your expression: ";

	stack num,symbol;
	InitStack(num);		// 操作数
	InitStack(symbol);	// 操作符

	string input;	// 放表达式的；
	cin >> input;
	input+="#";
	int c = 0;		// c指向input中的一个字符

	push(symbol,'#');	
	while( !IsEmpty(symbol) )		//  在所有符号不出错的情况下，最后一个#会把前面所有的符号都出栈后计算。那么最后的时候，符号栈里面肯定是没有东西的。
	{
		if( isnum(input[c]) )		// 数字，就入操作数栈。
		{
			push(num,input[c]-'0');
			c++;
		}
		else						// 是一个操作符，
		{
			switch(judge(GetStackTop(symbol),input[c])) // 判断一下和之前的操作符的优先级关系。
			{
				case '>':						// 前面的操作符的优先级高，那么就计算前面两个数字，和前面的那个操作符的结果，然后把结果压回去
				{								// 这个选项 不会把c给加一的。因为要一直向前面.
					int a,b,sy;
					pop(num,b); pop(num,a);
					pop(symbol,sy);
					push(num,calculate(a,sy,b));
					break;
				}
				case '<':						// 说明 当前的操作符的优先级高，所以要先算当前的操作符相邻的两个操作数，那么只能先把当前的操作数给保存起来，读入下个操作数之后，下个操作符之后再做判断。
				{
					push(symbol,input[c]);
					c++;
					break;
				}
				case '=':						// 只有当前后”(,)“ 括号相遇的时候，表示这两个括号里面的内容已经被算完了，就只有一个数字了，所以把这个两个符号弹出就好了，
				{								// 还有一种是前后的两个“##"相遇的时候，那么说明表达式处理完了，那么弹出就好了。就会产生出退出while的条件。
					int tmp;
					pop(symbol,tmp);
					c++;
					break;
				}
				case '!':						// 括号不匹配的情况，
				{
					cout << " the number of your '(' and ')'  is not match" << endl;
					exit(1);
				}
				

			}

		}
	}
	cout << "result: " <<  GetStackTop(num) << endl;

	return 0;
}

int main()
{
	InitSymbolOrder();
	while(1)
	{
		dodo();
	}
}
