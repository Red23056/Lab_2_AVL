#include <iostream>
#include <vector>
#include <climits>
using namespace std;
enum Color { RED, BLACK };

struct Node
{
    int data;
    Color color;
    Node* left, * right, * parent;

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    Node* rootParent;

    void rotateLeft(Node*& node)
    {
        Node* node_right = node->right;
        node->right = node_right->left;

        if (node->right != nullptr)
        {
            node->right->parent = node;
        }

        node_right->parent = node->parent;

        if (node->parent == nullptr)
        {
            rootParent = node_right;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = node_right;
        }
        else
        {
            node->parent->right = node_right;
        }

        node_right->left = node;
        node->parent = node_right;
    }

    void rotateRight(Node*& node)
    {
        Node* node_left = node->left;
        node->left = node_left->right;

        if (node->left != nullptr)
        {
            node->left->parent = node;
        }

        node_left->parent = node->parent;

        if (node->parent == nullptr)
        {
            rootParent = node_left;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = node_left;
        }
        else {
            node->parent->right = node_left;
        }

        node_left->right = node;
        node->parent = node_left;
    }

    void fixViolation(Node*& node)
    {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while ((node != rootParent) && (node->color == RED) && (node->parent->color == RED))
        {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else
                {
                    if (node == parent->right)
                    {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else
            {
                Node* uncle = grandparent->left;

                if ((uncle != nullptr) && (uncle->color == RED))
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                }
                else {
                    if (node == parent->left)
                    {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        rootParent->color = BLACK;
    }

public:
    RedBlackTree() : rootParent(nullptr) {}

    void insert(const int& data)
    {
        Node* newNode = new Node(data);
        rootParent = BSTInsert(rootParent, newNode);
        fixViolation(newNode);
    }

    Node* BSTInsert(Node* root, Node* newNode)
    {
        if (root == nullptr)
        {
            return newNode;
        }

        if (newNode->data < root->data)
        {
            root->left = BSTInsert(root->left, newNode);
            root->left->parent = root;
        }
        else if (newNode->data > root->data)
        {
            root->right = BSTInsert(root->right, newNode);
            root->right->parent = root;
        }

        return root;
    }

    int max_vector(vector<int> vec)
    {
        int mx = INT_MIN;
        for (int i = 0; i < vec.size(); i++)
        {
            if (mx < vec[i])
            {
                mx = vec[i];
            }
        }
        return mx;
    }
    void get_data(Node* these_child, int space, int position, vector<int>& vec_data, vector<int>& vec_level, vector<int>& vec_position)
    {
        vec_data.push_back(these_child->data);
        vec_level.push_back(space);
        vec_position.push_back(position);
        if (these_child->left != nullptr)
        {
            get_data(these_child->left, space + 1, position * 2, vec_data, vec_level, vec_position);
        }
        if (these_child->right != nullptr)
        {
            get_data(these_child->right, space + 1, position * 2 + 1, vec_data, vec_level, vec_position);
        }
    }

    void print_tree()
    {
        int space = 0;
        int position = 0;
        vector<int> vec_data;
        vector<int> vec_level;
        vector<int> vec_position;
        get_data(rootParent, space, position, vec_data, vec_level, vec_position);
        for (int i = 0; i < vec_data.size(); i++)
        {
            cout << vec_data.at(i) << "|" << vec_level.at(i) << "|" << vec_position.at(i) << " ";
        }
        cout << "\n";
        int max_level = max_vector(vec_level);
        int nado = 6 * pow(2, max_level);
        int step_nado = 6 * pow(2, max_level);
        for (int level = 0; level <= max_level; level++)
        {
            step_nado /= 2;
            int counter_position = 0;
            int new_position = step_nado;
            for (int j = 1; j <= nado; j++)
            {
                if (j == new_position)
                {
                    bool check_position = false;
                    int index_position;
                    for (int suka = 0; suka < vec_data.size(); suka++)
                    {
                        if (level == vec_level[suka] and counter_position == vec_position[suka])
                        {
                            check_position = true;
                            index_position = suka;
                            break;
                        }
                    }
                    if (check_position)
                    {
                        cout << vec_data[index_position];
                        counter_position++;
                    }
                    else
                    {
                        cout << " ";
                        counter_position++;
                    }
                    new_position += step_nado * 2;
                }
                else
                {
                    cout << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    Node* getRoot() {
        return rootParent;
    }
    void print_test() {
        int space = 0;
        int position = 0;
        vector<int> matrix_data;
        vector<int> matrix_level;
        vector<int> matrix_position;
        get_data(rootParent, space, position, matrix_data, matrix_level, matrix_position);
        cout << max_vector(matrix_level);
    }
};



void inorderTrav(Node* node) {
    if (node->left)
        inorderTrav(node->left);
    cout << node->data << " ";
    if (node->right)
        inorderTrav(node->right);
}

void preorderTrav(Node* node) {
    cout << node->data << " ";
    if (node->left)
        preorderTrav(node->left);
    if (node->right)
        preorderTrav(node->right);

}

void postorderTrav(Node* node) {
    if (node->left)
        postorderTrav(node->left);
    if (node->right)
        postorderTrav(node->right);
    cout << node->data << " ";
}

void printCurrentLevel(Node* root, int level);
int height(Node* node);

void printLevelOrder(Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        cout << '\n';
    }

}

void printCurrentLevel(Node* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        cout << root->data << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        return (lheight > rheight) ? (lheight + 1) :
            (rheight + 1);
    }
}

int main()
{
    int command;
    RedBlackTree rbt;
    for (int i = 0; i < 5; i++)
    {
        cin >> command;
        rbt.insert(command);
        //rbt.print_tree();
    }
    cout << "inorder traversal: ";
    inorderTrav(rbt.getRoot());
    cout << " depth: ";
    rbt.print_test();
    cout << "\nBFS:\n";
    printLevelOrder(rbt.getRoot());
}