#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <filesystem>

#include "config.h"

#include "processaLivro.h"

// Função Main que chama os livros
int main(int argc, char *argv[])
{
    ifstream file;

    file.open("input.txt");

    if (!file.is_open())
        cout << "Arquivo não aberto!" << endl;

    vector<string> booksName;
    while (!file.eof())
    {
        string name;

        // leitura do livro
        getline(file, name);
        // inserindo no vetor os nomes dos arquivos
        booksName.push_back(name);
    }
    int sizeVector = booksName.size();

    ProcessBook **books = new ProcessBook *[sizeVector];

    for (int i = 0; i < sizeVector; i++)
    {
        // acessando books (que armazena os livros e passando para o construtor da processaLivro)
        books[i] = new ProcessBook(booksName[i]);
    }
    return 0;
}