#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Worker {
    string name;
    string dateStart;
    string dateEnd;
    string post;
    int salary;
};

struct Node {
    Worker worker;
    Node* next;
    Node* prev;
};

struct List {
    Node* start;
    Node* end;
};

void stringToWorker(string& str, Worker& worker) {
    stringstream ss(str);
    ss >> worker.name >> worker.dateStart >> worker.dateEnd >> worker.post >> worker.salary;
}

void swap_workers(Node* worker1, Node* worker2) {
    Worker worker3 = worker1->worker;
    worker1->worker = worker2->worker;
    worker2->worker = worker3;
}

void selectionSort(Node* worker_start, Node* worker_next, Node* worker_min,int min_salary) {
    if (worker_next == nullptr) {
        swap_workers(worker_start, worker_min);
    } else {
        if (worker_next->worker.salary > min_salary) {
            worker_min = worker_next;
            min_salary = worker_next->worker.salary;
        }
        selectionSort(worker_start, worker_next->next, worker_min, min_salary);
    }
}

void printList(List& list) {
    Node* current = list.start;
    while (current != nullptr) {
        cout << current->worker.name << " " 
             << current->worker.dateStart << " "
             << current->worker.dateEnd << " "
             << current->worker.post << " "
             << current->worker.salary << endl;
        current = current->next;
    }
}

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);
    string line;
    getline(file, line);
    Worker worker1;
    stringToWorker(line, worker1);

    List list;
    list.start = new Node{worker1, nullptr, nullptr};
    list.end = list.start;
    while (getline(file, line)) {
        Worker new_worker;
        stringToWorker(line, new_worker);
        Node* new_node = new Node{new_worker, nullptr, list.end};
        list.end->next = new_node;
        list.end = new_node;
    }
    file.close();
    printList(list);
    Node* current = list.start;
    while (current != nullptr) {
        selectionSort(current, current->next, current, current->worker.salary);
        current = current->next;
    }
    cout << "--------------------------------------------------------------------" << endl;
    printList(list);
}