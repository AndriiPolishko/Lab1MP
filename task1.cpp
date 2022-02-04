#include <iostream>
#include <string>
#include <fstream>
int main() {
    std::ifstream fin("text.txt");
    if (!fin)
        std::cerr << "Cannot open text file" << '\n';

    std::string line, word;
    struct pair {
        std::string word;
        int counter;
    };
    pair dictionary[10000];
    int dictionarySize = 0,n = 10;
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
    if(!stopWords.eof())
      goto StopLbl;

readFile:
    getline(fin, line);
    int i = 0;
    readWord:
        //if ( line[i] != ' ') {
        if( (int(line[i]) > 64 && int(line[i]) < 91) || (int(line[i]) > 96 && int(line[i]) < 123) ){
            char cymbol = line[i];
            if (int(cymbol) >= 64 && int(cymbol) <= 90)
                cymbol = char(int(cymbol) + 32);
            word += cymbol;
        }
        if (line[i] == ' ' || i + 1 == line.size())
        {
          int h = 0;
          checkStop:
            if(word == stopWordsList[h]) {
              h = stopWordIter;
              stopFlag = false;
            }
            h += 1;
            if(h<stopWordIter)
              goto checkStop;

            if (word != "" && stopFlag)
            {
                int j = 0;
                checkDict:
                    if (dictionary[j].word == word) {
                        dictionary[j].counter += 1;
                        flag = false;
                    }
                j++;
                if(j< dictionarySize && flag == true)
                    goto checkDict;

                if (flag == true)
                {
                    dictionary[dictionarySize].word = word;
                    dictionary[dictionarySize].counter = 1;
                    dictionarySize += 1;
                }
            }
            stopFlag = true;
            word = "";
            flag = true;
        }

    i += 1;
    if (i < line.size())
        goto readWord;
    if (!fin.eof())
        goto readFile;

    if (n > dictionarySize)
        n = dictionarySize;

    int m = 0;
    pair temp;
    outter:
        int t = 0;
        inner:

        if (dictionary[t].counter < dictionary[t + 1].counter) {
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
        std::cout << dictionary[k].word << ":" << dictionary[k].counter << '\n';
        k++;
        if(k<n)
            goto outputWords;
    return 0;
}
