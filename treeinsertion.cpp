#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

node *insertinBST(node *root, int d)
{
    if (root == NULL)
    {
        return new node(d);
    }
    if (d <= root->data)
    {
        root->left = insertinBST(root->left, d);
    }
    else
    {
        root->right = insertinBST(root->right, d);
    }
    return root;
}

node *build()
{
    int d;
    cin >> d;

    node *root = NULL;
    while (d != -1)
    {
        root = insertinBST(root, d);
        cin >> d;
    }
    return root;
}

void bfs(node *root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        node *f = q.front();
        if (f == NULL)
        {
            cout << endl;
            q.pop();

            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        
        else
        {
            cout << f->data << " ";
            q.pop();

            if (f->left)
            {
                q.push(f->left);
            }
            if (f->right)
            {
                q.push(f->right);
            }
        }
    }
    return;
}

void inorder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

bool search(node *root, int key)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->data == key)
    {
        return true;
    }
    if (key <= root->data)
    {
        return search(root->left, key);
    }
    else
    {
        return search(root->right, key);
    }
}

//Check for the three cases where the node to be deleted might have
//1. NO child   2. One child      3. Two children
node *deleteinBST(node *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (key < root->data)
    {
        root->left = deleteinBST(root->left, key);
        return root;
    }
    else if (key == root->data)
    {
        if (root->left == NULL and root->right == NULL)
        {
            delete root;
            return NULL;
        }
        if (root->left != NULL and root->right == NULL)
        {
            node *temp = root->left;
            delete root;
            return temp;
        }
        if (root->right != NULL and root->left == NULL)
        {
            node *temp = root->right;
            delete root;
            return temp;
        }

        node *replace = root->right;
        while (replace->left != NULL)
        {
            replace = replace->left;
        }
        root->data = replace->data;
        root->right = deleteinBST(root->right, replace->data);
        return root;
    }
    else
    {
        root->right = deleteinBST(root->right, key);
        return root;
    }
}

//Top Down Approach Followed
bool isBST(node *root, int minv = INT_MIN, int maxv = INT_MAX)
{
    if (root == NULL)
    {
        return true;
    }

    if (root->data >= minv and root->data <= maxv and isBST(root->left, minv, root->data) and isBST(root->right, root->data, maxv))
    {
        return true;
    }
    return false;
}

//Largest Binary Search Tree in BST


//Flatten a linked list
class LinkedList
{
public:
    node *head;
    node *tail;
};

LinkedList flatten(node *root)
{
    LinkedList l;
    if (root == NULL)
    {
        l.head = l.tail = NULL;
        return l;
    }
    //Leaf Node
    if (root->left == NULL and root->right == NULL)
    {
        l.head = l.tail = root;
        return l;
    }

    if (root->left != NULL and root->right == NULL)
    {
        LinkedList leftll = flatten(root->left);
        leftll.tail->right = root;

        l.head = leftll.head;
        l.tail = root;
        return l;
    }

    if (root->left == NULL and root->right != NULL)
    {
        LinkedList rightll = flatten(root->right);
        root->right = rightll.head;

        l.head = root;
        l.tail = rightll.tail;
        return l;
    }
    
    LinkedList leftLL = flatten(root->left);
    LinkedList rightLL = flatten(root->right);

    leftLL.tail->right = root;
    root->right = rightLL.head;

    l.head = leftLL.head;
    l.tail = rightLL.tail;
    return l;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    node *root = build();
    inorder(root);
    cout << endl;
    // bfs(root);

    int s;
    cin >> s;

    // if (search(root, s))
    // {
    //     cout << "Present" << endl;
    // }
    // else
    // {
    //     cout << "Not present" << endl;
    // }

    // root = deleteinBST(root, s);
    // inorder(root);
    // cout << endl;
    // bfs(root);

    cout << endl;
    // if (isBST(root))
    // {
    //     cout << "Yes" << endl;
    // }
    // else
    // {
    //     cout << "NO" << endl;
    // }
    LinkedList l = flatten(root);
    node *temp = l.head;

    while (temp != NULL)
    {
        cout << temp->data << " -->";
        temp = temp->right;
    }
    return 0;
}