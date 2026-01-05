# Basic Data structs and algorithms

    DS:
    linked list
    doubly linked list
    Stack
    Queue / circular Queue / Priority Queue
    Tree
    HashTable
    min heap max heap
    set

    Algo:
    Linear search
    binary search
    bubble sort
    insertion sort
    selection sort
    merge sort
    quick sort
    graph
    recursions
   
    traversals
        dfs
            Inorder
            Preorder
            Postorder
        bfs
            Level order 

# linked list
                            //the linked list could have a next a prev or both
    class Node
    {
        public:
        int data;
        Node *next;
        Node *prev;
        Node(int val);
        Node();
        int getData() const;
        Node *getNext() const;
        Node *getPrev() const;
        void setNext(Node *nxt);
        void setPrev(Node *prv);
    };
                                                //the linked list can have a head, a tail or both
    class CustomLinkedList
    {
        Node *head;
        Node *tail;

        public:
        CustomLinkedList();
        // add data to the end of the linked list
        bool add(int data);
        
    }
    //add at the end
    bool CustomLinkedList::add(int data)
    {
        Node *newNode = new Node(data);
        // if head is null (meaning list is empty) then make head and tail point to newNode
        // there is no previous node or next node
        if (!head)
        {
            head = newNode;
            tail = newNode;
            return true;
        }
        // link the newNode to the end of the list by doing three steps:
        // 1. make current tail's next point to newNode
        // 2. make newNode's previous point to current tail
        // 3. update tail to point to newNode

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        return true;
    }
    //insert at index
    bool CustomLinkedList::insertAfterByIndex(int index, int data)
    {
        if (head == nullptr || index < 0)
            return false;
        Node *temp = getNode(index);
        if (temp == nullptr)
            return false;
        Node *newNode = new Node(data);
        // Connect newNode to temp's next
        newNode->prev = temp;
        newNode->next = temp->next;
        // Update temp's next to point to newNode
        temp->next = newNode;
        // If there was a node after temp, update its prev pointer
        if (newNode->next != nullptr)
        {
            newNode->next->prev = newNode;
        }
        else
        {
            // We inserted at the end, so update tail
            tail = newNode;
        }

        return true;
    }

    //remove index
        bool CustomLinkedList::removeAt(int index)
    {
        if (head == nullptr || index < 0)
            return false;

        Node *temp = getNode(index);
        if (temp == nullptr)
            return false;
        // Update previous node's next pointer (or head if no previous)
        if (temp->prev != nullptr)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Removing head
        }

        // Update next node's prev pointer (or tail if no next)
        if (temp->next != nullptr)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Removing tail
        }
        delete temp;
        return true;
    }

# Stack / Queue
    its the same as the linked list but you will keep
    track of either the head or the tail , you will be removing from one end either the head or the tail and constantly changing the head or the tail

# binary Search
    int binarySearch(int arr[], int n, int target) {
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target)
                return mid;          // element found
            else if (arr[mid] < target)
                left = mid + 1;      // search right half
            else
                right = mid - 1;     // search left half
        }

        return -1; // element not found
    }

    basically bs is impossible in linke list since it requries random access , althought there are somework arounds it would still lead to a linear search complexity

# swapping linked list
    // swaping solves a lot of stuff when applying different sorting algorithms

    //first we check the order since the algorithm below depends on the order in the linked list

    bool SortManager::isOrderCorrect(CustomLinkedList &list, Node *index1, Node *index2)
    {
    Node *temp = list.getHead();
    
    // here i simply see who would i find first
    if i find index 1 first then i am on the right track , if i find index2 first on the other hand
    then the order is wrong


    while (temp != nullptr)
    {
        if (temp == index1)
        {
            return true;
        }
        else if (temp == index2)
        {

            return false;
        }
        temp = temp->next;
    }
    return false;

    }

    //Now we start swaping

    void SortManager::swapNode(CustomLinkedList &list, Node *index1, Node *index2)
    {
        // first we check, if we have any nulls we return 

        if (index1 == nullptr || index2 == nullptr || index1 == index2)
            return;

        // confirming order of nodes , index1 comes before index2
        if (!isOrderCorrect(list, index1, index2))
        {
            //if the order is not correct we just change the indexes so we can work with them

            Node *tempNode = index1;
            index1 = index2;
            index2 = tempNode;
        }

        // Store surrounding nodes note that this will change according to how many connections you have for each node

        Node *index1Prev = index1->prev;
        Node *index1Next = index1->next;
        Node *index2Prev = index2->prev;
        Node *index2Next = index2->next;

        //we check if the nodes are next to each other
        because i need to know if i will have to do the extra work of reconnecting the adjacent nodes or not

        bool areAdjacent = (index1->next == index2);

        // dealing with surrounding nodes

        //if there is no prev i am trying to swap the head
        otherwise index1 prev next should point at index2

        if (index1Prev != nullptr)
        {
            index1Prev->next = index2;
        }
        else
        {
            list.setHead(index2);
        }

        //if there next is null then i am trying to swap the tail

        otherwise index2 next prev should point at index1

        if (index2Next != nullptr)
        {
            index2Next->prev = index1;
        }
        else
        {
            list.setTail(index1);
        }

        // if nothing in between then i dont need to worry about any more connections

        index1 connection should be index2 connections
        index 2 connections should be index 1 connections

        if (areAdjacent)
        {

            index2->prev = index1Prev;
            index1->prev = index2;
            index1->next = index2Next;
            index2->next = index1;
        }
        else
        {
            // in between elements
            now we have to manage index1 and index2 connections + index1 and index2 inbetween  connections
            
            index2->prev = index1Prev;
            index1->prev = index2Prev;
            index1->next = index2Next;
            index2->next = index1Next;
            index2Prev->next = index1;
            index1Next->prev = index2;
        }
    }

# Bubble sort 
    // this is the bubble sort algorithm done with a linked list

    void SortManager::bubbleSort(CustomLinkedList &list)
    {
        // checks if the list is null

        if (list.getHead() == nullptr)
            return;
        
        // the way to implement the nested is to do two 
        nodes both loops on the list

        Node *outerCurrent = list.getHead();
        bool swapPreformed = true; //if false then the list is sorted
        while (outerCurrent && swapPreformed)
        {
            swapPreformed = false;

            // each time the node starts from the begining
            Node *innerCurrent = list.getHead();

            // compare innercurrent and innercurrent->next

            while (innerCurrent && innerCurrent->next)
            {
            
                if (innerCurrent->data > innerCurrent->next->data)
                {
                    //i want to store the current next so 
                    i dont lose it when swapping

                    Node *nextNode = innerCurrent->next;
                    swapNode(list, innerCurrent, nextNode);
                    swapPreformed = true;
                    innerCurrent = nextNode; 
                    
                    // Continue from swapped position
                }
                else
                {
                    innerCurrent = innerCurrent->next;
                }
            }
            outerCurrent = outerCurrent->next;
        }
    }


# Selction sort
    // same idea with bubble sort but we find min and take it to the back
    void SortManager::selectionSort(CustomLinkedList &list)
    {
        if (list.getHead() == nullptr)
            return;

        Node *outerCurrent = list.getHead();

        while (outerCurrent)
        {
            Node *minNode = outerCurrent;
            Node *innerCurrent = outerCurrent->next;
            while (innerCurrent)
            {
                if (minNode->data > innerCurrent->data)
                    minNode = innerCurrent;

                innerCurrent = innerCurrent->next;
            }
            Node *nextNode = outerCurrent->next;
            swapNode(list, minNode, outerCurrent);
           
            outerCurrent = nextNode;
        }
    }

# insertion sort

    // insertion sort is a bit different , we arent swaping 
    which is a good thing for the linked list actually its the best kinda of sort after merge sort

    void SortManager::insertionSort(CustomLinkedList &list)
    {
        if (list.getHead() == nullptr)
            return;

        Node *outerCurrent = list.getHead();
        outerCurrent = outerCurrent->next;

        // the way this works is we detach our card (node) and
        then we insert it in the list , if i am smaller than the head then i insert before the head otherwise i insert after 

        while (outerCurrent)
        {
            Node *key = outerCurrent;
            Node *nextNode = outerCurrent->next;
            Node *innerCurrent = outerCurrent->prev;
            list.detach(key); // this detaches but doesnt delete

            // we know the node supposed position when we either reach the end of the list OR find the first Node that is smaller than it

            while (innerCurrent && innerCurrent->data > key->data)
                innerCurrent = innerCurrent->prev;

            //now that we have the postion of insertion we ask a couple of questions
            //am i Null? then i should be before the head
            // else i should insert after

            if (innerCurrent == nullptr)
            {
                list.insertBeforeByNode(list.getHead(), key);
            }
            else
            {
                list.insertAfterByNode(innerCurrent, key);
            }
        
            outerCurrent = nextNode;
        }
    }
