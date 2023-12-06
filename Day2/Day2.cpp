#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;
int
twoDigitConversion(char *num){
    int result = 0;
    if (num[0] == '0'){
        result = num[1] - 48;
    }
    else{
        result = (num[0] - 48) * 10 + (num[1] - 48);
    }
    return result;
}

int
getGame(string line){
    char gameNum[3] = {'0', '0', '0'};
    /*GAME COUNTER */
    gameNum[0] = {'0'};
    gameNum[1] = {'0'};
    gameNum[2] = {'0'};
    int colonPosition = line.find(':');
    if (line.at(colonPosition - 3) == ' ' || line.at(colonPosition - 3) == 'e') {
        if (line.at(colonPosition-2) == ' '){
            gameNum[2] = line.at(colonPosition-1);
        }
        else{
            gameNum[1] = line.at(colonPosition-2);
            gameNum[2] = line.at(colonPosition-1);
        }
    }
    else{
        gameNum[0] = line.at(colonPosition-3);
        gameNum[1] = line.at(colonPosition-2);
        gameNum[2] = line.at(colonPosition-1);
    }
    return (gameNum[0] - 48) * 100 + (gameNum[1] - 48) * 10 + (gameNum[2] - 48);
}

int main(){
    /*12 red 13 green 14 blue max*/
    std::ifstream infile("Day2.txt");
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    int sum = 0;
    for( std::string line; getline( infile, line ); ){
        int gameNumInt = getGame(line);
        char numColours[2];
        string line2 = line;

        int maxRed = 1;
        int maxGreen = 1;
        int maxBlue = 1;
        /*ALGORITHM*/
        /*Reds */
        while(line2.find("red") != std::string::npos){
            numColours[0] = '0';
            numColours[1] = '0';
            if (line2.at(line2.find("red") - 3) != ' ') {
                numColours[0] = line2.at(line2.find("red") - 3);
                numColours[1] = line2.at(line2.find("red") - 2);
            }
            else{
                numColours[1] = line2.at(line2.find("red") - 2);
            }
            line2.replace(line2.find("red"), 3, "");
            if (twoDigitConversion(numColours) > maxRed){
                maxRed = twoDigitConversion(numColours);
            }
        }
        line2 = line;
        while(line2.find("green") != std::string::npos){
            numColours[0] = '0';
            numColours[1] = '0';
            if (line2.at(line2.find("green") - 3) != ' ') {
                numColours[0] = line2.at(line2.find("green") - 3);
                numColours[1] = line2.at(line2.find("green") - 2);
            }
            else{
                numColours[1] = line2.at(line2.find("green") - 2);
            }
            line2.replace(line2.find("green"), 5, "");
            if (twoDigitConversion(numColours) > maxBlue){
                maxBlue = twoDigitConversion(numColours);
            }
        }
        line2 = line;
        while(line2.find("blue") != std::string::npos){
            numColours[0] = '0';
            numColours[1] = '0';
            if (line2.at(line2.find("blue") - 3) != ' ') {
                numColours[0] = line2.at(line2.find("blue") - 3);
                numColours[1] = line2.at(line2.find("blue") - 2);
            }
            else{
                numColours[1] = line2.at(line2.find("blue") - 2);
            }
            line2.replace(line2.find("blue"), 4, "");
            if (twoDigitConversion(numColours) > maxGreen){
                maxGreen = twoDigitConversion(numColours);
            }
        }
        cout << " Red: " << maxRed << " Green: " << maxGreen << " Blue: " << maxBlue << endl;
        sum += (maxRed * maxBlue * maxGreen);
    }
    cout << sum << endl;
    return 0;
}

