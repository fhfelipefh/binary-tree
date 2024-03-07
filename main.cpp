#include <iostream>
using namespace std;

#include "functions-binary-tree.hpp"

string mainMenu[] = {
    "Sair",
    "Incluir",
    "Mostrar pré-ordem",
    "Mostrar ordem simétrica",
    "Mostrar pós-ordem"
};

int main()
{
    // 0 - Sair
    // 1 - Incluir
    // 2 - Mostrar pré-ordem
    // 3 - Mostrar ordem simêtrica
    // 4 - Mostrar pós-ordem

    setlocale(LC_ALL, "Portuguese");
    cout << "Hello world!" << endl;
    return 0;
}

void showMenu() {
    cout << "***** Menu *****" << endl;
    for (int i = 0; i < sizeof(mainMenu) / sizeof(mainMenu[0]); ++i) {
        cout << i + 1 << " - " << mainMenu[i] << endl;
    }
    cout << "*****************" << endl;
}