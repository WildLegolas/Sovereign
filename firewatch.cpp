#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <windows.h>
#include <algorithm>
#include <vector>

std::string global_sequence1 = "!@#$%^&*()-_+=`~,.<>/';]}[{\\|";
std::string global_sequence2 = "qwertyuiopasdfghjklzxcvbnm";

std::string sequence_selection(std::string x){
	std::string y = x;
	random_shuffle(y.begin(), y.end());
	std::string first_five = y.substr(0, 5);
	return first_five;
}

void list_generation(std::vector<std::string>& list1, std::vector<std::string>& list2){
    for (int i=0; i<30; i++){
        list1.push_back(sequence_selection(global_sequence1));
	    list2.push_back(sequence_selection(global_sequence2));
    }
}

int main(){
    std::vector<std::string> s_list1;
    std::vector<std::string> s_list2;
    list_generation(s_list1, s_list2);
    std::cout << s_list1[0];
}