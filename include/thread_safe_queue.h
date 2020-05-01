#include <queue>

#ifndef QT_WEB_SEARCH_THRED_SAFE_QUEUE_H
#define QT_WEB_SEARCH_THRED_SAFE_QUEUE_H
#include <queue>
#include <set>
#include <Qurl>
template <class T>
class thread_safe_queue {
public:

    thread_safe_queue(): queue_() {

    }

    void push(const T& val) {
        queue_.push(val);
        set_.insert(val);
    }


public:
    std::queue<T> queue_;
    std::set<T> set_;
};

#endif //QT_WEB_SEARCH_THRED_SAFE_QUEUE_H
