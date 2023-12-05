#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;



int main(){
    std::ifstream infile("Day1.txt");
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    std::string numsString[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    char num[2];
    int indexes[2];
    int sum = 0;
    for( std::string line; getline( infile, line ); )
    {
        num[0] = '-';
        num[1] = '-';
        for (int i = 0; i < line.size(); i++){
            if (find(nums, end, line.at(i)) != end){
                if(num[0] == '-'){
                    num[0] = line.at(i);
                    indexes[0] = i;
                }
                else{
                    num[1] = line.at(i);
                    indexes[1] = i;
                }
            }
        }
        for(int j = 0; j < 10; j++){
            if (line.find(numsString[j]) != std::string::npos){
                if (num[0] == '-'){
                    num[0] = j + 48;
                    indexes[0] = line.find(numsString[j]);
                }
                if (num[1] == '-'){
                    num[1] = j + 48;
                    indexes[1] = line.find(numsString[j]);
                }
                else{
                    if (line.find(numsString[j]) <= indexes[0]){
                        num[0] = j + 48;
                        indexes[0] = line.find(numsString[j]);
                    }
                    else if (line.find(numsString[j]) >= indexes[1]){
                        num[1] = j + 48;
                        indexes[1] = line.find(numsString[j]);
                    }
                }
            }
        }

        if (num[1] != '-'){
            sum = sum + ((num[0]-48) * 10) + (num[1]-48);
        }
        else{
            sum = sum + ((num[0]-48) * 10) + (num[0]-48);
        }
    }
    cout << sum;
    return 0;
}