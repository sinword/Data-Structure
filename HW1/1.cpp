#include <iostream>
using namespace std;

template <typename T> class Queue {
    T* arr;
    int cap;
    int count;
    int front;
    int rear;

public:
    Queue() {
        arr = new T[1];
        cap = 1;
        count = 0;
        front = 0;
        rear = -1;
    }

    void push(T data) {
        rear++;
        count++;
        if (count == cap) {
            T* tmp = new T[2 * cap];
            int k = 0;
            for (int i = front; i <= rear; i++) {
                tmp[k] = arr[i];
                k++;
            }
            arr = tmp;
            cap *= 2;
        }
        arr[rear] = data;
    }

    T pop() {
        return arr[front++];
    }

    int size() { return rear - front + 1; }

    T getFront() { return arr[front]; }

    T getBack() { return arr[rear]; }

    bool isEmpty() {
        if (rear < front) {
            return true;
        }
        else {
            return false;
        }
    }
};

struct Customer {
    string name;
    int arrival;
    int t;
    int FT;
};

class Counter {
public:
    Queue<Customer> queue;
    int FT; // Finish time
    int wait;

    Counter() {
        FT = 0;
        wait = 0;
    }
};


int main() {
    int counterNum;
    cin >> counterNum;
    Counter counter[10];
    Customer cus;
    int input = 0;
    // Queue<int> outputCounter;
    while (cin >> cus.name >> cus.arrival >> cus.t) {
        input++;
        cus.FT = cus.arrival + cus.t;

        for (int i = 0; i < counterNum; i++) {
            Counter tmpCnt = counter[i];
            while (!tmpCnt.queue.isEmpty() && tmpCnt.queue.getFront().FT <= cus.arrival) {
                tmpCnt.queue.pop();
            }
            counter[i].wait = tmpCnt.queue.size();
        }
        
        int availCounter = counterNum - 1;
        for (int i = counterNum - 2; i >= 0; i--) {
            
            if (counter[i].wait <= counter[availCounter].wait) {
                availCounter = i;
            }
        }

        counter[availCounter].wait++;
        
        //cout << cus.name << " " << cus.FT << "\n";
        if (cus.arrival > counter[availCounter].FT) {
            counter[availCounter].FT = cus.FT;
        }
        else {
            counter[availCounter].FT += cus.t;
            cus.FT = counter[availCounter].FT;
        }

        counter[availCounter].queue.push(cus);
        
       // outputCounter.push(availCounter);
    }
    int output = 0;
    int outputCounter = 0;
    //int curCounter;
    while (output < input) {
        /*curCounter = outputCounter.pop();
        cus = counter[curCounter].queue.pop();
        cout << cus.name << " " << cus.FT << " " << curCounter << "\n";*/
        int time = 9999;

        for (int i = 0; i < counterNum; i++) {
            
            if (!counter[i].queue.isEmpty() && counter[i].queue.getFront().FT < time) {
                time = counter[i].queue.getFront().FT;
                outputCounter = i;
            }
        }
        output++;
        cus = counter[outputCounter].queue.pop();
        cout << cus.name << " " << cus.FT << " " << outputCounter << "\n";
    }


}

// 3
// John 3 9
// Mr._Brown 4 12
// Alice 6 20
// Jack 9 18
// God 18 22
// GiGi 23 10