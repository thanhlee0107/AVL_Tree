#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    //check from this line
    Node*leftBalance(Node*&root,bool& taller){
        Node*leftTree=root->pLeft;
        //left of left
        if(leftTree->balance==LH){
            root=rotateRight(root);
            root->balance=EH;
            leftTree->balance=EH;
            taller=false;
        }
        //right of left
        else{
            Node*rightTree=leftTree->pRight;
            if(rightTree->balance==LH){
                root->balance=RH;
                leftTree->balance=EH;
            }
            else if(rightTree->balance==EH){
                leftTree->balance=EH;
            }
            else{
                root->balance=EH;
                leftTree->balance=LH;
            }
            rightTree->balance=EH;
            root->pLeft=rotateLeft(leftTree);
            root=rotateRight(root);
            taller=false;
        }
        return root;
    }
    Node*rightBalance(Node*&root,bool& taller){
        Node*rightTree=root->pRight;
        //right of right
        if(rightTree->balance==RH){
            root=rotateLeft(root);
            root->balance=EH;
            rightTree->balance=EH;
            taller=false;
        }
        else{// left of right
            Node*leftTree=rightTree->pLeft;
            if(leftTree->balance==RH){
                root->balance=LH;
                rightTree->balance=EH;
            }
            else if(leftTree->balance==EH){
                rightTree->balance=EH;
            }
            else{
                root->balance=EH;
                rightTree->balance=RH;
            }
            leftTree->balance=EH;
            root->pRight=rotateRight(rightTree);
            root=rotateLeft(root);
            taller=false;
        }
        return root;
    }
    Node* add(const T&value,Node*&root,bool& t){
            if(!root) {
                root=new Node(value);
                t=true;
                return root;
            }
            if(value<root->data){
                root->pLeft=add(value,root->pLeft,t);
                if (t)
                {
                    if(root->balance==LH){
                        root=leftBalance(root,t);
                    }
                    else if(root->balance==EH){
                        root->balance=LH;
                    }
                    else {
                        root->balance=EH;
                        t=false;
                    }
                } 
            }
            else{
                    root->pRight=add(value,root->pRight,t);
                    if(t){
                        if(root->balance==LH){
                            root->balance=EH;
                            t=false;
                        }
                        else if(root->balance==EH){
                            root->balance=RH;
                        }
                        else {
                            root=rightBalance(root,t);
                        }
                    }
                }
            return root;

    }
    void insert(const T &value){
        bool a= true;
        this->root=add(value,this->root,a);
        
    }
int getBalance(Node*subroot){
    if(!subroot) return 0;
    return getHeightRec(subroot->pLeft)- getHeightRec(subroot->pRight);
}
Node* rotateLeft(Node* subroot)
{
//TODO: Rotate and return new root after rotate
    //int balance=getBalance(subroot);
    //swap
    Node*mid=subroot->pRight;
    Node*end=mid->pLeft;
    // Node *x = y->left;                y            oxay phai
    // Node *T2 = x->right;           x             -->   x
 //                                      T2                  y
    // // Perform rotation                                T2
    // x->right = y;  
    // y->left = T2; 
   mid->pLeft=subroot;
   subroot->pRight=end;
   return mid;
}
Node* rotateRight(Node* subroot)
{
//TODO: Rotate and return new root after rotate
    Node*mid=subroot->pLeft;
    Node*end=mid->pRight;
    mid->pRight=subroot;
    subroot->pLeft=end;
    return mid;
}

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}

    };
};
int main(){
	
AVLTree<int> avl;
int nums[] = {1,2,3,4,5,6,7,8,9};
for (int i = 0; i < 9; i++){
    avl.insert(nums[i]);
}
avl.printTreeStructure();
}