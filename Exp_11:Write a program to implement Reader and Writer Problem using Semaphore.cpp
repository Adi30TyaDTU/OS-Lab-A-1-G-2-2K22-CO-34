
// The Reader-Writer Problem is a classical synchronization problem in concurrent programming. The problem involves multiple readers and writers accessing a shared resource. The constraints are as follows:
// 1. Multiple readers can read the shared resource simultaneously.
// 2. Only one writer can write to the shared resource at a time.
// 3. Readers and writers cannot access the shared resource simultaneously.
// To implement the Reader-Writer Problem using semaphores, we can use two semaphores:
// •	`mutex`: A binary semaphore to control access to the `read_count` variable and ensure mutual exclusion.
// •	`write`: A binary semaphore to control access to the shared resource and ensure that only one writer can write at a time.

// •	The `read` method simulates the behavior of a reader. It acquires the `mutex` to increment `read_count`, reads from the shared resource, and then releases the `mutex` after decrementing `read_count`.
// •	The `write` method simulates the behavior of a writer. It acquires the `write` semaphore to block other writers and readers, writes to the shared resource, and then releases the `write` semaphore.
// •	Multiple reader and writer threads are created and started to simulate concurrent access to the shared resource

#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>

using namespace std;

class ReadersWriters {
private:
    mutex mtx;
    sem_t write_mutex;
    int readers_count;

public:
    ReadersWriters() : readers_count(0) {
        sem_init(&write_mutex, 0, 1);
    }

    void start_read() {
        mtx.lock();
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_mutex);
        }
        mtx.unlock();

        // Reading the shared resource
        cout << "Reader is reading" << endl;

        mtx.lock();
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_mutex);
        }
        mtx.unlock();
    }

    void start_write() {
        sem_wait(&write_mutex);

        // Writing to the shared resource
        cout << "Writer is writing" << endl;

        sem_post(&write_mutex);
    }
};

void reader_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Reading
        rw.start_read();
        // Simulating some delay for reading
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void writer_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Writing
        rw.start_write();
        // Simulating some delay for writing
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main() {
    ReadersWriters rw;

    // Creating reader threads
    thread readers[5];
    for (int i = 0; i < 5; ++i) {
        readers[i] = thread(reader_thread, ref(rw), i);
    }

    // Creating writer threads
    thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer_thread, ref(rw), i);
    }

    // Joining threads
    for (int i = 0; i < 5; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}
