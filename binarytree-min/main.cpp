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
    Tree *stl; // left
    Tree *str; // right
};

int is_empty_tree(Tree *tree)
{
    if (tree == NULL)
        return 1;
    if (tree->info == NULL)
        return 1;
    return 0;
}

void insert_in_tree(Tree **pTree, int num)
{
    if (*pTree == NULL)
    {
        *pTree = new Tree;
        (*pTree)->stl = NULL;
        (*pTree)->str = NULL;
        (*pTree)->info = num;
    }
    else
    {
        if (num < (*pTree)->info)
            insert_in_tree(&(*pTree)->stl, num);
        else
            insert_in_tree(&(*pTree)->str, num);

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

Tree *remove_tree_item(Tree **pTree, int num)
{
    if (num < (*pTree)->info)
        remove_tree_item(&(*pTree)->stl, num);
    else if (num > (*pTree)->info)
        remove_tree_item(&(*pTree)->str, num);
    else
    {
        Tree *aux = *pTree;
        if (((*pTree)->stl == NULL) && ((*pTree)->str == NULL))
        {
            delete (aux);
            (*pTree) = NULL;
        }
        else if ((*pTree)->stl == NULL)
        {
            (*pTree) = (*pTree)->str;
            aux->str = NULL;
            delete (aux);
            aux = NULL;
        }
        else if ((*pTree)->str == NULL)
        {
            (*pTree) = (*pTree)->stl;
            aux->stl = NULL;
            delete (aux);
            aux = NULL;
        }
        else
        {
            aux = (*pTree)->stl;
            while (aux->str != NULL)
            {
                aux = aux->str;
            }
            (*pTree)->info = aux->info;
            aux->info = num;
            (*pTree)->stl = remove_tree_item(&(*pTree)->stl, num);
        }
    }
    return (*pTree);
}

int find_left_sub_tree_height(Tree *tree);

int find_right_sub_tree_height(Tree *tree);

int find_right_sub_tree_height(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        return max(find_left_sub_tree_height(tree->stl), find_right_sub_tree_height(tree->str)) + 1;
    }
}

int find_left_sub_tree_height(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    else
    {
        return max(find_left_sub_tree_height(tree->stl), find_right_sub_tree_height(tree->str)) + 1;
    }
}

int show_left_sub_tree_height(Tree *tree)
{
    if (is_empty_tree(tree))
    {
        return 0;
    }
    int height = find_left_sub_tree_height(tree->stl);
    cout << "Altura da sub-arvore esquerda: " << height << endl;
    return height;
}

int show_right_sub_tree_height(Tree *tree)
{
    if (is_empty_tree(tree))
    {
        return 0;
    }
    int height = find_right_sub_tree_height(tree->str);
    cout << "Altura da sub-arvore direita: " << height << endl;
    return height;
}

int find_tree_height(Tree *tree)
{
    if (is_empty_tree(tree))
    {
        return 0;
    }

    if (tree == nullptr)
    {
        return 0;
    }
    else
    {
        int left_height = find_tree_height(tree->stl);
        int right_height = find_tree_height(tree->str);
        return max(left_height, right_height) + 1;
    }
}

void show_tree_height(Tree *tree)
{
    int height = find_tree_height(tree);
    cout << "Altura da arvore: " << height << endl;
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

int get_element_level(Tree *tree, int num)
{
    int level = 0;
    Tree *current = tree;

    while (current != NULL)
    {
        if (num == current->info)
        {
            cout << "O numero " << num << " esta no nivel " << level << endl;
            return level;
        }
        else if (num < current->info)
        {
            current = current->stl;
        }
        else
        {
            current = current->str;
        }
        level++;
    }

    cout << "O numero " << num << " nao esta na arvore" << endl;
    return -1;
}

void processInputLine(Tree **tree, string action, int value)
{
    int declaredOperation = 0;

    if (action == "inserir")
    {
        declaredOperation = 1;
    }
    else if (action == "remover")
    {
        declaredOperation = 2;
    }
    else
    {
        cout << "Operacao nao reconhecida" << endl;
        return;
    }

    switch (declaredOperation)
    {
    case 1:
        insert_in_tree(tree, value);
        break;
    case 2:
        if (tree != NULL)
        {
            remove_tree_item(tree, value);
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

int get_number_of_nodes(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    return 1 + get_number_of_nodes(tree->stl) + get_number_of_nodes(tree->str);
}

void show_number_of_nodes(Tree *tree)
{
    int count = get_number_of_nodes(tree);
    cout << "A quantidade de nos da arvore e: " << count << endl;
}

int get_number_of_leaves(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }

    if (tree->stl == NULL && tree->str == NULL)
    {
        return 1;
    }

    return get_number_of_leaves(tree->stl) + get_number_of_leaves(tree->str);
}

void show_number_of_leaves(Tree *tree)
{
    int count = get_number_of_leaves(tree);
    cout << "A quantidade de folhas da arvore e: " << count << endl;
}

int get_max_level_in_tree(Tree *tree)
{
    if (tree == NULL)
    {
        return -1;
    }

    int left_level = get_max_level_in_tree(tree->stl);
    int right_level = get_max_level_in_tree(tree->str);

    return max(left_level, right_level) + 1;
}

void show_max_level_in_tree(Tree *tree)
{
    int max_level = get_max_level_in_tree(tree);
    cout << "O maior nivel na arvore é: " << max_level << endl;
}

bool is_complete_tree(Tree* tree)
{
    if (tree == NULL) {
       return true;
    }

    int left_height = find_tree_height(tree->stl);
    int right_height = find_tree_height(tree->str);

    if (left_height == right_height)
    {
        return is_complete_tree(tree->stl) && is_complete_tree(tree->str);
    }
    else
    {
        return false;
    }
}

void show_if_tree_is_complete(Tree *tree)
{
    bool is_complete = is_complete_tree(tree);
    if (is_complete)
    {
        cout << "Arvore e completa." << endl;
    }
    else
    {
        cout << "Arvore nao e completa." << endl;
    }
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
            insert_in_tree(&root, input);
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
            show_left_sub_tree_height(root);
            show_right_sub_tree_height(root);
            pause();
            break;
        case 6:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_tree_height(root);
            pause();
            break;
        case 7:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            root = free_nodes(root);
            break;
        case 8:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            input = get_number_dialog();
            get_element_level(root, input);
            pause();
            break;
        case 9:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_file_process_result(&root, "entrada.txt");
            pause();
            break;
        case 10:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_number_of_leaves(root);
            pause();
            break;
        case 11:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_max_level_in_tree(root);
            pause();
            break;
        case 12:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_if_tree_is_complete(root);
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

    int menu_size = 14;

    string menu[menu_size] =
    {
        "Sair",
        "Incluir",
        "Mostrar pre-ordem",
        "Mostrar ordem simetrica",
        "Mostrar pos-ordem",
        "Encontrar a altura da sub-arvore esquerda e direita",
        "Encontrar a altura da arvore",
        "Limpar todos os nos da arvore, liberando as respectivas memorias",
        "Dado um determinado valor, se o mesmo estiver contido na arvore encontrar o nivel que ele se encontra",
        "Processar arquivo entrada.txt",
        "Apresentar o total de elementos folhas existentes na arvore",
        "Mostrar o maior nivel existente na arvore",
        "Verificar se a arvore e uma arvore completa, exibindo uma mensagem com tal informacao",
        "Exibir a árvore usando paragrafação"
    };

    Tree *root = nullptr;

    show_menu(menu, menu_size, root);

    cout << "Programa encerrado. Goodbye!!!" << endl;

    return 0;
}
