#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <set>

template<typename T>
class concurrent_queue {
    std::queue<T> queue_;
    std::set<T> set_;
    mutable std::mutex m_;
    std::condition_variable data_cond_;

    concurrent_queue &operator=(const concurrent_queue &) = delete;

    concurrent_queue(const concurrent_queue &other) = delete;

public:
    concurrent_queue() {}

    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            if (set_.find(item) == set_.end()) {
                queue_.push(std::move(item));
                set_.emplace(queue_.back());
            }
        }
        data_cond_.notify_one();
    }

    bool try_and_pop(T &popped_item) {
        std::lock_guard<std::mutex> lock(m_);
        if (queue_.empty()) {
            return false;
        }
        popped_item = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    void clear() {
        std::queue<T> empty;
        std::swap(queue_, empty);
        std::set<T> empty_s;
        std::swap(set_, empty_s);
    }
};

