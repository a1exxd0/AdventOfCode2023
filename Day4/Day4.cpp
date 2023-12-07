#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;

#define SIZE 197 //def 197, 6
#define WINNING 10 //def 10, 5
#define DRAWN 25 //def 25, 8
#define CARDDEF 9 //to and including colon def 9, 7
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
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
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

    int winningCards[SIZE];
    int sumCards[SIZE];

    for(int line = 0; line < SIZE; line++){
        char winners[WINNING*2];
        char draws[DRAWN*2];
        int lineSum = 0;
        for(int i = 0; i < WINNING*2; i=i+2){
            if (file[line][CARDDEF-1 + ((i/2)+1)*3-1] == ' '){
                winners[i] = '0';
            } else{
                winners[i] = file[line][CARDDEF-1 + ((i/2)+1)*3 - 1];
            }
            winners[i+1] = file[line][CARDDEF-1 + ((i/2)+1)*3];
        }
        for(int i = 0; i < DRAWN*2; i=i+2){
            if (file[line][CARDDEF-1 + (WINNING*3) + 2 + ((i/2)+1)*3 - 1] == ' '){
                draws[i] = '0';
            } else{
                draws[i] = file[line][CARDDEF-1 + (WINNING*3) + 2 + ((i/2)+1)*3 - 1];
            }
            draws[i+1] = file[line][CARDDEF-1 + (WINNING*3) + 2 + ((i/2)+1)*3];
        }
        
        for(int i = 0; i < DRAWN * 2; i=i+2){
            for(int j = 0; j < WINNING * 2; j = j+2){
                if (draws[i] == winners[j] && draws[i+1] == winners[j+1]){
                    lineSum++;
                    break;
                }
            }
        }
        if (lineSum > 0){
            winningCards[line] = lineSum;
            sumCards[line] = pow(2,(lineSum-1));
        } else{
            winningCards[line] = 0;
            sumCards[line] = 0;
        }
    }
    // cards n past winning card with n matches are copies of card n
    int cardCopies[SIZE];
    for (int i = 0; i < SIZE; i++){
        cardCopies[i] = 1;
    }
    for(int i = 0; i < SIZE; i++){
        if (winningCards[i] > 0){
            for (int j = 1; j < winningCards[i] + 1; j++){
                if (i+j < SIZE){
                    cardCopies[i+j] = cardCopies[i+j] + cardCopies[i];
                }
            }
        }
        cout << "card: "<< i <<", copies: " <<cardCopies[i] << ", matches: "<< winningCards[i] << ", sum: "<< sumCards[i] << ", ps: " << sumCards[i]*cardCopies[i] << endl;
    }
    for(int i = 0; i < SIZE; i++){
        sum = sum + (sumCards[i] * cardCopies[i]);
    }
    cout << sum << endl;
}