#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

const std::map<char, std::string> alphabet = {{'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"}, {'Z', "--.."}};

const std::map<char, std::string> numerals = {{'1',".----"}, {'2',"..---"}, {'3',"...--"}, {'4',"....-"}, {'5',"....."},
    {'6',"-...."}, {'7',"--..."}, {'8',"---.."}, {'9',"----."}, {'0',"-----"}};

void display(std::string ascii, std::string morse)
{
    std::cout << "Original: " << ascii << std::endl;
    std::cout << "Morse: " << morse << std::endl;
}

std::string parseLine(std::string input)
{
    std::string morse;
    std::string space = " ";
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    for(auto it = input.begin(); it != input.end(); ++it)
    {
        if(isupper(*it))
            morse.append(alphabet.find(*it)->second);
        else if(isdigit(*it))
            morse.append((numerals.find(*it)->second));
        morse.append(space);
    }
    return morse;
}

void parseDocument(const char *filename)
{
    std::ifstream inputFile;
    std::string asciiSentence;
    std::string finalSentence;
    std::string morseSentence;

    inputFile.open(filename);
    
    if(!inputFile.is_open())
    {
        std::cerr << "error opening " << filename << std::endl;
        return;
    }

    while(!inputFile.eof())
    {
        std::getline(inputFile, asciiSentence);
        if(!asciiSentence.empty())
        {
            finalSentence.append(asciiSentence);
            finalSentence.append("\n");
            morseSentence.append(parseLine(asciiSentence));
            morseSentence.append("\n");
        }
    }
    // get rid of trailing \n
    finalSentence.erase(finalSentence.end()-1);
    morseSentence.erase(morseSentence.end()-1);
    display(finalSentence, morseSentence);
    inputFile.close();
}

int main(int argc, char** argv)
{
    std::string input;
    if(argc < 2)
    {
        std::cout << "Ctrl+D to exit." << std::endl;
        std::cout << "You can also read a file using: " << argv[0] << " input_file" << std::endl << "> ";
        while(std::getline(std::cin, input))
        {
            display(input, parseLine(input));
            std::cout << "> ";
        }
        std::cout << std::endl;
    }
    else
        parseDocument(argv[1]);
    return 0;
}
