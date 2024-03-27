#include <iostream>
#include <windows.h>
#include <locale>
#include <limits>
#include <algorithm>
#include <sstream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct Tree
{
    int info;
    int fb;
    Tree *stl;
    Tree *str;
};

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

int is_empty_tree(Tree *tree)
{
    if(tree == NULL)
        return 1;
    if(tree->info == NULL)
        return 1;
    return 0;
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

int count_nodes_with_fb_minus_one(Tree *root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->fb == -1) {
        count++;
    }
    count += count_nodes_with_fb_minus_one(root->stl);
    count += count_nodes_with_fb_minus_one(root->str);
    return count;
}

int count_nodes_with_fb_plus_one(Tree *root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->fb == 1) {
        count++;
    }
    count += count_nodes_with_fb_plus_one(root->stl);
    count += count_nodes_with_fb_plus_one(root->str);
    return count;
}

int count_nodes_with_fb_zero(Tree *root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->fb == 0) {
        count++;
    }
    count += count_nodes_with_fb_zero(root->stl);
    count += count_nodes_with_fb_zero(root->str);
    return count;
}

Tree* findNode(Tree* root, int value) {
    if (root == NULL || root->info == value)
        return root;
    if (root->info < value)
        return findNode(root->str, value);
    return findNode(root->stl, value);
}

void show_descendants(Tree *root, int value) {
    Tree* node = findNode(root, value);

    if (node == NULL) {
        cout << "Nao encontrado na arvore." << endl;
        return;
    }

    if (node->stl != NULL) {
        cout << "Descendente a esquerda: " << node->stl->info << endl;
    }
    if (node->str != NULL) {
        cout << "Descendente a direita: " << node->str->info << endl;
    }
}

void processInputLine(Tree **tree, string action, int value)
{
    int declaredOperation = 0;

    if (action == "Incluir")
    {
        declaredOperation = 1;
    }
    else if (action == "Remover")
    {
        declaredOperation = 2;
    }
    else if (action == "Mostrar")
    {
      declaredOperation = 3;
    }
    else
    {
        cout << "Operacao nao reconhecida" << endl;
        return;
    }

    switch (declaredOperation)
    {
    case 1:
            // Insere e faz o balanco
            insert_and_balance(tree, value);
        break;
    case 2:
        if (tree != NULL)
        {
            // Remove e faz o balanco
            remove_and_balance(tree, value);
        }
        break;
    case 3:
        // Mostrar e faz o balanco
        if (tree != NULL)
        {
            if (value == 1) {
                // (exibe a árvore em pré-ordem)
                show_pre_order(*tree);
            } else if (value == 2) {
                // (exibe a árvore em ordem simétrica)
                show_in_simetric_order(*tree);
            } else {
                // Não implementado
            }
        }
        break;
    default:
        cout << "Nao implementado" << endl;
        break;
    }
}

string processInputFile(Tree **tree, string file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        return "O arquivo " + file_name + " nao foi encontrado";
    }
    else
    {
        string line;
        while (getline(file, line))
        {
            string action;
            int value;
            stringstream ss(line);
            ss >> action >> value;
            processInputLine(tree, action, value);
        }
    }

    file.close();

    return "\nProcessamento finalizado";
}

string show_file_process_result(Tree **tree, string file_name)
{
    string process_result = processInputFile(tree, file_name);
    cout << process_result << endl;
    return process_result;
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
        default:
            system("cls");
            cout << "Opcao nao implementada. Tente novamente." << endl;
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int menu_size = 4;

    string menu[menu_size] =
    {
        "Sair",
        "Funcao que apresente a quantidade de nós com FB = -1",
        "Funcao que apresente a quantidade de nós com FB = +1",
        "Funcao que apresente a quantidade de nós com FB = 0",
        "Funcao que recebe um valor qualquer e apresenta os descendentes deste no",
        "Funcao que le um arquivo texto e realize as acoes descritas no arquivo, seguindo o seguinte formato",
    };

    Tree *root = NULL;

    show_menu(menu, menu_size, root);

    cout << "Programa encerrado. Goodbye!!!" << endl;

    return 0;
}
