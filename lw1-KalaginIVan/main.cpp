#include <iostream>
#include <thread>

using namespace std;

void call_from_thread1() {
    std::cout << "Hello, World1" << std::endl;
}

void call_from_thread2() {
    std::cout << "Hello, World2" << std::endl;
}

void call_from_thread3() {
    std::cout << "Hello, World3" << std::endl;
}

int main(int argc, const char * argv[]) {

    if (argc != 3) {
        cout << "Invalid arguments count\n"
             << "Usage: program <thread_count> <iteration_count>\n";
        return 1;
    }

    string inputThreadCount = argv[1];
    string inputIterationCount = argv[2];
    unsigned threadCount, iterationCount;

    if (isdigit(inputThreadCount[0]) && isdigit(inputIterationCount[0])) {
        try {
            threadCount = stoi(inputThreadCount);
            iterationCount = stoi(inputIterationCount);
        }
        catch(...)
        {
            cout << "Invalid arguments type\n" << "Example: program 3 4\n";
        }
    }
    else
    {
        cout << "Invalid arguments type\n" << "Example: program 3 4\n";
    }

    std::thread t1(call_from_thread1);
    std::thread t2(call_from_thread2);
    std::thread t3(call_from_thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;

}
