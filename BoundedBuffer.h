#ifndef BBF_H
#define BBF_H

#include <mutex>
#include <condition_variable>
#include <deque>


template <typename T>
class BoundedBuffer
{
public:
	BoundedBuffer(size_t capacity) :capacity_(capacity) {}
	void Enqueue(const T &item)
	{
		std::unique_lock<std::mutex> lock(mux_);//���� 
		if (queue_.size() >= capacity_)
			return;
		queue_.emplace_back(item);
		cv_.notify_one();//cv_.notify_all(); //������Ϊ�����ԣ�����notify_allû��Ҫ���Ͼ�����һ�ξ�pushһ��Ԫ��
	}
	void Enqueue(T &&item)//��̬���书�ܵĶ����� 
	{
		std::unique_lock<std::mutex> lock(mux_);//���� 
		
		if (queue_.size() >= capacity_)
			return;

		queue_.emplace_back(item);
		cv_.notify_one();//cv_.notify_all();//������Ϊ�����ԣ�����notify_allû��Ҫ���Ͼ�����һ�ξ�pushһ��Ԫ��
	}
	T Dequeue()
	{
		std::unique_lock<std::mutex> lock(mux_);//���� 

		while (queue_.empty())
		{
			cv_.wait(lock);
		}
	
		T tmp(queue_.front());
		queue_.pop_front();
		return tmp;
	}

private:
	std::deque<T> queue_;
	size_t capacity_;
	std::mutex mux_;
	std::condition_variable cv_;
};

#endif
