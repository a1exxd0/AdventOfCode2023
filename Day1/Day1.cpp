#include <fstream>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;

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
        indexes[0] = 1000;
        indexes[1] = 0;
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
                cout << "indexes: "<< indexes[0] << " " << indexes[1] << endl;
                cout << "found "<< numsString[j] << " at " << line.find(numsString[j]) << endl;
                if (line.find(numsString[j]) < indexes[0]){
                    if (num[1] == '-'&& indexes[0] != 1000){
                        num[1] = num[0];
                        indexes[1] = indexes[0];
                    }
                    num[0] = j + 48;
                    indexes[0] = line.find(numsString[j]);
                }
                else if (line.find(numsString[j]) > indexes[1]){
                    num[1] = j + 48;
                    indexes[1] = line.find(numsString[j]);
                }
            }
        }
        for(int j = 0; j < 10; j++){
            if (line.find(numsString[j]) != std::string::npos){
                cout << "indexes: "<< indexes[0] << " " << indexes[1] << endl;
                cout << "found "<< numsString[j] << " at " << line.rfind(numsString[j]) << endl;
                if (line.rfind(numsString[j]) < indexes[0]){
                    if (num[1] == '-'&& indexes[0] != 1000){
                        num[1] = num[0];
                        indexes[1] = indexes[0];
                    }
                    num[0] = j + 48;
                    indexes[0] = line.rfind(numsString[j]);
                }
                else if (line.rfind(numsString[j]) > indexes[1]){
                    num[1] = j + 48;
                    indexes[1] = line.rfind(numsString[j]);
                }
            }
        }
        
        cout << num[0] << " " << num[1] << endl;
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