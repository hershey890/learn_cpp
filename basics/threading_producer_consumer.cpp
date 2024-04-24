#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <utility>
#include <iostream>
#include <shared_mutex>
#include <condition_variable>
    
using namespace std;
using namespace std::chrono;

/**
 * Implemented using circular buffer that is resized as needed.
 * The underlying vector capacity is only ever increased, never decreased.
 * 
 * todo: there is potentially a bug if start gets too big. depends on how overflow is handled
 */
template<typename T>
class ThreadSafeQueue {
    size_t start = 0;
    size_t buf_len = 0;
    vector<T> buf;
    shared_mutex mtx;

public:
    ThreadSafeQueue() {}
    ThreadSafeQueue(const initializer_list<T>& lst) : buf_len(lst.size()) {
        buf.resize(lst.size());
        buf.resize(buf.capacity());
        copy(lst.begin(), lst.end(), buf.begin());
    }

    void push(const T& elem) {
        unique_lock<shared_mutex> lock(mtx);
        if(++buf_len >= buf.size()) {
            size_t old_size = buf.size();
            buf.resize(buf_len);
            buf.resize(buf.capacity());
            
            if(start + buf_len >= buf.size()) { // if end is before start, shift everything after start forward
                size_t n_incrsd_capacity = buf.size() - old_size;
                for(size_t i=0, j=start+buf_len-1; i<n_incrsd_capacity; i++, j--, start++)
                    swap(buf[j], buf[j + n_incrsd_capacity]);
            }
        }
        buf[(start + buf_len - 1) % buf.size()] = elem;
    }

    T pop() {
        unique_lock<shared_mutex> lock(mtx);
        if(buf_len == 0)
            throw runtime_error("Unable to pop, queue is empty");
        buf_len--;
        return buf[start++ % buf.size()];
    }

    T top() {
        shared_lock<shared_mutex> lock(mtx);
        if(buf_len == 0)
            throw runtime_error("Unable to view top element, queue is empty");
        return buf[start];
    }

    size_t size() {
        shared_lock<shared_mutex> lock(mtx);
        return buf_len;
    }
};

template<typename T>
struct LockableQueue : public queue<T> { 
    mutex mtx;
    condition_variable cond;
    size_t queue_max_len;
    LockableQueue(const size_t& len = 0) : queue_max_len(len) {}
    LockableQueue(const LockableQueue<T>& lq) : queue<T>(lq), queue_max_len(queue_max_len) {}
};

template<typename T>
class Producer {
    LockableQueue<T>& lq;
    vector<float> insertion_schedule;
    vector<T> insertion_elements;
    size_t idx = 0;

    void push(T& elem) {
        cout << "p: " << elem << endl;
        unique_lock lock{lq.mtx};
        lq.cond.wait(lock, [this]() { return lq.size() < lq.queue_max_len; });
        lq.push(elem);
        lock.unlock();
        lq.cond.notify_all();
    }

public:
    Producer(LockableQueue<T>& q, const vector<float>& insertion_schedule, const vector<T>& insertion_elements) : 
        lq(q),
        insertion_schedule(insertion_schedule), 
        insertion_elements(insertion_elements) {}
    
    void operator()() {
        time_point t0 = system_clock::now();
        decltype(t0) t1;
        while(idx < insertion_schedule.size()) {
            t1 = system_clock::now();
            auto diff = duration_cast<seconds>(t1-t0).count();
            if(diff >= insertion_schedule[idx]) 
                push(insertion_elements[idx++]);
        }
    }
};

template<typename T>
void consumer(LockableQueue<T>& q) {
    while(1) {
        unique_lock lock{q.mtx};
        q.cond.wait(lock, [&q]() { return q.size(); });
        T data = q.front();
        q.pop();
        lock.unlock();
        q.cond.notify_all();
        cout << "c: " << data << endl;
    }
}

int main() {
    /* Thread Safe Queue */
    ThreadSafeQueue<int> q {1,2,3,4,5};
    q.push(6);
    cout << q.size() << endl;
    while(q.size())
        cout << q.pop() << " ";
    cout << endl;
    q.push(7);
    q.push(8);
    q.push(9);
    q.pop();
    q.push(10);
    while(q.size())
        cout << q.pop() << " ";
    cout << endl;

    /* Producer Consumer Queue */
    LockableQueue<int> lq(4);
    lq.push(1);
    lq.push(2);
    lq.push(3);
    lq.push(4);
    vector<float> insertion_schedule {0.7, 1.4, 2.1, 2.8, 3.5, 4.2};
    vector<int> elems {-1, -2, -3, -4, -5, -6};

    jthread prod {Producer<int>(lq, insertion_schedule, elems)};
    jthread cons {consumer<int>, ref(lq)};
    
    return 0;
}