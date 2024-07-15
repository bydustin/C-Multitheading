#include <iostream>
#include <thread>
#include <condition_variable>
#include <stdint.h>
#include <functional>

// Printing all natural numbers from 1 to 100 through the use of 2 threads.


const int MAX_NUMBER = 100;

std::mutex mtx;
std::condition_variable cv;
int currentNumber = 1;

void printNumbers(int threadId)
{
    while (true)
    {
        if (currentNumber > MAX_NUMBER)
        {
            break;
        }
        std::unique_lock<std::mutex> lock(mtx);
        if ((threadId == 0 && (currentNumber % 2 == 0)) || (threadId == 1 && (currentNumber % 2 == 1)))
        {
            std::cout << "Thread: " << threadId << ": " << currentNumber << std::endl;
            currentNumber++;
            cv.notify_all();
        }
        else
        {
            cv.wait(lock);
        }

    }
}

int main()
{
    std::thread OddThread(printNumbers, 0);
    std::thread EvenThread(printNumbers, 1);

    OddThread.join();
    EvenThread.join();

    return 0;
}
