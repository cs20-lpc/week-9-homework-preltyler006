#include <iostream>
#include <cstdlib>
#include <ctime>
#include "QueueFactory.hpp"
using namespace std;

void simulateTicketCounter() {
    cout << "=== Simulation 1: Ticket Counter (ArrayQueue, cap = 10) ===" << endl;
    Queue<int>* q = QueueFactory::GetQueue<int>(10);
    srand(static_cast<unsigned>(time(nullptr)));

    int turnedAway = 0;
    for (int i = 0; i < 100; ++i) {
        int r = rand() % 3 - 1; // -1, 0, or 1
        try {
            if (r < 0) q->dequeue();   // customer served
            else q->enqueue(1);        // new customer arrives
        } catch (string& e) {
            if (e.find("full") != string::npos)
                turnedAway++;
        }
    }

    cout << "Queue length: " << q->getLength() << endl;
    cout << "Customers turned away: " << turnedAway << endl;
    delete q;
    cout << endl;
}

void simulateBankLine() {
    cout << "=== Simulation 2: Bank Service Line (LinkedQueue) ===" << endl;
    Queue<int>* q = QueueFactory::GetQueue<int>(); // linked queue (no limit)
    srand(static_cast<unsigned>(time(nullptr)) + 100);

    for (int i = 0; i < 100; ++i) {
        int r = rand() % 4 - 1; // -1, 0, 1, 2
        try {
            if (r < 0) q->dequeue();   // served customer
            else q->enqueue(1);        // new customer
        } catch (string& e) {
            // no capacity limit, so no turn-aways expected
        }
    }

    cout << "Final queue length: " << q->getLength() << endl;
    delete q;
    cout << endl;
}

int main() {
    simulateTicketCounter();
    simulateBankLine();
    return 0;
}
