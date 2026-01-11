#include <iostream>

using namespace std;

/*
HashTable :
    key data
    Hashing Function
    Table index(Array of Pointer Dyanmic pointer of pointer)
    Handling collision
*/
class Node {
    public :
    int key ;
    Node * next;
    Node(int key){
        this->key=key;
        next=NULL;
    }
};
class HashTable{
    int size;
    // Dynamic Array of Pointers Nodes
    Node ** table;
    public :
    HashTable( int size ){
        this->size=size;
        //Create Array of Pointers
        table = new Node* [size];
        for(int i=0; i<size; i++){
            table[i]=NULL;
        }
    }
    // Key(data)====>HashFunction ====> index
    int hashFunction(int key ){
        int index = key %size;
        return index ;

    }
    void insert(int key){
        //1- Calculate Index
            int index= hashFunction(key);
        // 2- Create New Node
            Node *newNode=new Node(key);
        // 3- next of Me --> Point of Prev
            newNode->next = table[index];
        // 4- Pointer[index] (Head) point of me
            table[index]= newNode;
    }
    bool search(int key ){
        //1- Calculate Index
            int index= hashFunction(key);
        Node * current = table[index];
        while(current!=NULL){
            if (current->key == key){
                return true;
            }
            current=current->next;
        }
        return false;
    }
    void display( ){
        //1- Calculate Index
        for(int i=0; i<size; i++){
            Node * current = table[i];
            cout<<"index "<< i <<" : "; // Index
            while(current!=NULL){
                cout << current->key<<" --> ";
                current=current->next;
            }
            cout <<endl;
          }

    }

    ~ HashTable(){
        //Wait :)
         for(int i=0; i<size; i++){
            Node * current = table[i];
            while(current!=NULL){
                Node * temp = current;
                current=current->next;
                delete temp;
            }
            cout <<endl;
          }
        delete [] table;
    }

};
int main()
{
    HashTable a(10);
    a.insert(15);
    a.insert(10);
    a.insert(115);//Collision
    a.insert(215);//Collision
    a.search(215)? cout<<"Found"<<endl:cout<<"Not Found"<<endl;
    a.search(10)? cout<<"Found"<<endl:cout<<"Not Found"<<endl;
    a.search(115)? cout<<"Found"<<endl:cout<<"Not Found"<<endl;
    a.search(15)? cout<<"Found"<<endl:cout<<"Not Found"<<endl;
    a.search(13)? cout<<"Found"<<endl:cout<<"Not Found"<<endl;
    cout << "Hello world!" << endl;
    a.display();
    return 0;
}
