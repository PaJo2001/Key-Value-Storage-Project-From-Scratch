#include<bits/stdc++.h>
#include <stdint.h>
#include<string.h>

using namespace std;

struct Slice{
	uint8_t size;
	char * data;
};

string slicToStr(Slice& a) {
    string ret = "";

    for (int i = 0; i < a.size; i++)
        ret += a.data[i];

    return ret;
}

void strToSlic(string l, Slice& a) {
    a.size = l.length();
    a.data = (char*)malloc(a.size);
    strncpy(a.data, l.c_str(), a.size);
}


int strcm(Slice& a, Slice& b) {
    string x=slicToStr(a);
    string y=slicToStr(b);
    if(x==y)
    return 0;
    else if(x<y)
    return -1;
    else
    return 1;
}
//--------------------------------------------


// An AVL tree node  
class Node  
{  
    public: 
    // int key;
    Slice key;      //Key data slice
    Slice value;    //Value data slice

    Node *left;  
    Node *right;  
    int height;  
};

struct Search {
    
    int num;
    int flag;
    Node* node;
    
}Search;


void clearSearch(){
    Search.node = NULL;
    Search.num = 0;
    Search.flag = 0;
}

int duplicate = 0; //for checking dupl during insertions

// A utility function to get maximum 
// of two slices
Slice max(Slice a, Slice b);  
  
// A utility function to get height  
// of the tree  
int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  

Slice max(Slice a, Slice b)  
{  
    return (strcm( a, b) > 0)? a : b;  
}  
  
Node* newNode(Slice& key, Slice& value)  
{  
    Node* node = new Node(); 
    node->key = key;
    node->value = value;
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// FINE 
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),  
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// FINE
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) -  
           height(N->right);  
}  
  
Node* insert(Node* node, Slice key, Slice value)  
{  
    /* 1. Perform the normal BST rotation */
    if (node == NULL)  
        return(newNode(key, value));
  
    if (strcm(key, node->key) < 0)  
        node->left = insert(node->left, key, value);  
    else if (strcm(key, node->key) > 0)  
        node->right = insert(node->right, key, value);  
    else {
        duplicate = 1;
        return node;    
    }
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                           height(node->right));  
  
    /* 3. Get the balance factor of this  
        ancestor node to check whether  
        this node became unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, 
    // then there are 4 cases  
  
    // Left Left Case  
    // if (balance > 1 && key < node->left->key)  
    if (balance > 1 && strcm(key, node->left->key) < 0)  
        return rightRotate(node);  
  
    // Right Right Case  
    if (balance < -1 && strcm(key, node->right->key) > 0)  
        return leftRotate(node);  
  
    // Left Right Case  
    // if (balance > 1 && key > node->left->key)  
    if (balance > 1 && strcm(key, node->left->key) > 0)      
    {  
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && strcm(key, node->right->key) < 0)  
    {  
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
    return node;  
}  

Node * minValueNode(Node* node)  
{  
    Node* current = node;  
  
    while (current->left != NULL)  
        current = current->left;  
  
    return current;  
}  

Node* deleteNode(Node* root, Slice key)  
{  
      
    // STEP 1: PERFORM STANDARD BST DELETE  
    if (root == NULL)  
        return root;  
  
    // If the key to be deleted is smaller  
    // than the root's key, then it lies 
    // in left subtree  
    if ( strcm(key, root->key) < 0 )
        root->left = deleteNode(root->left, key);  
  
    // If the key to be deleted is greater  
    // than the root's key, then it lies  
    // in right subtree  
    // else if( key > root->key )
    else if( strcm(key, root->key) > 0 )    
        root->right = deleteNode(root->right, key);  
  
    // if key is same as root's key, then  
    // This is the node to be deleted  
    else
    {  
        // node with only one child or no child  
        if( (root->left == NULL) || 
            (root->right == NULL) )  
        {  
            Node *temp = root->left ?  
                         root->left :  
                         root->right;  
  
            // No child case  
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else // One child case  
            *root = *temp; // Copy the contents of  
                           // the non-empty child  
            free(temp);  
        }  
        else
        {  
            // node with two children: Get the inorder  
            // successor (smallest in the right subtree)  
            Node* temp = minValueNode(root->right);  
  
            // Copy the inorder successor's  
            // data to this node  
            root->key = temp->key;
            root->value = temp->value;  
  
            // Delete the inorder successor  
            root->right = deleteNode(root->right,  
                                     temp->key);  
        }  
    }  
  
    // If the tree had only one node 
    // then return  
    if (root == NULL)  
    return root;  
  
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
    root->height = 1 + max(height(root->left),  
                           height(root->right));  
  
    // STEP 3: GET THE BALANCE FACTOR OF  
    // THIS NODE (to check whether this  
    // node became unbalanced)  
    int balance = getBalance(root);  
  
    // If this node becomes unbalanced,  
    // then there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 &&  
        getBalance(root->left) >= 0)  
        return rightRotate(root);  
  
    // Left Right Case  
    if (balance > 1 &&  
        getBalance(root->left) < 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
  
    // Right Right Case  
    if (balance < -1 &&  
        getBalance(root->right) <= 0)  
        return leftRotate(root);  
  
    // Right Left Case  
    if (balance < -1 &&  
        getBalance(root->right) > 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  
    // cout<<"Delete succ\n";
    return root;  
}  


// Before every search initialize Search.num to 0 and also after.

//USE FINDS,DELS for N (lex) functionality



void search(Node *root, int N)  
{   
    if(Search.flag == 1){
        // cout<<"search aborted1";
        return;
    }

    if(root != NULL)  
    {  
        
        search(root->left, N);
        if(Search.flag == 1){
        // cout<<"search aborted2";
        return;
        }

        if(Search.num == N){
            Search.node = root;
            // Search.num = N;
            // cout<<Search.num<<endl;
            Search.flag = 1;
            return;
        }
        else
            Search.num++;

        if(Search.flag == 1){
        // cout<<"search aborted3";
        return;
    }      
        search(root->right, N);
    }  
}  

//Data wise search 
void dsearch(Node *root, Slice key)  
{   
    // cout<<"this fine";
    if(root != NULL)  
    {  
        dsearch(root->left, key);
//chinha
        if(strncmp(root->key.data,key.data,min(key.size,root->key.size))==0){
            // cout<<"fine2";
            Search.node = root;
            Search.num = 0;
            return;
        }

        dsearch(root->right, key);
    }  
}  

static inline void finds(Node *root, int N){
    Search.num = 0;
    Search.node = NULL;
    Search.flag = 0;
    search(root, N);
}

static inline void dels(Node *root, int N){
    finds(root, N);
    root = deleteNode(root, Search.node->key);
    // cout<<"Delbynum dels succ\n";
}

//--------------------------------------------------------------------

class kvStore{
public:
    Node* root = NULL;
    int counter = 0;
    int dupop = 0;
	//constructor
	kvStore(uint64_t max_entries){
        // Node* root = NULL;
        // Node* root = NULL;
    };
    //to check 1st elem
    Slice getbse(){
    Node*node = root;
    while(node->left!=NULL){
        node=node->left;
    }
    return node->key;
    }
	
    int getdupop(){
        return dupop;
    }
	//retrieve key value pair to `key` and `value`
	bool get(Slice& key, Slice& value){

        clearSearch();
        // string a=slicToStr(key);
        dsearch(root, key);
   
        if(Search.node!=NULL)
        {
            // key = Search.node->key;
            string b=slicToStr(Search.node->value);
            strToSlic(b,value);

            return true;
        }
        else
            return false;
	}

	//put key and value into kvstore
	bool put(Slice& key, Slice& value){
        //Supports overwrite
        clearSearch();
        duplicate = 0;

        root = insert(root, key, value);

        // return false;
        if(duplicate==0) {
        return false;
        }
        else {
        // counter++;
        dupop++;
        duplicate = 0;
        root = deleteNode(root, key);
        root = insert(root, key, value);
        // cout<<"duplicate!\n";
        // value.data+='\0';
        // value.size++;
        return true;
        }
	}

	//delete key and corresponding value
	bool del(Slice& key){
        clearSearch();
		//Your Code Here
        root = deleteNode(root, key);
		return false; //?
	}

	//get kv pair #N into `key` and `value` ..sumting wrong
	bool get(int N,Slice& key, Slice& value){
        clearSearch();
		// Your Code Here
        finds(root, N);
        key = Search.node->key;
        value = Search.node->value;
		return true; //?
	}

	//delete kv pair #N from kvstore 
	bool del(int N){
        clearSearch();
		dels(root, N);
		return true;  //?
	}
};

//-------------------------------------------------------------------------

// // Driver Code 
// int main()  
// {
// cout<<"start";
// Node *root = NULL;  
// Slice k,k2,m,m2,l,l2,n,nn,o,oo,p,pp;
// k.data = "asa";
// k2.data = "asavalue";
// l.data = "basa";
// l2.data = "basavalue";
// m.data = "basa";
// m2.data = "dasavalue";  
// n.data = "nasa";
// nn.data = "nasavalue";  
// o.data = "oasa";
// oo.data = "oasavalue";  
// p.data = "pasa";
// pp.data = "pasavalue";  

//     root = insert(root, m, m2);
//     root = insert(root, k, k2);
//     // root = insert(root, l, l2);
//     root = insert(root, o, oo);
//     root = insert(root, p, pp);
//     root = insert(root, n, nn);
    
//     cout<<root->left->key.data<<endl;
//     cout<<root->key.data<<endl;
//     if(root->right)
//         cout<<root->right->key.data<<endl;
    
//     dsearch(root, slicToStr(m));
//     cout<<"Search results\n";
//     cout<<Search.node->key.data<<'\n';
//     cout<<Search.node->value.data<<'\n';
//     int nu;cin>>nu;
//     finds(root, nu);
//     cout<<"Finds results\n";
//     cout<<Search.node->key.data<<'\n';
//     cout<<Search.node->value.data<<'\n';
 
//     root = deleteNode(root, k);  //WORKS!
//     dels(root, 0);   //WORKS!
  
//     return 0;  
// }  
  
