#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;

#define SIZE 197
#define WINNING 10
#define DRAWN 25
#define CARDDEF 9 //to and including colon
#define LINELEN CARDDEF + (WINNING * 3) + 2 + (DRAWN * 3) //2 digit nums
#define FILE "Day4"

int
threeDigitConversion(char *num){
    return (num[0] - 48) * 100 + (num[1] - 48) * 10 + (num[2] - 48);
}

int
twoDigitConversion(char *num){
    return (num[0]-48)*10 + (num[1]-48);
}

int 
main(){
    string filename = FILE;
    filename += ".txt";
    std::ifstream infile(filename);
    char nums[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    int sum = 0;

    /*Set up array */
    int lineNum = 0;
    char file[SIZE][LINELEN];
    for( std::string line; getline( infile, line ); ){
        for (int i = 0; i < LINELEN; i++){
            file[lineNum][i] = line.at(i);
        }
        lineNum++;
    }

    for(int line = 0; line < SIZE; line++){
        char winners[WINNING*2];
        char draws[DRAWN*2];
        int arbCount = 0;
        for(int i = CARDDEF+1; i < (CARDDEF-1) + (WINNING*3) + 1; i++){
            if (file[line][i] == ' '){
                winners[i-CARDDEF-1] = '0';
            } else{
                winners[i-CARDDEF-1] = file[line][i];
            }
            arbCount++;
            if (arbCount == 2){
                i++;
                arbCount == 0;
            }
        }
        arbCount = 0;
        for(int i = (CARDDEF-1) + (WINNING * 3) + 4; i < (CARDDEF-1) + (WINNING * 3) + 2 + (DRAWN*3) + 1; i++){
            if (file[line][i] == ' '){
                draws[i-((CARDDEF-1) + (WINNING * 3) + 4)] = '0';
            } else{
                draws[i-((CARDDEF-1) + (WINNING * 3) + 4)] = file[line][i];
            }
            arbCount++;
            if (arbCount == 2){
                i++;
                arbCount == 0;
            }
        }
        for(int i = 0; i < WINNERS; i++)
    }
}