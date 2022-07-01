#ifndef PROCESSALIVRO_H
#define PROCESSALIVRO_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "hash.h"

class ProcessBook
{
private:
    // tamanho do livro contado em linhas
    int bookSizeInLines;

    // arquivo do livro em txt
    string bookTxtFile;

    // arquivo do livro em ascii
    fstream bookStream; // fstream do livro

    //Report dos Metodos de Ordenação
    fstream sortReport;
    
    //seletor da funcao hash
    int hashfunctselec;

    //cria diertorio para hash report log
    int createHashReportLog = 0;

public:
    // Construtor
    ProcessBook(string bookTxtFile);
    ProcessBook(string bookTxtFile, int createHashReportLog);
    ProcessBook(string bookTxtFile,  int hashfuncselect , int createHashReportLog);
    ProcessBook();

    // Destrutor
    ~ProcessBook();
    //Fecha Livro
    void CloseBook();
    // Transformar texto para letras minúsculas
    void convertWordToLowercase(string &word);
    // Remove pontuações
    void removePontuation(string &word);

    void stripPunct(string &word);

    // obter numero de linhas do livro
    int getNumberLines(string bookTxtFile);

    // lê o livro e realiza o tratamento de cada palavra para inseri-la na tabela hash
    void processBookInsertsIntoHash(string bookTxtFile);
    void processBookInsertsIntoHash(string bookTxtFile, int hashfuncselect);

    // Passa para um vetor (a ser ordenado) as palavras da tabela hash.
    void hashToVector();

    void sortVector(sorting_method sortMethod);
   
    // exibe as 50 palavras que mais se repetem em cada
    void displaySortVector();
    
    HashTable *hashTableOfProcessBook;

    // vetor usado para ordenar as listas
    HashEntry *vectorList;
    
    HashEntry* getVector50();

    HashEntry *List;

    // vetor para armazenar todos os vetores refrentes a cada livro;
    HashEntry *vectorOfVectors;

#pragma region getters_e_setters
    // getters
    int getSizeBookInLines();
    // setters
    void setSizeBookInLines(int bookSizeInLines);

#pragma endregion getters_e_setters
};

#endif /* PROCESSALIVRO_H */
