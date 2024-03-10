#include <iostream>
#include <windows.h>
#include <locale>
using namespace std;

struct Tree {
    int info;
    Tree *stl; // left
    Tree *str; // right
};

int is_empty_tree(Tree *tree)
{
    if(tree == NULL)
        return 1;
    if(tree->info == NULL)
        return 1;
    return 0;
}

void insert_in_tree(Tree **pTree, int num) {
    if (*pTree == NULL) {
        *pTree = new Tree;
        (*pTree)->stl = NULL;
        (*pTree)->str = NULL;
        (*pTree)->info = num;
    } else {
        if (num < (*pTree)->info)
            insert_in_tree(&(*pTree)->stl, num);
        else
            insert_in_tree(&(*pTree)->str, num);

    }
}

void show_pre_order(Tree *tree)
{
    cout << "<";
    if(!is_empty_tree(tree))
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
    if(!is_empty_tree(tree))
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
    if(!is_empty_tree(tree))
    {
        show_post_order(tree->stl);
        show_post_order(tree->str);
        cout << tree->info;
    }
    cout << ">";
}

Tree* remove(Tree **pTree, int num)
{
    if(num < (*pTree)->info)
        remove(&(*pTree)->stl, num);
    else if(num > (*pTree)->info)
        remove(&(*pTree)->str, num);
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
            aux->str = NULL;
            delete(aux);
            aux = NULL;
        }else if((*pTree)->str == NULL)
        {
            (*pTree) = (*pTree)->stl;
            aux->stl = NULL;
            delete(aux);
            aux = NULL;
        }
        else
        {
            aux = (*pTree)->stl;
            while(aux->str != NULL)
            {
                aux = aux->str;
            }
            (*pTree)->info = aux->info;
            aux->info = num;
            (*pTree)->stl = remove(&(*pTree)->stl, num);
        }
    }
    return (*pTree);
}

int find_left_sub_tree_height(Tree *tree);
int find_right_sub_tree_height(Tree *tree);

int find_right_sub_tree_height(Tree *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        return max(find_left_sub_tree_height(tree->stl), find_right_sub_tree_height(tree->str)) + 1;
    }
}

int find_left_sub_tree_height(Tree *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        return max(find_left_sub_tree_height(tree->stl), find_right_sub_tree_height(tree->str)) + 1;
    }
}

int show_left_sub_tree_height(Tree *tree) {
    int height = find_left_sub_tree_height(tree->stl);
    cout << "Altura da sub-arvore esquerda: " << height << endl;
    return height;
}

int show_right_sub_tree_height(Tree *tree) {
    int height = find_right_sub_tree_height(tree->str);
    cout << "Altura da sub-arvore direita: " << height << endl;
    return height;
}

int get_number_dialog() {
    int num;
    cout << "Digite um numero: ";
    cin >> num;
    return num;
}

void pause() {
    cout << "\n" << endl;
    system("pause");
}

void show_menu(string menu[], int size, Tree *root) {
    int selectedOption = -1;

    while (selectedOption != 0) {
        system("cls");
        cout << "\n**Menu Principal**\n";

        for (int i = 0; i < size; i++) {
            cout << i << " - " << menu[i] << endl;
        }

        cout << "\nDigite a opcao desejada: (0 - sair): ";
        cin >> selectedOption;
        cout << endl;

        int input = 0;
        switch (selectedOption) {
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
                pause();
                break;
            case 7:
                system("cls");
                cout << "--- " << menu[selectedOption] << " ---" << endl;
                pause();
                break;
            case 8:
                system("cls");
                cout << "--- " << menu[selectedOption] << " ---" << endl;
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

    int menu_size = 8;

    string menu[menu_size] = {
        "Sair",
        "Incluir",
        "Mostrar pre-ordem",
        "Mostrar ordem simetrica",
        "Mostrar pos-ordem",
        "Encontrar a altura da sub-arvore esquerda e direita",
        "Encontrar a altura da arvore",
        "Limpar todos os nos da arvore, liberando as respectivas memorias",
        "Dado um determinado valor, se o mesmo estiver contido na arvore encontrar o nivel que ele se encontra"
    };

    Tree *root = nullptr;

    show_menu(menu, menu_size, root);

    cout << "Programa encerrado. Goodbye!!!" << endl;

    return 0;
}
