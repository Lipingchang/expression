//  top 指向的是可以放元素的单元。就是空的单元。
struct stack
{
	SEleType *stack;
	int top;
	int length;			// 该栈最多可以放多少个元素。
};
void WatchStack(stack S)
{
	cout << "WatchStack: " << endl;
	for(int i = 0;i < S.top; i++ )
	{
		cout << i << ": " << S.stack[i] << endl;
	}
	cout << endl;
}
bool push(stack &S,SEleType e)
{
	if(S.top+1>=S.length)  // 等于100个就超了。
	{
		cout << "push fail, no more memory! " << endl;
		return false;
	}
	S.stack[S.top] = e;
	S.top++;
	// cout << "after push " << endl;
	// WatchStack(S);
	return true;
}
void InitStack(stack &S)
{
	S.stack = new SEleType[MAX_LEN];
	if(S.stack == NULL)
	{
		cout << "init stack failed ! " << endl;
		return;
	}
	S.top = 0;
	S.length = MAX_LEN;
}
bool IsEmpty(stack S)
{
	if(S.top == 0)
		return true;
	return false;
}
bool pop(stack &S,SEleType &e)
{
	if( IsEmpty(S) )
	{
		cout << "can't pop a empty stack !" << endl;
		return false;
	}
	
	S.top--;
	e = S.stack[S.top];
	return true;
}
void DestoryStack(stack &S)
{
	if(S.stack != NULL)
		delete [] S.stack;
	S.length = 0;
	S.top = 0;
}

SEleType GetStackTop(stack S)
{
	if(S.top != 0)
		return S.stack[S.top-1];
	cout << "stack is empty, so can't get stack top " << endl;
	exit(1);
}