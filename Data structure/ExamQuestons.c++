#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {

    
    
public:
    Node<T>* head;
    Node<T>* tail;
    int size;
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    void pushFront(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    void pushBack(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    void popFront() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }
    
    void popBack() {
        if (!tail) return;
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }
    
    void insert(int pos, T val) {
        if (pos <= 0) {
            pushFront(val);
            return;
        }
        if (pos >= size) {
            pushBack(val);
            return;
        }
        
        Node<T>* newNode = new Node<T>(val);
        Node<T>* curr = head;
        for (int i = 0; i < pos; i++) {
            curr = curr->next;
        }
        
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
        size++;
    }
    
    void remove(int pos) {
        if (pos < 0 || pos >= size) return;
        if (pos == 0) {
            popFront();
            return;
        }
        if (pos == size - 1) {
            popBack();
            return;
        }
        
        Node<T>* curr = head;
        for (int i = 0; i < pos; i++) {
            curr = curr->next;
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
    }
    
    T get(int pos) const {
        if (pos < 0 || pos >= size) {
            throw out_of_range("Index out of bounds");
        }
        Node<T>* curr = head;
        for (int i = 0; i < pos; i++) {
            curr = curr->next;
        }
        return curr->data;
    }
    
    void display() const {
        Node<T>* curr = head;
        cout << "Forward: ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    
    void displayReverse() const {
        Node<T>* curr = tail;
        cout << "Reverse: ";
        while (curr) {
            cout << curr->data << " ";
            curr = curr->prev;
        }
        cout << endl;
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const {
        return size == 0;
    }
    
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
    
};
Node<int>* findInsertionPostion(DoublyLinkedList<int>& list,int data){
    Node<int>* current = list.head;
    while(current != nullptr){
        if(current->data>=data){
            return current;
        }else{
            current = current->next;
        }
    }
    return nullptr;
}

void insertSorted(DoublyLinkedList<int>& list ,int data){
    Node<int>* correctPostion = findInsertionPostion(list,data);
    Node<int>* newNode = new Node<int>(data);
    Node<int>* tail = list.tail;
    Node<int>* head = list.head;
    if(correctPostion == nullptr){
        newNode->prev =  tail;
        tail->next = newNode;
        tail = newNode;
    }else if(correctPostion == head){
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }else{
        newNode->next = correctPostion;
        newNode->prev = correctPostion->prev;
        correctPostion->prev->next = newNode;
        correctPostion->prev = newNode;
    }


}

// Example usage
int main() {
    DoublyLinkedList<int> list;
    
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushFront(4);
    insertSorted(list,5);
    
    list.display();           // Fward: 5 10 20 30
  
    
     insertSorted(list,10);
     insertSorted(list,6);
    list.display();           // Forward: 5 10 15 20 30
    
    list.remove(1);
    list.display();           // Forward: 5 15 20 30
    
    cout << "Element at index 2: " << list.get(2) << endl;
    cout << "List size: " << list.getSize() << endl;
    
    return 0;
}