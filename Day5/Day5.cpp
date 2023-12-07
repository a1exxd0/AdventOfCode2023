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

#define FILE "Day5"
typedef struct Seeds{
    long int seeds[20];
} Seeds;

long int
twelveDigConv(char *num){
    cout <<(num[0] - 48) * 100000000000 << endl;
    return (num[0] - 48) * 100000000000 + (num[1] - 48) * 10000000000 +
            (num[2] - 48) * 1000000000 + (num[3] - 48) * 100000000 +
            (num[4] - 48) * 10000000 + (num[5] - 48) * 1000000 +
            (num[6] - 48) * 100000 + (num[7] - 48) * 10000 +
            (num[8] - 48) * 1000 + (num[9] - 48) * 100 +
            (num[10] - 48) * 10 + (num[11] - 48);
}

Seeds
setSeeds(string line){
    Seeds result;
    int counter = 0;
    char num[12];
    for(int i = 0; i < 12; i++){
        num[i] = 0;
    }
    for (int i = 0; i < line.length(); i++){
        if (line.at(i) == ' '){
            result.seeds[counter] = twelveDigConv(num);
            for(int j = 0; j < 12; j++){
                num[j] = '0';
            }
        } 
        else{
            for(int j = 0; j < 11; j++){
                num[j] = num[j+1];
            }
            num[11] = line.at(i);
            cout <<"placed " <<num[11] << endl;
        }
    }
    return result;
}

int 
main(){
    string filename = FILE;
    filename += ".txt";
    std::ifstream infile(filename);
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    long int seeds[20];
    for(int i = 0; i < 20; i++){
        seeds[i] = 0;
    }
    int seedCount = 0;
    std::string line; getline( infile, line );
    int indexColon = line.find(':') + 1;
    line.replace(line.find("seeds: "), 7, "");
    Seeds seed = setSeeds(line);
    for( std::string line; getline( infile, line ); ){

    }
}