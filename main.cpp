
#include <iostream>
#include <fstream>

using namespace std;


//************************* NODE CLASS *******************************/
class ListNode{
public:
    int data;
    ListNode *next;
    
/*------------------ ListNode Constructor -------------------------*/
    ListNode(int value){
        data = value;
        next = NULL;
    }
/*------------------- PrintNode Method ------------------------*/
    void printNode() {
        cout<<"listHead -->("<< data <<", ";
            if(!next) {
                cout<<"NULL)->";
            }
            else {
                cout<< next -> data <<")->";
            }
    }
    
};

//************************** STACK CLASS ******************************/
class LLStack{
public:
    ListNode *top;
/*----------------- Stack Constructor --------------------------*/
    LLStack(){
        ListNode *dNode = new ListNode(-99999);
        top = dNode;
    }
/*-------------------- Inserting into Stack -----------------------*/
    void push(ListNode *newNode){
        newNode -> next = top ;
        top = newNode;

    }
/*------------------ Checking if Stack is empty -------------------------*/
    bool isEmpty(){
        return (top -> next == NULL);
    }

/*------------------ Deleting from Stack -------------------------*/
    ListNode *pop(){
        if(isEmpty()){
            cout << "Stack is empty" <<endl;
            return NULL;
        }
        else{
            ListNode *ptr = top;
            top = top -> next;
            return ptr;
        }
    }
    
/*------------------ Build Stack -------------------------*/
    void buildStack(ifstream& inFile){
       int num;
       while(inFile >> num){
           ListNode *newNode = new ListNode(num);
           push(newNode);
           cout <<newNode -> data << " ";
       }
       cout <<endl;
    }

    
};

//**************************** QUEUE CLASS ****************************/
class LLQueue{
public:
    ListNode *head;
    ListNode *tail;
/*----------------- Queue Constructor --------------------------*/
    
    LLQueue(){
        ListNode *dNode = new ListNode(-99999);
        head = dNode;
        tail = dNode;
    }
/*------------------ Checking if Queue is empty -------------------------*/
    bool isEmpty(){
        return (head -> next == NULL);
    }
/*----------------- Inserting into Queue --------------------------*/
    void insertQ(ListNode *newNode){
        if(tail == NULL){
            head = newNode;
            tail = newNode;
            return;
        }
        tail -> next = newNode;
        tail = newNode;
    }
/*----------------- Deleting from Queue --------------------------*/
    ListNode *deleteQ(){
        if(isEmpty()){
            cout<<"Queue is empty" <<endl;
            return NULL;
        }
        else{
            ListNode *ptr = head;
            head = head -> next;
            return ptr;     
        }
            
    }
   
/*-------------------- Building Queue -----------------------*/
    void buildQueue(LLStack stack, ofstream& outFile) {
            while(!stack.isEmpty()) {
                ListNode* newNode = stack.pop();
                outFile<< newNode -> data <<" ";
                insertQ(newNode);
            }
        }
      
};

//*************************** LLIST CLASS *****************************/

class LList{
public:
    ListNode *listHead;

/*----------------- Queue Constructor --------------------------*/
    LList() {
        ListNode *dNode = new ListNode(-99999);
        listHead = dNode;
    }

/*----------------- Find a Spot on LList --------------------------*/
    ListNode *findSpot(ListNode *newNode) {
        ListNode *spot = listHead;
        while(spot != NULL){
            if(spot -> data < newNode -> data ){
                 spot = spot -> next;
            }
        }
        return spot;
    }
/*----------------- Insert One node on LList --------------------------*/
    void insertOneNode(ListNode *spot, ListNode *newNode) {
        newNode->next = spot->next;
        spot->next = newNode;
    }
    

/*----------------- Build List --------------------------*/
    void buildList(LLQueue queue, ofstream& outFile) {
        while(!queue.isEmpty()) {
            ListNode* newNode = queue.deleteQ();
            outFile<<newNode->data<<" ";
            ListNode* spot = findSpot(newNode);
            insertOneNode(spot, newNode);
        }
    }

/*----------------- Print List --------------------------*/
    void printList(ofstream& outFile) {
            cout<<"listHead->";
            outFile<<"listHead->";
            ListNode *ptr = listHead->next;
            while(ptr->next) {
                ptr->printNode();
                outFile<<"("<<ptr->data<<", "<<ptr->next->data<<")->";
                ptr = ptr->next;
            }
            ptr->printNode();
            outFile<<"("<<ptr->data<<", NULL)->NULL";
            cout<<"NULL";
            
        }
    
};


//******************** Main function *******************************/

int main(int argc, const char * argv[]) {
     if(argc != 5) {
        cout<<"need one inFile and three outFiles"<<endl;
    }
    else {
        ifstream inFile;
        ofstream outFile1, outFile2, outFile3;
        inFile.open(argv[1]);
        outFile1.open(argv[2]);
        outFile2.open(argv[3]);
        outFile3.open(argv[4]);

        LLStack *stack = new LLStack();
        stack->buildStack(inFile);

        LLQueue *queue = new LLQueue();
        queue->buildQueue(*stack, outFile1);

        LList *list = new LList();
        list->buildList(*queue, outFile2);

        list->printList(outFile3);

        inFile.close();
        outFile1.close();
        outFile2.close();
        outFile3.close();
    }

    return 0;    
}
