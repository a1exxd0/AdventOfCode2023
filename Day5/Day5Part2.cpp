#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using std::cout;
using std::endl;
using std::cin;
using std::atoi;
using std::find;
using std::string;
using std::vector;

#define FILE "Day5"
typedef struct Seeds{
    long long int seeds[20];
} Seeds;

typedef struct Mappable{
    /*destination, source, range*/
    long long int container[3];
} Mappable;

long long int
twelveDigConv(char *num){
    return (num[0] - 48LL) * 100000000000LL + (num[1] - 48LL) * 10000000000LL +
            (num[2] - 48LL) * 1000000000LL + (num[3] - 48LL) * 100000000LL +
            (num[4] - 48LL) * 10000000LL + (num[5] - 48LL) * 1000000LL +
            (num[6] - 48LL) * 100000LL + (num[7] - 48LL) * 10000LL +
            (num[8] - 48LL) * 1000LL + (num[9] - 48LL) * 100LL +
            (num[10] - 48LL) * 10LL + (num[11] - 48LL);
}

Seeds
setSeeds(string line){
    Seeds result;
    int counter = 0;
    char num[12];

    for(int i = 0; i < 12; i++){ num[i] = '0'; }

    for (int i = 0; i < line.length(); i++){
        if (line.at(i) == ' '){
            result.seeds[counter++] = twelveDigConv(num);
            for(int j = 0; j < 12; j++){ num[j] = '0'; }
        } 
        else{
            for(int j = 0; j < 11; j++){ num[j] = num[j+1]; }
            num[11] = line.at(i);
        }
    }
    result.seeds[counter++] = twelveDigConv(num);
    return result;
}

Mappable
setMappable(string line){
    Mappable result;
    int counter = 0;
    char num[12];

    for(int i = 0; i < 12; i++){ num[i] = '0'; }

    for (int i = 0; i < line.length(); i++){
        if (line.at(i) == ' '){
            result.container[counter++] = twelveDigConv(num);
            for(int j = 0; j < 12; j++){ num[j] = '0'; }
        } 
        else{
            for(int j = 0; j < 11; j++){ num[j] = num[j+1]; }
            num[11] = line.at(i);
        }
    }
    result.container[counter++] = twelveDigConv(num);

    return result;
}

long long
traceSourceOutput(long long source, vector<Mappable> mappable){
    for(int i = 0; i < mappable.size(); i++){
        long long upperBound = mappable.at(i).container[1] + mappable.at(i).container[2] - 1;
        long long lowerBound = mappable.at(i).container[1];
        if(lowerBound <= source && source <= upperBound){
            return (mappable.at(i).container[0] - mappable.at(i).container[1]) + source;
        }
    }
    return source;
}

long long
minimum(Seeds seed){
    long long min = -1;
    for(int i = 0; i < ; i++){
        if(min == -1 || seed.seeds[i] < min){
            min = seed.seeds[i];
        }
    }
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
    
    /*seed -> soil -> fertiliser -> water -> light -> temperature -> humidity -> location*/
    vector<Mappable> seedToSoil;
    vector<Mappable> soilToFertiliser;
    vector<Mappable> fertiliserToWater;
    vector<Mappable> waterToLight;
    vector<Mappable> lightToTemperature;
    vector<Mappable> temperatureToHumidity;
    vector<Mappable> humidityToLocation;
    vector<Mappable> mappables[7] = {seedToSoil, soilToFertiliser,
                                        fertiliserToWater, waterToLight,
                                        lightToTemperature, temperatureToHumidity,
                                        humidityToLocation};

    int container_counter = -1;
    int counter = 0;
    for( std::string line; getline( infile, line ); ){
        if (line.find(":") != std::string::npos){
            container_counter++;
            counter = 0;
            cout << "found new" << endl;
        }
        else{
            if (line.size() == 0){
                //do nothing
            }
            else if(find(nums, end, line.at(0)) != end){
                mappables[container_counter].push_back(setMappable(line));
            }
        }
    }
    
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 7; j++){
            seed.seeds[i]  = traceSourceOutput(seed.seeds[i], mappables[j]);
        }
        printf("%lld\n", seed.seeds[i]);
    }
    
    
    return 0;
}

