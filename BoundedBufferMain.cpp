#include "BoundedBuffer.h"
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

class Producer
{
public:
	Producer(BoundedBuffer<int> *p, int n, int t) :m__pBuffer(p), m_Note(n),m_Times(t)
	{

	}

	int operator ()()
	{
		for (int i=0; i<m_Times;i++)
		{
			int x = m_Note * 100 + i;
			stringstream ss;
			ss << " Producer " << m_Note << " Enqueue " << x << endl;
			cout << ss.str();
			m__pBuffer->Enqueue(x);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}

		return 0;
	}

private:
	BoundedBuffer<int> * m__pBuffer;
	int m_Note;
	int m_Times;
};



class Consumer
{
public:
	Consumer(BoundedBuffer<int> *p, int n, int t) :m__pBuffer(p), m_Note(n), m_Times(t)
	{

	}

	int operator ()()
	{
		for (int i = 0; i < m_Times; i++)
		{
			int x = m__pBuffer->Dequeue();
			stringstream ss;
			ss << " Consumer " << m_Note << " Dequeue " << x << endl;
			cout << ss.str();
			std::this_thread::sleep_for(std::chrono::milliseconds(1200));
		}

		return 0;
	}

private:
	BoundedBuffer<int> * m__pBuffer;
	int m_Note;//标记对象 
	int m_Times;//循环控制次数 
};

int main()
{
	BoundedBuffer<int> *pb = new BoundedBuffer <int>(10);

	Producer p1(pb, 1, 10), p2(pb, 2, 10), p3(pb, 3, 10), p4(pb,4,10);
	std::thread sp1(p1), sp2(p2), sp3(p3), sp4(p4);

	Consumer c1(pb, 1, 15), c2(pb, 2, 15);
	std::thread sc1(c1), sc2(c2);

	sp1.join();
	sp2.join();
	sp3.join();
	sp4.join();
	
	sc1.join();
	sc2.join();

	char ch;
	cin >> ch;
	delete pb;
	return 0;
}
