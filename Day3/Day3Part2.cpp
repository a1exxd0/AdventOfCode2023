#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;

#define SIZE 140
#define FILE "Day3"
int
threeDigitConversion(char *num){
    return (num[0] - 48) * 100 + (num[1] - 48) * 10 + (num[2] - 48);
}

int
returnAdjacentNum(int x, int y, char array[][SIZE]){
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;
    int iteratorY=0;

    char num[3] = {'0','0','0'};
    int count = 0;
    while (count < 3 && !(y+iteratorY < 0)){
        if(find(nums, end, (array)[x][y+iteratorY]) != end){
            num[2-count] = (array)[x][y+iteratorY];
            count++;
            iteratorY--;
        }
        else{
            break;
        }
    }
    iteratorY = 1;
    while (count < 3 && !(y+iteratorY >= SIZE)){
        if(find(nums, end, (array)[x][y+iteratorY]) != end){
            num[0] = num[1];
            num[1] = num[2];
            num[2] = (array)[x][y+iteratorY];
            count++;
            iteratorY++;
        }
        else{
            break;
        }
    }
    return (threeDigitConversion(num));
}

int
findProdGears(int x, int y, char array[][SIZE]){
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;
    int prodGears = 1;
    int countGears = 0;
    int iteratorX = -1;
    int iteratorY;
    while (iteratorX < 2){
        iteratorY = -1;
        while (iteratorY < 2){
            if (!(x+iteratorX < 0 || y+iteratorY < 0 || x+iteratorX >= SIZE || y+iteratorY >= SIZE)){
                if (find(nums, end, (array)[x + iteratorX][y + iteratorY]) != end){
                    if(iteratorY == 0){
                        if (!(iteratorX == 0 && iteratorY == 0)){
                            cout << returnAdjacentNum(x+iteratorX, y+iteratorY, array) << endl;
                            prodGears = prodGears * returnAdjacentNum(x+iteratorX, y+iteratorY, array);
                            countGears++;
                            break;
                        }
                    }
                    else{
                        cout << returnAdjacentNum(x+iteratorX, y+iteratorY, array) << endl;
                        prodGears = prodGears * returnAdjacentNum(x+iteratorX, y+iteratorY, array);
                        countGears++;
                        if (find(nums, end, (array)[x + iteratorX][y + iteratorY + 1]) != end){
                            break;
                        }
                        iteratorY++;
                    }
                }
            }
            iteratorY++;
        }
        iteratorX++;
    }
    if (countGears != 2){
        prodGears = 0;
    }
    cout << "gear prod: " << prodGears << endl;
    return prodGears;
}
int 
main(){
    string filename = FILE;
    filename += ".txt";
    std::ifstream infile(filename);
    char notSymbols[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    size_t numsSize = sizeof(notSymbols) / sizeof(char);
    char *end = notSymbols + numsSize;

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
            if (find(notSymbols, end, (file)[i][j]) == end){
                    sum += findProdGears(i, j, file);
            }
        }
    }
    cout << sum << endl;
    return 0;
}