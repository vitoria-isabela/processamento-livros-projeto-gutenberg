
#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
#include <streambuf>
#include <bits/stdc++.h>
#include <vector>
#include "config.h"
#include "processaLivro.h"
#include "sort.h"

using namespace std;

// Construtor
ProcessBook::ProcessBook(string bookTxtFile, int hashfunctselec, int createHashReportLog)
{
    this->hashfunctselec = hashfunctselec;
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe String: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile, this->hashfunctselec);
    
  
}


ProcessBook::ProcessBook(string bookTxtFile, int createHashReportLog)
{
    this->createHashReportLog = createHashReportLog; 
    cout << "Recebe String: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile);
    
  
}

ProcessBook::ProcessBook(string bookTxtFile)
{
    cout << "Recebe String: " << bookTxtFile << endl;
    this->bookTxtFile = bookTxtFile;
    this->bookStream.open(this->bookTxtFile, ios::in);

    if (this->bookStream.is_open())
    {
        cout << "Livro aberto com sucesso" << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o livro" << endl;
        exit(-1);
    }
    processBookInsertsIntoHash(bookTxtFile);    
  
}

void ProcessBook::CloseBook()
{
    this->bookStream.close();   
  
}

ProcessBook::ProcessBook() {}

// Destrutor do livro
ProcessBook::~ProcessBook() 
{
   cout << "Destroi Livro " << bookTxtFile << endl;
   this->hashTableOfProcessBook->ClearHashTable();   
   this->bookStream.close();
   
}

// Converte uma palavra
void ProcessBook::convertWordToLowercase(string &word)
{
    for (size_t j = 0; j < word.length(); ++j)
    {
        word[j] = tolower(word[j]);
    }
}

// Remove as pontuações, se houver na palavra
void ProcessBook::removePontuation(string &word)
{
    word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
}

// Obtem o numero de linhas do livro
int ProcessBook::getNumberLines(string bookTxtFile)
{
    int numberOfLines = 0;
    this->bookSizeInLines = numberOfLines;
    string line;
    ifstream bookInputStream;

    bookInputStream.open(bookTxtFile, ios::in);

    if (!bookInputStream.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return -1;
    }

    if (bookInputStream.is_open())
    {
        while (!bookInputStream.eof())
        {
            getline(bookInputStream, line);
            cout << line << endl;
            numberOfLines++;
        }
        bookInputStream.close();

        numberOfLines--; // debugar essa linha
        return numberOfLines;
    }
    else
        return 0;
}

// lê o livro e realiza o tratamento de cada palavra para inseri-la na tabela hash
void ProcessBook::processBookInsertsIntoHash(string bookTxtFile)
{
    // cria uma tabela hash
    HashTable *hashTable = new HashTable(50001, 3);
    this->hashTableOfProcessBook = hashTable;

    ifstream arq;
    arq.open(bookTxtFile, ios::in);

    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);

            if (tokenStopWord.length() > 3)
                // insere palavra na tabela hash
                hashTableOfProcessBook->insertKey(tokenStopWord);
        }
    }
    hashToVector();
    
}

void ProcessBook::processBookInsertsIntoHash(string bookTxtFile, int hashfuncselect)
{
    // cria uma tabela hash
    HashTable *hashTable = new HashTable(50001, hashfuncselect, this->createHashReportLog);
    this->hashTableOfProcessBook = hashTable;

    ifstream arq;
    arq.open(bookTxtFile, ios::in);

    if (!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
    }

    string line;
    string fileContents;

    // Extrai caracteres de arq e os armazena em line até que o caractere de nova linha, '\n', seja encontrado
    while (getline(arq, line))
    {
        // Convertendo a linha para objeto stringstream (ss vai armazenar uma linha)
        stringstream ss(line);

        string tokenStopWord;
        while (getline(ss, tokenStopWord, ' '))
        {
            // realiza os tratamentos na palavra
            convertWordToLowercase(tokenStopWord);
            removePontuation(tokenStopWord);

            if (tokenStopWord.length() > 3)
                // insere palavra na tabela hash
                hashTableOfProcessBook->insertKey(tokenStopWord);
        }
    }
    
    hashTableOfProcessBook->displayInfo();
    hashTableOfProcessBook->displayOnlyInfo(hashfuncselect);
}

bool compareByOccurrences(HashEntry &a, HashEntry &b)
{
    return a.getOccurrencies() > b.getOccurrencies();
}

// Passa para um vetor (a ser ordenado) as palavras da tabela hash.
void ProcessBook::hashToVector()
{
    // contador de posições de todas as listas em todos os buckets
    int counter = 0;
    int sizeOfhashTableOfProcessBook = hashTableOfProcessBook->getWordsCounter();
    // Cria uma lista
    LinkedList<HashEntry> *hashEntry;

    HashEntry *auxVector = new HashEntry[sizeOfhashTableOfProcessBook];

    // percorre tabela hash
    for (int i = 0; i < hashTableOfProcessBook->getTam(); i++)
    {
        // verifica se posição i do bucket é nula
        if (hashTableOfProcessBook->getPosition(i) != nullptr)
        {
            // acessando lista no indice
            hashEntry = hashTableOfProcessBook->getPosition(i);

            // percorre a lista do bucket no indice j
            for (int j = 0; j < hashEntry->length(); j++)
            {
                // verifica se a lista do bucket na posição j está vazio
                if (!hashEntry->empty())
                {

                    // adicionando os dados da lista, naquele indice, no vetor
                    auxVector[counter] = hashEntry->get(j);
                    // incrementa o contador para ir para as próximas posições do vetor
                    counter++;
                }
            }
        }
    }
    this->vectorList = auxVector;
}

void ProcessBook::sortVector(sorting_method sortMethod)
{
   switch (sortMethod)
    {
    case MERGESORT:
        merge_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;   
    case QUICKSORT:
        quick_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;
    case SHELLSORT:
        shell_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences, this->createHashReportLog);
        
        break;
    }
    
    displaySortVector();

}

void ProcessBook::displaySortVector()
{       
    string dir = SORTMETHOD + to_string(this->createHashReportLog) + "sort_results.txt";
    cout << "Diretorio do report: -> " << dir << endl;
    this->sortReport.open(dir, ios::out | ios::app );    
    
    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;
    this->sortReport << "IMPRIMINDO AS 50 PALAVRAS DE MAIORES OCORRENCIAS DE CADA VETOR ORDENADO: " << endl;
    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;
   
    
    for (int i = 0; i < 50; i++)
    {
        this->sortReport << endl
        << " Numero de Ocorrencias da palavra \"" << this->vectorList[i].getKey() << "\": " << this->vectorList[i].getOccurrencies() << endl;
    }
    this->sortReport << ">>>>>>>>>>>>>>>>>>>>" << endl;

}

HashEntry* ProcessBook::getVector50()
{
    fstream printSortBook;
    

    HashEntry* vectorOut = new HashEntry[50];
    shell_sort<HashEntry>(this->vectorList, hashTableOfProcessBook->getWordsCounter(), compareByOccurrences);
    for (int i = 0; i < 50; i++)
    {
       vectorOut[i] = this->vectorList[i];

    }
     
    string dir = CASO4 + to_string(this->createHashReportLog) + "book_words.txt";
    cout << "Diretorio do report: -> " << dir << endl;
    printSortBook.open(dir, ios::out | ios::app );    
    
    printSortBook << "---------------------------------------------------------------------------" << endl;
    printSortBook << "IMPRIMINDO AS 50 PALAVRAS DE MAIORES OCORRENCIAS DE CADA VETOR ORDENADO: " << endl;
    printSortBook << "---------------------------------------------------------------------------" << endl;
   
    
    for (int i = 0; i < 50; i++)
    {
        printSortBook << endl
        << " Numero de Ocorrencias da palavra \"" << vectorOut[i].getKey() << "\": " << vectorOut[i].getOccurrencies() << endl;
    }
    printSortBook << "---------------------------------------------------------------------------" << endl;
    printSortBook.close();    
    return vectorOut;
}


