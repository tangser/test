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
		std::unique_lock<std::mutex> lock(mux_);//加锁 
		if (queue_.size() >= capacity_)
			return;
		queue_.emplace_back(item);
		cv_.notify_one();//cv_.notify_all(); //个人以为都可以，但是notify_all没必要，毕竟这里一次就push一个元素
	}
	void Enqueue(T &&item)//动态分配功能的对象用 
	{
		std::unique_lock<std::mutex> lock(mux_);//加锁 
		
		if (queue_.size() >= capacity_)
			return;

		queue_.emplace_back(item);
		cv_.notify_one();//cv_.notify_all();//个人以为都可以，但是notify_all没必要，毕竟这里一次就push一个元素
	}
	T Dequeue()
	{
		std::unique_lock<std::mutex> lock(mux_);//加锁 

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
