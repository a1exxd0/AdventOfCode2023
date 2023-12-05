#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;

#define SIZE 10
int
threeDigitConversion(char *num){
    return (num[0] - 48) * 100 + (num[1] - 48) * 10 + (num[2] - 48);
}

bool
checkSurroundingsForSymbol(int x, int y, char array[][SIZE]){
    char notSymbols[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    size_t numsSize = sizeof(notSymbols) / sizeof(char);
    char *end = notSymbols + numsSize;
    int iteratorX = -1;
    int iteratorY = -1;
    while (iteratorX < 2){
        while (iteratorY < 2){
            try{
                if (find(notSymbols, end, (array)[x + iteratorX][y + iteratorY]) == end){
                    if(iteratorX != 0 && iteratorY != 0){
                        cout << "found not symbol" << endl;
                        return true;
                    }
                }
            }
            catch(...){
                //do nothing
            }
            iteratorY++;
        }
        iteratorX++;
    }
    return false;
}

int main(){
    /*12 red 13 green 14 blue max*/
    std::ifstream infile("Day3Test.txt");
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    int sum = 0;
    int lineNum = 0;
    char file[SIZE][SIZE];
    //line length 140
    for( std::string line; getline( infile, line ); ){
        for (int i = 0; i < SIZE; i++){
            file[lineNum][i] = line.at(i);
        }
        lineNum++;
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            int foundFlag = 0;
            char partNum[3] = {'0', '0', '0'};
            if (find(nums, end, (file)[i][j]) != end){
                foundFlag += checkSurroundingsForSymbol(i, j, file) ? 1 : 0;
                if(find(nums, end, (file)[i][j+1]) != end){
                    j++;
                    foundFlag += checkSurroundingsForSymbol(i, j, file) ? 1 : 0;
                    if(find(nums, end, (file)[i][j+1]) != end){
                        j++;
                        foundFlag += checkSurroundingsForSymbol(i, j, file) ? 1 : 0;
                        partNum[0] = (file)[i][j-2];
                        partNum[1] = (file)[i][j-1];
                        partNum[2] = (file)[i][j];
                    } else{
                        partNum[1] = (file)[i][j-1];
                        partNum[2] = (file)[i][j-0];
                    }
                }
                else{
                    partNum[2] = (file)[i][j];
                }
            }
            if (foundFlag != 0){
                sum += threeDigitConversion(partNum);
                cout << threeDigitConversion(partNum) << endl;
            }
        }
    }
    cout << sum << endl;
    return 0;
}