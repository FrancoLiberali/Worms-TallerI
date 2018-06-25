#ifndef _QUEUE_H
#define _QUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>

/**
* @template Queue
* Template de una cola bloqueante
*/

template<class T>
class Queue {
 private:
  std::queue<T> q;

  std::mutex mtx;
  std::condition_variable cv;

 public:
  Queue() {}
  bool empty() {
    std::unique_lock<std::mutex> lck(mtx);
    return q.empty();
  }
  void push(const T &val) {
    std::unique_lock<std::mutex> lck(mtx);
    if (q.empty()) {
      cv.notify_all();
    }
    q.push(val);
  }

  T pop() {
    std::unique_lock<std::mutex> lck(mtx);
    while (q.empty()) {
      cv.wait(lck);
    }

    const T val = q.front();
    q.pop();

    return val;
  }

 private:
  Queue(const Queue &) = delete;
  Queue &operator=(const Queue &) = delete;
};

#endif