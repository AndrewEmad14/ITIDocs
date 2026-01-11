#include <iostream>

using namespace std;
/*
dict={
        "name":"mina",
        "age":20
    }
print(dict["name"])
dict["name"]="ali"
print(dict["name"])

*/

class Node {
    public :
    std::string key ;
    std::string value;
    Node * next;
    Node(std::string k, std::string val):key(k), value(val),next(NULL){
        /*this->key=k;
        this->value=val;
        next=NULL;*/
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
    int hashFunction(std::string  key ){
            //string ====> Hash ===> index
            unsigned long int hashValue=0;
            for(char c : key ){
               hashValue=hashValue*31+c;
            }
            return hashValue%size;
    }
    void insert(std::string  key, std::string  value){
        //1- Calculate Index
            int index= hashFunction(key);
        //Check if already exists Key to update Values
            Node * current=table[index];
            while(current != NULL){
                if(current->key == key){
                    current->value=value;
                    return ;
                }
                current=current->next;
            }

        // 2- Create New Node
            Node *newNode=new Node(key,value);
        // 3- next of Me --> Point of Prev
            newNode->next = table[index];
        // 4- Pointer[index] (Head) point of me
            table[index]= newNode;
    }
    std::string search(std::string key ){
        //1- Calculate Index
        int index= hashFunction(key);
        Node * current = table[index];
        while(current!=NULL){
            if (current->key == key){
                return current->value;
            }
            current=current->next;
        }
        return "Key Not found";
    }
    void display( ){
        //1- Calculate Index
        for(int i=0; i<size; i++){
            Node * current = table[i];
            cout<<"index "<< i <<" : "; // Index
            while(current!=NULL){
                cout << current->key<<":"<<current->value<<"  ,  ";
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
    cout<<a.hashFunction("abc")<<endl;//4
    cout<<a.hashFunction("cab")<<endl;
    cout<<a.hashFunction("bac")<<endl;//4
    cout<<a.hashFunction("aaa")<<endl;
    a.insert("name","mina");
    a.insert("abc","ahmed");
    a.insert("bac","mark");
    a.insert("age","30");
    cout<<a.search("name")<<endl;//mina
    cout<<a.search("abc")<<endl;//ahmed
    cout<<a.search("bac")<<endl;//mark
    cout<<a.search("age")<<endl;//30
    a.insert("age","60");
    a.insert("abc","mina");
    cout<<a.search("name")<<endl;//mina
    cout<<a.search("abc")<<endl;//mina
    cout<<a.search("bac")<<endl;//mark
    cout<<a.search("age")<<endl;//60
    a.display();

    cout << "Hello world!" << endl;
    return 0;
}


//Graph
//MergeSort , Quick Sort
