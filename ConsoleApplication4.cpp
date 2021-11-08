#include <iostream>
#include "BoundedBuffer.h"
using namespace std;
class myc
{
public:
	myc(int i) :m_i(i) {}
	int m_i;
};
int main() {

	if (1)
	{
		BoundedBuffer<myc> bb(10);
		bb.Enqueue(5);
		cout << bb.Dequeue().m_i<< endl;
		for (int i = 0; i < 11; i++)
		{
			myc mc(i); bb.Enqueue(mc);//Enqueue(T &item)
			//bb.Enqueue(i);//Enqueue(T &&item)
		}
		for (int i = 0; i < 12; i++)
		{
			cout << bb.Dequeue().m_i << endl;
		}
	}
	else
	{
		BoundedBuffer<int> bb(10);
		bb.Enqueue(5);
		cout << bb.Dequeue() << endl;
		for (int i = 0; i < 11; i++)
		{
			bb.Enqueue(i);
		}
		for (int i = 0; i < 12; i++)
		{
			cout << bb.Dequeue() << endl;
		}

	}
	
	
	return 0;
}

