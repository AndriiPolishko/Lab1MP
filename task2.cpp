#include <iostream>
#include <string>
#include <fstream>
int main() {
    std::ifstream fin("text.txt");
    if (!fin)
        std::cerr << "Cannot open text file" << '\n';
    int linesInPage = 45;
    std::string line, word;
    struct pair {
        std::string word = "";
        int counter = 0;
        int *pages = new int[1000];
        int pageNum = 0;
    };
    pair *dictionary = new pair[10000];
    int dictionarySize = 0, n = 10;
    //std::cout << "Enter number of words that you want to see: ";
    //std::cin >> n;
    bool flag = true;

    std::ifstream stopWords("stopWords.txt");
    if (!stopWords)
        std::cerr << "Cannot open stopWords file" << '\n';

    std::string stopWord;
    std::string stopWordsList[200];
    int stopWordIter = 0;
    bool stopFlag = true;

StopLbl:
    getline(stopWords, stopWord);
    stopWordsList[stopWordIter] = stopWord;
    stopWordIter += 1;
    if (!stopWords.eof())
        goto StopLbl;

std::string page="";
int pageNum = 0;

readFile:
    int lineCounter = 0;
    readPage:
      getline(fin, line);
      page+=line;
      lineCounter+=1;
      if(!fin.eof() && lineCounter % linesInPage != 0) {
        page+=" ";
        goto readPage;
      }
    pageNum+=1;
    int i = 0;
readWord:
    if ((int(page[i]) > 64 && int(page[i]) < 91) || (int(page[i]) > 96 && int(page[i]) < 123)) {
        char cymbol = page[i];
        if (int(cymbol) >= 64 && int(cymbol) <= 90)
            cymbol = char(int(cymbol) + 32);
        word += cymbol;
    }
    if (page[i] == ' ' || i + 1 == page.size())
    {
        int h = 0;

    checkStop:
        if (word == stopWordsList[h]) {
            h = stopWordIter;
            stopFlag = false;
        }
        h += 1;
        if (h < stopWordIter)
            goto checkStop;

        if (word != "" && stopFlag)
        {
            int j = 0;

        checkDict:

            if (dictionary[j].word == word) {
              if(dictionary[j].pages[dictionary[j].pageNum] != pageNum) {
                dictionary[j].pageNum += 1;
                dictionary[j].pages[dictionary[j].pageNum] = pageNum;
              }
                dictionary[j].counter += 1;
                flag = false;
            }
            j++;
            if (j < dictionarySize && flag == true)
                goto checkDict;

            if (flag == true)
            {
                dictionary[dictionarySize].word = word;
                dictionary[dictionarySize].counter = 1;
                dictionary[j].pages[0] = pageNum;
                dictionarySize += 1;
            }
        }
        stopFlag = true;
        word = "";
        flag = true;
    }

    i += 1;
    if (i < page.size())
        goto readWord;
    page = "";
    if (!fin.eof())
        goto readFile;

    if (n > dictionarySize)
        n = dictionarySize;

    int m = 0;
    pair temp;
outter:
    int t = 0;
inner:

    if (dictionary[t].word > dictionary[t + 1].word) {
        temp = dictionary[t];
        dictionary[t] = dictionary[t + 1];
        dictionary[t + 1] = temp;
    }
    t += 1;
    if (t < dictionarySize - m - 1)
        goto inner;
    m += 1;
    if (m < dictionarySize - 1)
        goto outter;

    int k = 0;
outputWords:
    if(dictionary[k].counter < 100) {
      std::cout << dictionary[k].word << ":";
      int pageIter = 0;

      outPages:
          std::cout << dictionary[k].pages[pageIter];
          pageIter+=1;

          if (pageIter <= dictionary[k].pageNum) {
            std::cout <<',';
            goto outPages;
          }
          std::cout<<"\n";
        }
    k++;
    if (k < n)
        goto outputWords;
    return 0;
}
