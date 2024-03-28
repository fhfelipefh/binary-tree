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

struct Aluno
{
    int matricula;
    string nome;
    float media;
    float frequencia;
};

struct Tree
{
    Aluno info;
    int fb;
    Tree *stl;
    Tree *str;
};

int is_empty_tree(Tree *tree)
{
    if (tree == NULL)
        return 1;
    if (tree->info.matricula == 0 && tree->info.nome.empty())
        return 1;
    return 0;
}

int get_highest_matricula(Tree *tree)
{
    if (tree == NULL)
        return 0;

    int highest_matricula = 0;
    while (tree != NULL)
    {
        highest_matricula = tree->info.matricula;
        tree = tree->str;
    }
    return highest_matricula;
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

int factor_balance(Tree *root)
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
        root->fb = factor_balance(root);
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

Tree* balance_tree_node(Tree *root )
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

    int factor = factor_balance(root);

    if (factor >= 2)
    {
        if (factor_balance(root->stl) <= -1 )
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
        if (factor_balance(root->str) >= 1 )
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

void insert_in_tree(Tree **pTree, Aluno value)
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
        if(value.matricula < (*pTree)->info.matricula)
            insert_in_tree(&(*pTree)->stl, value);
        else
            insert_in_tree(&(*pTree)->str, value);
    }
}

void insert_and_balance(Tree **root, string studentName, double media, double frequency)
{
    Aluno new_node;
    new_node.matricula = get_highest_matricula(*root) + 1;
    new_node.nome = studentName;
    new_node.media = media;
    new_node.frequencia = frequency;

    insert_in_tree(root, new_node);
    calc_fb(*root);
    if (verify_avl_balance(*root) != 0)
    {
        *root = balance_tree_node(*root);
        calc_fb(*root);
    }
}

Tree* remove_student(Tree **pTree, int matricula)
{
    if (*pTree == NULL)
        return NULL;

    if (matricula < (*pTree)->info.matricula)
        (*pTree)->stl = remove_student(&((*pTree)->stl), matricula);
    else if (matricula > (*pTree)->info.matricula)
        (*pTree)->str = remove_student(&((*pTree)->str), matricula);
    else
    {
        Tree *aux = *pTree;
        if ((*pTree)->stl == NULL)
        {
            *pTree = (*pTree)->str;
            delete aux;
        }
        else if ((*pTree)->str == NULL)
        {
            *pTree = (*pTree)->stl;
            delete aux;
        }
        else
        {
            aux = (*pTree)->stl;
            while (aux->str != NULL)
                aux = aux->str;
            (*pTree)->info = aux->info;
            (*pTree)->stl = remove_student(&((*pTree)->stl), aux->info.matricula);
        }
    }
    return *pTree;
}

void show_students(Tree *root)
{
    if (root != NULL)
    {
        cout << "Matricula: " << root->info.matricula << endl;
        cout << "Nome: " << root->info.nome << endl;
        cout << "Media: " << root->info.media << endl;
        cout << "Frequencia: " << root->info.frequencia << endl;
        cout << "FB: " << root->fb << endl;
        cout << endl;

        show_students(root->stl);
        show_students(root->str);
    }
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

void studentsApproved(Tree *root)
{
    if (root != NULL)
    {
        if (root->info.media >= 6 && root->info.frequencia >= 75)
        {
            cout << "Matricula: " << root->info.matricula << endl;
            cout << "Nome: " << root->info.nome << endl;
            cout << "Media: " << root->info.media << endl;
            cout << "Frequencia: " << root->info.frequencia << endl;
            cout << endl;
        }

        studentsApproved(root->stl);
        studentsApproved(root->str);
    }
}

void show_pre_order(Tree *tree)
{
    cout << "<";
    if(!is_empty_tree(tree))
    {
        cout << tree->info.matricula;
        show_pre_order(tree->stl);
        show_pre_order(tree->str);
    }
    cout << ">";
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
        string studentName = "";
        double media = 0.0;
        double frequency = 0.0;
        switch (selectedOption)
        {
        case 0:
            break;
        case 1:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            cout << "Informe o nome do aluno: " << endl;
            cin.ignore();
            getline(cin, studentName);
            cout << "Informe a media do aluno: " << endl;
            cin >> media;
            cout << "Informe a frequencia do aluno: " << endl;
            cin >> frequency;
            insert_and_balance(&root, studentName, media, frequency);
            break;
        case 2:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            show_students(root);
            show_pre_order(root);
            pause();
            break;
        case 3:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            cout << "Informe a matricula do aluno a ser excluido: " << endl;
            cin >> input;
            remove_student(&root, input);
            break;
        case 4:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            root = free_nodes(root);
            break;
        case 5:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            cout << "Altura da arvore: " << tree_height(root) << endl;
            pause();
            break;
        case 6:
            system("cls");
            cout << "--- " << menu[selectedOption] << " ---" << endl;
            studentsApproved(root);
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

    int menu_size = 7;

    string menu[menu_size] =
    {
        "Sair",
        "Incluir (informar o aluno)",
        "Mostrar",
        "Excluir um valor (informar valor)",
        "Limpar Arvore",
        "Altura da Arvore",
        "apresentar os alunos aprovados (media >= 6 e frequencia >= 75)",
    };

    Tree *root = NULL;

    show_menu(menu, menu_size, root);

    cout << "Programa encerrado. Goodbye!!!" << endl;

    return 0;
}
