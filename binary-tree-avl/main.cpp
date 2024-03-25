#include <iostream>
#include <windows.h>
#include <locale>
#include <limits>
#include <algorithm>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

struct Tree
{
    int info;
    int fb;
    Tree *stl;
    Tree *str;
};

int is_empty_tree(Tree *tree)
{
    if(tree == NULL)
        return 1;
    if(tree->info == NULL)
        return 1;
    return 0;
}

void insert_in_tree(Tree **pTree, int value)
{
    if(*pTree == NULL)
    {
        *pTree = new Tree;
        (*pTree)->stl = NULL;
        (*pTree)->str = NULL;
        (*pTree)->info = value;
    }
    else
    {
        if(value < (*pTree)->info)
            insert_in_tree(&(*pTree)->stl, value);
        else
            insert_in_tree(&(*pTree)->str, value);
    }
}

void show_pre_order(Tree *tree)
{
    cout << "<";
    if (!is_empty_tree(tree))
    {
        cout << tree->info;
        show_pre_order(tree->stl);
        show_pre_order(tree->str);
    }
    cout << ">";
}

void show_in_simetric_order(Tree *tree)
{
    cout << "<";
    if (!is_empty_tree(tree))
    {
        show_in_simetric_order(tree->stl);
        cout << tree->info;
        show_in_simetric_order(tree->str);
    }
    cout << ">";
}

void show_post_order(Tree *tree)
{
    cout << "<";
    if (!is_empty_tree(tree))
    {
        show_post_order(tree->stl);
        show_post_order(tree->str);
        cout << tree->info;
    }
    cout << ">";
}

Tree* remove_node(Tree **pTree, int num)
{
    if(*pTree == NULL)
    {
        cout << "Nao existe o elemento na arvore";
        return *pTree;
    }
    if(num < (*pTree)->info)
        remove_node(&(*pTree)->stl, num);
    else if(num > (*pTree)->info)
        remove_node(&(*pTree)->str, num);
    else
    {
        Tree *aux = *pTree;
        if(((*pTree)->stl == NULL) && ((*pTree)->str == NULL))
        {
            delete(aux);
            (*pTree) = NULL;
        }
        else if((*pTree)->stl == NULL)
        {
            (*pTree) = (*pTree)->str;
            aux->str =  NULL;
            delete(aux);
            aux = NULL;
        }
        else if((*pTree)->str == NULL)
        {
            (*pTree) = (*pTree)->stl;
            aux->stl =  NULL;
            delete(aux);
            aux = NULL;
        }
        else
        {
            aux = (*pTree)->stl;
            while(aux->str != NULL)
                aux = aux->str;
            (*pTree)->info = aux->info;
            aux->info = num;
            (*pTree)->stl = remove_node(&(*pTree)->stl, num);
        }
    }
    return *pTree;
}

int tree_height(Tree *root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        int heightLeft = tree_height(root->stl);
        int heightRight = tree_height(root->str);
        if(heightLeft < heightRight)
            return (heightRight + 1);
        else
            return (heightLeft + 1);
    }
}

int factor_balalance(Tree *root)
{
    int factor = 0;

    if (root->stl)
        factor += tree_height(root->stl);

    if (root->str)
        factor -= tree_height(root->str);

    return factor;
}

void calc_fb(Tree *root)
{
    if(!is_empty_tree(root))
    {
        root->fb = factor_balalance(root);
        if(root->stl != NULL)
        {
            calc_fb(root->stl);
        }
        if(root->str != NULL)
        {
            calc_fb(root->str);
        }
    }
}

int verify_avl_balance(Tree *root)
{
    if(!is_empty_tree(root))
    {
        if((root->fb > 1) || (root->fb < -1))
        {
            return root->fb;
        }
        if(root->stl != NULL)
            verify_avl_balance(root->stl);
        else
            return 0;
        if(root->str != NULL)
            verify_avl_balance(root->str);
        else
            return 0;
    }
}

Tree* rotate_ll (Tree *p)
{
    Tree * temp_ptr = p;
    Tree * esq_ptr = temp_ptr->stl;

    temp_ptr->stl = esq_ptr->str;
    esq_ptr->str = temp_ptr;

    return esq_ptr;
}

Tree* rotate_lr (Tree *p)
{
    Tree* temp_ptr = p;
    Tree* esq_ptr = temp_ptr->stl;
    Tree* dir_ptr = esq_ptr->str;

    temp_ptr->stl = dir_ptr->str;
    esq_ptr->str = dir_ptr->stl;
    dir_ptr->stl = esq_ptr;
    dir_ptr->str = temp_ptr;

    return dir_ptr;
}

Tree* rotate_rl (Tree *p)
{
    Tree *temp_ptr = p;
    Tree *dir_ptr = temp_ptr->str;
    Tree *esq_ptr = dir_ptr->stl;

    temp_ptr->str = esq_ptr->stl;
    dir_ptr->stl = esq_ptr->str;
    esq_ptr->str = dir_ptr;
    esq_ptr->stl = temp_ptr;

    return esq_ptr;
}

Tree* rotate_rr (Tree *t)
{
    Tree *temp_ptr = t;
    Tree *dir_ptr = temp_ptr->str;

    temp_ptr->str = dir_ptr->stl;
    dir_ptr->stl = temp_ptr;

    return dir_ptr;
}

Tree* balance_tree_node (Tree *root )
{
    Tree *tree_with_balance = NULL;

    if (root->stl)
    {
        root->stl = balance_tree_node(root->stl);
    }


    if (root->str)
    {
        root->str = balance_tree_node(root->str);
    }

    int factor = factor_balalance(root);

    if (factor >= 2)
    {
        if (factor_balalance(root->stl) <= -1 )
        {
            tree_with_balance = rotate_lr(root);
        }
        else
        {
            tree_with_balance = rotate_ll(root);
        }

    }
    else if (factor <= -2)
    {
        if (factor_balalance(root->str) >= 1 )
        {
            tree_with_balance = rotate_rl(root);
        }
        else
        {
            tree_with_balance = rotate_rr(root);
        }
    }
    else
    {
        tree_with_balance = root;
    }

    return tree_with_balance;
}

int get_number_dialog()
{
    int num;
    string input;
    cout << "Digite um numero: ";

    while (true)
    {
        cin >> input;
        if (all_of(input.begin(), input.end(), ::isdigit))
        {
            stringstream ss(input);
            ss >> num;
            break;
        }
        else
        {
            cout << "Digite um numero valido: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return num;
}

Tree *free_nodes(Tree *&tree)
{
    if (tree == NULL)
    {
        return tree;
    }

    free_nodes(tree->stl);
    free_nodes(tree->str);

    delete tree->stl;
    delete tree->str;

    tree->stl = NULL;
    tree->str = NULL;

    delete tree;
    tree = NULL;
    return tree;
}

void show_with_factor(Tree *root)
{
    cout << "<";
    if(!is_empty_tree(root))
    {
        show_with_factor(root->stl);
        cout << root->info << "(" << root->fb << ")";
        show_with_factor(root->str);
    }
    cout << ">";
}

void insert_and_balance(Tree **pRoot, int value)
{
    insert_in_tree(pRoot, value);
    calc_fb(*pRoot);
    if (verify_avl_balance(*pRoot) != 0)
    {
        *pRoot = balance_tree_node(*pRoot);
        calc_fb(*pRoot);
    }
}

void remove_and_balance(Tree **pRoot, int value)
{
    *pRoot = remove_node(pRoot, value);

    calc_fb(*pRoot);
    if (verify_avl_balance(*pRoot) != 0)
    {
        *pRoot = balance_tree_node(*pRoot);
        calc_fb(*pRoot);
    }
}

int find_level(Tree *root, int value, int level)
{
    if (root == NULL)
        return -1;

    if (root->info == value)
        return level;

    int level_left = find_level(root->stl, value, level + 1);
    int level_right = find_level(root->str, value, level + 1);

    return (level_left != -1) ? level_left : level_right;
}

bool search_value(Tree *root, int value) {
    if (root == NULL)
        return false;

    if (root->info == value)
        return true;

    if (value < root->info)
        return search_value(root->stl, value);
    else
        return search_value(root->str, value);
}

int count_nodes(Tree *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + count_nodes(root->stl) + count_nodes(root->str);
    }
}

bool is_full_tree(Tree *root) {
    if (root == NULL) {
        return true;
    }
    int total_nodes = count_nodes(root);
    int height = tree_height(root);
    int max_nodes = (1 << height) - 1;
    return total_nodes == max_nodes;
}

bool is_leaf(Tree *node) {
    return (node != NULL && node->stl == NULL && node->str == NULL);
}

bool is_complete_tree(Tree *root, int index, int num_nodes) {
    if (root == NULL)
        return true;

    if (index >= num_nodes)
        return false;

    // Verificar recursivamente se os filhos esquerdo e direito são árvores completas
    return is_complete_tree(root->stl, 2 * index + 1, num_nodes) &&
           is_complete_tree(root->str, 2 * index + 2, num_nodes);
}

bool is_complete_tree(Tree *root) {
    int num_nodes = count_nodes(root);
    return is_complete_tree(root, 0, num_nodes);
}

Tree* minValueNode(Tree* node) {
    Tree* current = node;
    // Encontra o nó mais à esquerda na subárvore direita
    while (current && current->stl != NULL)
        current = current->stl;
    return current;
}

Tree* maxValueNode(Tree* node) {
    Tree* current = node;
    // Encontra o nó mais à direita na subárvore esquerda
    while (current && current->str != NULL)
        current = current->str;
    return current;
}

Tree* findNode(Tree* root, int value) {
    if (root == NULL || root->info == value)
        return root;
    if (root->info < value)
        return findNode(root->str, value);
    return findNode(root->stl, value);
}

void print_level_order(Tree *root) {
    if (root == NULL) return;

    int current_level_count = 1;
    int next_level_count = 0;

    Tree **current_level = new Tree*[current_level_count];
    current_level[0] = root;

    while (current_level_count > 0) {
        for (int i = 0; i < current_level_count; i++) {
            cout << current_level[i]->info << " ";
            if (current_level[i]->stl != NULL) {
                next_level_count++;
            }
            if (current_level[i]->str != NULL) {
                next_level_count++;
            }
        }

        cout << endl;

        Tree **next_level = new Tree*[next_level_count];

        int index = 0;

        for (int i = 0; i < current_level_count; i++) {
            if (current_level[i]->stl != NULL) {
                next_level[index++] = current_level[i]->stl;
            }
            if (current_level[i]->str != NULL) {
                next_level[index++] = current_level[i]->str;
            }
        }

        current_level_count = next_level_count;
        next_level_count = 0;
        delete[] current_level;
        current_level = next_level;
    }

    delete[] current_level;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

bool is_balanced(Tree *root) {
    if (root == NULL) {
        return true;
    }

    int left_height = tree_height(root->stl);
    int right_height = tree_height(root->str);

    if (abs(left_height - right_height) <= 1 && is_balanced(root->stl) && is_balanced(root->str)) {
        return true;
    }

    return false;
}

bool findPath(Tree* root, int target, int path[], int& pathLen) {
    if (root == NULL) return false;

    path[pathLen++] = root->info;

    if (root->info == target) return true;

    if ((root->stl && findPath(root->stl, target, path, pathLen)) ||
        (root->str && findPath(root->str, target, path, pathLen))) {
        return true;
    }

    pathLen--;
    return false;
}

void shortestPath(Tree* root, int node1, int node2) {
    const int MAX_SIZE = 1000;
    int path1[MAX_SIZE], path2[MAX_SIZE];
    int pathLen1 = 0, pathLen2 = 0;
    if (!findPath(root, node1, path1, pathLen1) || !findPath(root, node2, path2, pathLen2)) {
        cout << "Pelo menos um dos nós não está presente na árvore." << endl;
        return;
    }

    int i;
    for (i = 0; i < pathLen1 && i < pathLen2; i++) {
        if (path1[i] != path2[i]) {
            break;
        }
    }

    cout << "Caminho mais curto entre " << node1 << " e " << node2 << ": ";

    for (int j = pathLen1 - 1; j >= i; j--) {
        cout << path1[j] << " ";
    }

    for (int j = i; j < pathLen2; j++) {
        cout << path2[j] << " ";
    }
    cout << endl;
}

void balance_and_describe(Tree **pRoot)
{
    if (*pRoot == NULL)
        return;

    while (true)
    {
        int factor = factor_balalance(*pRoot);

        if (factor >= 2)
        {
            if (factor_balalance((*pRoot)->stl) <= -1)
            {
                *pRoot = rotate_lr(*pRoot);
                cout << "LR rotation" << endl;
            }
            else
            {
                *pRoot = rotate_ll(*pRoot);
                cout << "LL rotation" << endl;
            }
        }
        else if (factor <= -2)
        {
            if (factor_balalance((*pRoot)->str) >= 1)
            {
                *pRoot = rotate_rl(*pRoot);
                cout << "RL rotation" << endl;
            }
            else
            {
                *pRoot = rotate_rr(*pRoot);
                cout << "RR rotation" << endl;
            }
        }
        else
        {
            break;
        }
    }
}

int count_nodes_at_level(Tree *root, int target_level, int current_level) {
    if (root == NULL) {
        return 0;
    }
    if (current_level == target_level) {
        return 1;
    }
    return count_nodes_at_level(root->stl, target_level, current_level + 1) +
           count_nodes_at_level(root->str, target_level, current_level + 1);
}

Tree* find_min_value_node(Tree* node) {
    Tree* current = node;
    while (current && current->stl != NULL)
        current = current->stl;
    return current;
}

Tree* find_max_value_node(Tree* node) {
    Tree* current = node;
    while (current && current->str != NULL)
        current = current->str;
    return current;
}

Tree* find_successor(Tree* root, Tree* node) {
    if (node == NULL) return NULL;
    if (node->str != NULL)
        return find_min_value_node(node->str);

    Tree* successor = NULL;
    while (root != NULL) {
        if (node->info < root->info) {
            successor = root;
            root = root->stl;
        } else if (node->info > root->info) {
            root = root->str;
        } else {
            break;
        }
    }
    return successor;
}

Tree* find_predecessor(Tree* root, Tree* node) {
    if (node == NULL) return NULL;
    if (node->stl != NULL)
        return find_max_value_node(node->stl);

    Tree* predecessor = NULL;
    while (root != NULL) {
        if (node->info > root->info) {
            predecessor = root;
            root = root->str;
        } else if (node->info < root->info) {
            root = root->stl;
        } else {
            break;
        }
    }
    return predecessor;
}

int get_node_depth(Tree* root, int value, int depth) {
    if (root == NULL) {
        return -1;
    }
    if (root->info == value) {
        return depth;
    }

    int left_depth = get_node_depth(root->stl, value, depth + 1);
    if (left_depth != -1) {
        return left_depth;
    }

    int right_depth = get_node_depth(root->str, value, depth + 1);
    return right_depth;
}

void print_tree_structure(Tree* root, int level = 0) {
    if (root == NULL) {
        return;
    }

    // Indentação para representar o nível atual da árvore
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }

    // Imprime o valor do nó atual
    cout << root->info << endl;

    // Imprime recursivamente a subárvore esquerda com um nível a mais
    print_tree_structure(root->stl, level + 1);

    // Imprime recursivamente a subárvore direita com um nível a mais
    print_tree_structure(root->str, level + 1);
}

void calculate_sum_and_count(Tree *root, int &sum, int &count) {
    if (root == nullptr) {
        return;
    }
    // Percorre a subárvore esquerda
    calculate_sum_and_count(root->stl, sum, count);
    // Incrementa a soma com o valor do nó atual
    sum += root->info;
    // Incrementa o contador de nós
    count++;
    // Percorre a subárvore direita
    calculate_sum_and_count(root->str, sum, count);
}

double calculate_tree_average(Tree *root) {
    int sum = 0; // Soma dos valores
    int count = 0; // Contador de nós
    calculate_sum_and_count(root, sum, count); // Chama a função auxiliar para calcular a soma e o contador
    if (count == 0) {
        return 0; // Retorna 0 se a árvore estiver vazia
    }
    // Calcula a média
    return static_cast<double>(sum) / count;
}

void pause()
{
    cout << "\n" << endl;
    system("pause");
}

void show_menu(string menu[], int size, Tree *root)
{
    int selectedOption = -1;

    while (selectedOption != 0)
    {
        system("cls");
        cout << "\n**Menu Principal**\n";

        for (int i = 0; i < size; i++)
        {
            cout << i << " - " << menu[i] << endl;
        }

        cout << "\nDigite a opcao desejada: (0 - sair): ";
        cin >> selectedOption;
        cout << endl;

        int input = 0;
        switch (selectedOption)
        {
        case 0:
            break;
        case 1:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            input = get_number_dialog();
            insert_in_tree(&root,input);
            calc_fb(root);
            if(verify_avl_balance(root) != 0)
            {
                root = balance_tree_node(root);
                calc_fb(root);
            }
            break;
        case 2:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_pre_order(root);
            pause();
            break;
        case 3:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_in_simetric_order(root);
            pause();
            break;
        case 4:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_post_order(root);
            pause();
            break;
        case 5:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            if (is_empty_tree(root))
            {
                cout << "Arvore vazia." << endl;
                pause();
                break;
            }
            input = get_number_dialog();
            root = remove_node(&root, input);
            calc_fb(root);
            if(verify_avl_balance(root) != 0)
            {
                root = balance_tree_node(root);
                calc_fb(root);
            }
            pause();
            break;
        case 6:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            root = free_nodes(root);
            break;
        case 7:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            cout << "Altura da arvore: " << tree_height(root) << endl;
            pause();
            break;
        case 8:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_with_factor(root);
            pause();
            break;
        case 9:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            print_level_order(root);
            pause();
            break;
        default:
            system("cls");
            cout << "Opcao nao implementada. Tente novamente." << endl;
            break;
        }
    }
}

main()
{
    setlocale(LC_ALL, "Portuguese");

    int menu_size = 10;

    string menu[menu_size] =
    {
        "Sair",
        "Incluir (informar valor)",
        "Mostrar pre-ordem",
        "Mostrar ordem simetrica",
        "Mostrar pos-ordem",
        "Excluir um valor (informar valor)",
        "Limpar Arvore",
        "Altura da Arvore",
        "Mostra fator",
        "print_level_order",
    };

    Tree *root = NULL;

    show_menu(menu, menu_size, root);

    cout << "Programa encerrado. Goodbye!!!" << endl;

    return 0;
}
