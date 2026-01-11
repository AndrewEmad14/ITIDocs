# Basic Data structs and algorithms

    DS:
    linked list
    doubly linked list
    Stack
    Queue / circular Queue / Priority Queue
    Tree bst , aval , redblacktree
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

# binary search Tree
    class Node
    {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int data)
        {
            this->data = data;
            left = NULL;
            right = NULL;
        }
        ~Node()
        {
        }
    };
    class Tree{
        Node *Tree;
        public:
           void add(int data)
            {
                // Create Node
                Node *newNode = new Node(data); // newNode->data=data;
                // Build Connections
                // Tree Empty No Root
                if (root == NULL)
                {
                    root = newNode;
                }
                // Tree Empty Not Empty
                else
                {
                    Node *current = root; // Jump
                    Node *parent = NULL;  // Jump-1
                    while (current != NULL)
                    {
                        parent = current; // root
                        if (data > current->data)
                        {
                            current = current->right; //
                        }
                        else
                        {
                            current = current->left; //
                        }
                    }
                 
                    if (data > parent->data)
                    {
                        parent->right = newNode;
                    }
                    else
                    {
                        parent->left = newNode;
                    }
                }
            }
            void removeNode(int data)
            {
                // Step 1: Find the node to delete
                Node *current = getNodeByData(data);
                if (current == NULL) {
                    return; // Node not found
                }
                
                // Step 2: Handle root deletion separately
                if (current == root) {
                    root = handleRootDeletion(root);
                    delete current;
                    return;
                }
                
                // Step 3: Handle non-root deletion
                Node *parent = getParent(current);
                Node *replacement = getReplacementNode(current);
                
                // Link parent to replacement node
                if (current->data > parent->data) {
                    parent->right = replacement;
                } else {
                    parent->left = replacement;
                }
                
                delete current;
            }

            private:
                // Helper: Get replacement node for deletion
                Node* getReplacementNode(Node *node)
                {
                    // Case 1: Leaf node (no children)
                    if (node->left == NULL && node->right == NULL) {
                        return NULL;
                    }
                    
                    // Case 2: Only right child
                    if (node->left == NULL) {
                        return node->right;
                    }
                    
                    // Case 3: Only left child
                    if (node->right == NULL) {
                        return node->left;
                    }
                    
                    // Case 4: Two children
                    // Strategy: Use left subtree as replacement,
                    // attach right subtree to rightmost node of left subtree
                    Node *leftSubtree = node->left;
                    Node *rightmost = getMaxRight(leftSubtree);
                    rightmost->right = node->right;
                    
                    return leftSubtree;
                }
                
                // Helper: Handle root deletion
                Node* handleRootDeletion(Node *root)
                {
                    // Case 1: Root is only node
                    if (root->left == NULL && root->right == NULL) {
                        return NULL;
                    }
                    
                    // Case 2: Root has only right child
                    if (root->left == NULL) {
                        return root->right;
                    }
                    
                    // Case 3: Root has only left child
                    if (root->right == NULL) {
                        return root->left;
                    }
                    
                    // Case 4: Root has two children
                    // Use left subtree as new root,
                    // attach right subtree to rightmost of left subtree
                    Node *newRoot = root->left;
                    Node *rightmost = getMaxRight(newRoot);
                    rightmost->right = root->right;
                    
                    return newRoot;
                }
                 Node *getMaxRight(Node *current)
                {
                    if (current == NULL)
                    {
                        return NULL;
                    }
                    while (current->right != NULL)
                    {
                        current = current->right;
                    }
                    return current;
                }
                //inorder traversal
                void LDRRecursive(Node *node)
                {
                    if (node == NULL) {
                        return;
                    }
                    
                    // L: Traverse left subtree
                    LDRRecursive(node->left);
                    
                    // D: Process current node (print data)
                    cout << node->data << " ";
                    
                    // R: Traverse right subtree
                    LDRRecursive(node->right);
                }
                //preorder
                void DLRRecursive(Node *node) 
                { 
                    if (node == NULL) { 
                        return; 
                    } 
                    
                    // D: Process current node (print data) 
                    cout << node->data << " "; 
                    
                    // L: Traverse left subtree 
                    DLRRecursive(node->left);  
                    
                    // R: Traverse right subtree 
                    DLRRecursive(node->right); 
                }
                //postorder
                void LRDRecursive(Node *node) 
                { 
                    if (node == NULL) { 
                        return; 
                    } 
                    
                
                    
                    // L: Traverse left subtree 
                    LRDRecursive(node->left);  
                    
                    // R: Traverse right subtree 
                    LRDRecursive(node->right);
                // D: Process current node (print data) 
                    cout << node->data << " "; 
                }
                void BFS()
                {
                    if (root == NULL) {
                        return;
                    }
                    
                    queue<Node*> q;
                    q.push(root);
                    
                    cout << "BFS (Level-order): ";
                    
                    while (!q.empty()) {
                        // Get front node
                        Node *current = q.front();
                        q.pop();
                        
                        // Process current node
                        cout << current->data << " ";
                        
                        // Add left child to queue
                        if (current->left != NULL) {
                            q.push(current->left);
                        }
                        
                        // Add right child to queue
                        if (current->right != NULL) {
                            q.push(current->right);
                        }
                    }
                    
                    cout << endl;
                }
                
                Node *getParent(Node *current)
                {
                    // Node * current =getNodeByData(data);
                    // current = root;
                    if (current == root)
                    {
                        return NULL;
                    }
                    if (current != NULL)
                    {
                        Node *parent = root;
                        while (parent != NULL)
                        {
                            if (parent->left == current || parent->right == current)
                            {
                                return parent;
                            }
                            else
                            {
                                // JUMP
                                if (current->data > parent->data)
                                {
                                    parent = parent->right;
                                }
                                else
                                {
                                    parent = parent->left;
                                }
                            }
                        }
                    }
                    return NULL;
                }



    };
# hashtable
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
# merge sort 
    void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[]
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
    }


    void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
    }

