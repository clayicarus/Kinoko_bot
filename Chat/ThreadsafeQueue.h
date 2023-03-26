//
// Created by clay on 3/10/23.
//

#ifndef ATRI_THREADSAFEQUEUE_H
#define ATRI_THREADSAFEQUEUE_H

#include <mutex>

template<typename T>
class ThreadsafeQueue {
public:
    ThreadsafeQueue() = default;
    ThreadsafeQueue(const ThreadsafeQueue&);
    ThreadsafeQueue& operator=(const ThreadsafeQueue&) = delete;

    std::deque<T> &deque() { return q_; }
    std::mutex &mutex() { return m_; }

    void push(T value);

    bool tryPop(T &value);

    void waitAndPop(T &value);

    bool empty() const;
private:
    std::deque<T> q_;
    std::mutex m_;
};

#endif //ATRI_THREADSAFEQUEUE_H
