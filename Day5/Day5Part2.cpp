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
#define UPPERBOUND mappable.at(i).container[1] + mappable.at(i).container[2] - 1 //leq
#define LOWERBOUND mappable.at(i).container[1] //leq
typedef struct SeedRange{
    vector<long long int> seedsVector;
} SeedRange;

typedef struct Seeds{
    vector<long long int> seedsVector;
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

SeedRange
setSeedRange(string line){
    SeedRange result;
    int counter = 0;
    char num[12];

    for(int i = 0; i < 12; i++){ num[i] = '0'; }

    for (int i = 0; i < line.length(); i++){
        if (line.at(i) == ' '){
            result.seedsVector.push_back(twelveDigConv(num));
            for(int j = 0; j < 12; j++){ num[j] = '0'; }
        } 
        else{
            for(int j = 0; j < 11; j++){ num[j] = num[j+1]; }
            num[11] = line.at(i);
        }
    }
    result.seedsVector.push_back(twelveDigConv(num));
    return result;
}

Seeds
setSeeds(SeedRange seedRange){
    Seeds result;

    for(int i = 0; i < seedRange.seedsVector.size(); i=i+2){
        cout << "new pair" << endl;
        for (int j = 0; j < seedRange.seedsVector.at(i+1); j++){
            result.seedsVector.push_back(seedRange.seedsVector.at(i) + j);
        }
    }
    
    return result;
}

SeedRange
traceSourceRangeOutput(SeedRange source, vector<Mappable> mappable){
    SeedRange result;
    for(int i = 0; i < source.seedsVector.size(); i=i+2){
        long long startStep = source.seedsVector.at(i);
        while(startStep <= source.seedsVector.at(i+1)+source.seedsVector.at(i)-1){
            bool startStepFound = false;
            long long leastSeed = -1;
            for(int j = 0; j < mappable.size(); j++){
                if(startStep <= UPPERBOUND && startStep >= LOWERBOUND){
                    result.seedsVector.push_back(startStep);
                    result.seedsVector.push_back(UPPERBOUND - startStep + 1);
                    startStep = UPPERBOUND + 1;
                    startStepFound = true;
                    break;
                }
            }
            
            bool smallestGreaterThan = false;
            for (int j = 0; j < mappable.size(); j++){
                if (mappable.at(j).container[1] > startStep){
                    if (mappable.at(j).container[1] < leastSeed || leastSeed == -1){
                        leastSeed = mappable.at(j).container[1];
                        break;
                    }
                }
            }

            if (!startStepFound){
                result.seedsVector.push_back(startStep);
                result.seedsVector.push_back(leastSeed - startStep);
                startStep = leastSeed;
            }

            if(leastSeed == -1){
                result.seedsVector.push_back(startStep);
                result.seedsVector.push_back(source.seedsVector.at(i+1));
                startStep = startStep + source.seedsVector.at(i+1);
            }
        }
        printf("Range: %lld - %lld\n", result.seedsVector.at(i), result.seedsVector.at(i+1));
    }
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
minimum(SeedRange seed){
    long long min = -1;
    for(long long int i = 0; i < seed.seedsVector.size(); i=i+2){
        if(min == -1 || seed.seedsVector.at(i) < min){
            min = seed.seedsVector.at(i);
        }
    }
    return min;
}

int 
main(){
    string filename = FILE;
    filename += ".txt";
    std::ifstream infile(filename);
    char nums[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    size_t numsSize = sizeof(nums) / sizeof(char);
    char *end = nums + numsSize;

    std::string line; getline( infile, line );
    int indexColon = line.find(':') + 1;
    line.replace(line.find("seeds: "), 7, "");
    SeedRange seedRange = setSeedRange(line);
    
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

    for (int j = 0; j < 7; j++){
        seedRange = traceSourceRangeOutput(seedRange, mappables[j]);
    }
    cout << "seeds traced" << endl;
    long long min = minimum(seedRange);
    printf("Minimum: %lld\n", min);
    
    return 0;
}

