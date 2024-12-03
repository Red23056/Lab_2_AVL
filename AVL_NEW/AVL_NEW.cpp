#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct node {
    int data;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { data = k; left = right = 0; height = 1; }
};

int max_vector(vector<int> matrix) {
    int max = INT_MIN;
    for (int i = 0; i < matrix.size(); i++) {
        if (max < matrix[i]) {
            max = matrix[i];
        }
    }
    return max;
}

void get_data(node* these_child, int space, int position, vector<int>& matrix_data, vector<int>& matrix_level, vector<int>& matrix_position)
{
    matrix_data.push_back(these_child->data);
    matrix_level.push_back(space);
    matrix_position.push_back(position);
    if (these_child->left != nullptr)
    {
        get_data(these_child->left, space + 1, position * 2, matrix_data, matrix_level, matrix_position);
    }
    if (these_child->right != nullptr)
    {
        get_data(these_child->right, space + 1, position * 2 + 1, matrix_data, matrix_level, matrix_position);
    }
}

void print_tree(node* root_parent)
{
    int space = 0;
    int position = 0;
    vector<int> matrix_data;
    vector<int> matrix_level;
    vector<int> matrix_position;
    get_data(root_parent, space, position, matrix_data, matrix_level, matrix_position);
    for (int i = 0; i < matrix_data.size(); i++) {
        cout << matrix_data.at(i) << "|" << matrix_level.at(i) << "|" << matrix_position.at(i) << " ";
    }
    cout << "\n";
    int max_level = max_vector(matrix_level);
    int nado = 6 * pow(2, max_level);
    int step_nado = 6 * pow(2, max_level);
    for (int level = 0; level <= max_level; level++) {
        step_nado /= 2;
        int counter_position = 0;
        int new_position = step_nado;
        for (int j = 1; j <= nado; j++) {
            if (j == new_position) {
                bool check_position = false;
                int index_position;
                for (int suka = 0; suka < matrix_data.size(); suka++) {
                    if (level == matrix_level[suka] and counter_position == matrix_position[suka]) {
                        check_position = true;
                        index_position = suka;
                        break;
                    }
                }
                if (check_position) {
                    cout << matrix_data[index_position];
                    counter_position++;
                }
                else {
                    cout << " ";
                    counter_position++;
                }
                new_position += step_nado * 2;
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

unsigned char height(node* p)
{
    return p ? p->height : 0;
}

int bfactor(node* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k);
    if (k < p->data)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left ? findmin(p->left) : p;
}


node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->data)
        p->left = remove(p->left, k);
    else if (k > p->data)
        p->right = remove(p->right, k);
    else //  k == p->data 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void print_test(node* root_parent)
{
    int space = 0;
    int position = 0;
    vector<int> matrix_data;
    vector<int> matrix_level;
    vector<int> matrix_position;
    get_data(root_parent, space, position, matrix_data, matrix_level, matrix_position);
    cout << max_vector(matrix_level);
}

void inorderTrav(node* node) {
    if (node->left)
        inorderTrav(node->left);
    cout << node->data << " ";
    if (node->right)
        inorderTrav(node->right);
}

void preorderTrav(node* node) {
    cout << node->data << " ";
    if (node->left)
        preorderTrav(node->left);
    if (node->right)
        preorderTrav(node->right);

}

void postorderTrav(node* node) {
    if (node->left)
        postorderTrav(node->left);
    if (node->right)
        postorderTrav(node->right);
    cout << node->data << " ";
}

void printCurrentLevel(node* root, int level);
int depth(node* node);

void printLevelOrder(node* root) {
    int h = depth(root);
    for (int i = 1; i <= h; i++) {
        printCurrentLevel(root, i);
        cout << '\n';
    }

}

void printCurrentLevel(node* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        cout << root->data << " ";
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int depth(node* node) {
    if (node == nullptr)
        return 0;
    else {
        int lheight = depth(node->left);
        int rheight = depth(node->right);
        return (lheight > rheight) ? (lheight + 1) :
            (rheight + 1);
    }
}

int main()
{
    int data;
    node* trees;
    cin >> data;
    node tree(data);
    trees = &tree;
    for (int i = 0; i < 9; i++)
    {
        cin >> data;
        trees = insert(trees, data);
        //print_tree(trees);
    }
    cout << "inorder traversal: ";
    inorderTrav(trees);
    cout << " depth: ";
    print_test(trees);
    cout << "\nBFS\n";
    printLevelOrder(trees);
}