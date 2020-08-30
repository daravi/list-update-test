#pragma once

#include <functional>
#include <thread>
#include <vector>

#include <QDebug>

class Store
{
public:
	Store(const Store& other) = delete;
	Store& operator=(const Store& other) = delete;
	~Store();

	static Store& instance()
	{
		static Store store;

		return store;
	}

	void registerCallback(std::function<void(const std::vector<int>&)> callback);

private:
	Store();
	void workerThread();
	std::vector<std::function<void(const std::vector<int>&)>> m_callbacks;
	std::thread m_worker;
};

Store::Store()
{
	qDebug() << "Here";
	m_worker = std::thread(std::bind(&Store::workerThread, this));
}

Store::~Store()
{
	m_worker.join();
}

void Store::registerCallback(std::function<void(const std::vector<int>&)> callback)
{
	m_callbacks.push_back(std::move(callback));
}

void Store::workerThread()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	m_callbacks[0]({1,1,1,1,1,1}); // update test
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// remove and insert test
	std::vector<int> states;
	for (auto & callback : m_callbacks)
	{
		for (size_t i = 0; i < 10; i++)
		{
			states.push_back(1);
			callback(states);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}