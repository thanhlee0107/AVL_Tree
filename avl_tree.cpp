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
           
            root->balance=EH;
            leftTree->balance=EH;
            taller=false; 
            return rotateRight(root);
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
                root->balance=EH;
            }
            else{
                root->balance=EH;
                leftTree->balance=LH;
            }
            rightTree->balance=EH;
            root->pLeft=rotateLeft(leftTree);
            taller=false; 
            return rotateRight(root);
        }
        return root;
    }
    Node*rightBalance(Node*&root,bool& taller){
        Node*rightTree=root->pRight;
        //right of right
        if(rightTree->balance==RH){
            root->balance=EH;
            rightTree->balance=EH;
            taller=false;            
            return rotateLeft(root);

        }
        else{// left of right
            Node*leftTree=rightTree->pLeft;
            if(leftTree->balance==RH){
                root->balance=LH;
                rightTree->balance=EH;
            }
            else if(leftTree->balance==EH){
                rightTree->balance=EH;
                root->balance=EH;
            }
            else{
                root->balance=EH;
                rightTree->balance=RH;
            }
            //cout<<1<<endl;
            leftTree->balance=EH;
            root->pRight=rotateRight(root->pRight);
            taller=false;
           return rotateLeft(root);
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
                            //cout<<value<<endl;
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
    Node*mid=subroot->pRight;
    Node*end=mid->pLeft;
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
Node*deleteRightBalance(Node*&root, bool&shorter){
    if(root->balance==LH){
        root->balance=EH;
    }
    else if(root->balance==EH){
        root->balance=RH;
        shorter=false;
    }
    else{
        Node*rightTree=root->pRight;
        if(rightTree->balance==LH){
            Node*leftTree=rightTree->pLeft;
            if(leftTree->balance==LH){
                rightTree->balance=EH;
            }
            else if(leftTree->balance==EH){
                root->balance=LH;
                rightTree->balance=EH;
            }
            else{
                root->balance=LH;
                rightTree->balance=EH;
            }
            leftTree->balance=EH;
            root->pRight=rotateRight(rightTree);
            return rotateLeft(root);
        }
        else{
            if (rightTree->balance!=EH){
                root->balance=EH;
                rightTree->balance=EH;
            }
            else{
                root->balance=RH;
                rightTree->balance=LH;
                shorter=false;
            }
            return rotateLeft(root);
        }
    }
    return root;
}
Node*deleteLeftBalance(Node*&root, bool&shorter){
    if(root->balance==RH){
        root->balance=EH;
    }
    else if(root->balance==EH){
        root->balance=LH;
        shorter=false;
    }
    else {
        Node*leftTree=root->pLeft;
        if(leftTree->balance==RH){
            Node*rightTree=leftTree->pRight;
            if(rightTree->balance==RH){
                leftTree->balance=LH;
                root->balance=EH;
            }
            else if(rightTree->balance==EH){
                root->balance=RH;
                leftTree->balance=EH;
            }
            else{
                root->balance=RH;
                leftTree->balance=EH;
            }
            rightTree->balance=EH;
            root->pLeft=rotateLeft(leftTree);
            return rotateRight(root);
        }
        else{
            if(leftTree->balance!=EH){
                root->balance=EH;
                leftTree->balance=EH;
            }
            else{
                root->balance=LH;
                leftTree->balance=RH;
                shorter=false;
            }
            return rotateRight(root);

        }
    }
    return root;
}
Node*deleteAVL(Node*root,T key,bool& shorter,bool& success){
    if(!root){
        shorter=false;
        success=false;
        return nullptr;
    }
    if(key<root->data){
        root->pLeft=deleteAVL(root->pLeft,key,shorter,success);
        if(shorter){
            root=deleteRightBalance(root,shorter);
        }
    }
    else if(key>root->data){
        root->pRight=deleteAVL(root->pRight,key,shorter,success);
        if(shorter){
            root=deleteLeftBalance(root,shorter);
        }
    }
    else{
        Node*deleteNode=root;
        if(!root->pRight){
            Node*newRoot=root->pLeft;
            success=true;
            shorter=true;
            //recycle deleteNode
            delete deleteNode;
            return newRoot;
        }
        else if(!root->pLeft){
            Node*newRoot=root->pRight;
            success=right;
            shorter=right;
            delete deleteNode;
            return newRoot;
        }
        else{
            Node*exchPtr=root->pLeft;
            while(exchPtr->pRight){
                exchPtr=exchPtr->pRight;
            }
            root->data=exchPtr->data;
            root->pLeft=deleteAVL(root->pLeft,exchPtr->data,shorter,success);
            if(shorter){
                root=deleteRightBalance(root,shorter);
            }
        }
    }
    return root;
}
void remove(const T &value){
    bool shorter=true;
    bool success=true;
    this->root=deleteAVL(this->root,value,shorter,success);
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
int arr[] = {10, 5, 15, 7};
for (int i = 0; i < 4; i++)
{
  avl.insert(arr[i]);
}
avl.printTreeStructure();
cout<<endl<<"------------------------------------------"<<endl;
avl.remove(15);
avl.printTreeStructure();
}