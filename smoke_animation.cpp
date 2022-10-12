#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stdio.h>


using namespace std::literals;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void gotoxy( int column, int line ){
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}

void setPos(int col, int row){
	gotoxy(col, row); // windows
	//printf("\033[%d;%dH", row, col); // linux/terminal
	//std::cout << "\033[F"; // for single line up, linux/terminal

}

std::string global_sequence1 = "!@#$%^&*()-_+=`~,.<>/';]}[{\\|";
std::string global_sequence2 = "0123456789";

std::string sequence_selection(std::string x){
	std::string y = x;
	random_shuffle(y.begin(), y.end());
	std::string first_five = y.substr(0, 5);
	return first_five;
}

void list_generation(std::vector<std::string>& list1, std::vector<std::string>& list2){
    for (int i=0; i<70; i++){
        list1.push_back(sequence_selection(global_sequence1));
	    list2.push_back(sequence_selection(global_sequence2));
    }
}

void Animation_section(){
	std::vector<std::string> s_list1; // random 5 chars from global_sequence1
    std::vector<std::string> s_list2; // random 5 chars from global_sequence2
    list_generation(s_list1, s_list2);

	
    
	auto duration = 10000s;
	auto duration_step = 50ms;
	for (auto i = 0; i < (duration/duration_step); ++i) {
		
		int col_ref0 = 53;
        for (int k = 11; k <= 33; k++){ // per line
			setPos(col_ref0-floor(k*1.40), k); // higher floor coef moves blast cone left
			int a = floor(0.40*pow(2.72, 0.1426*k)); // min line length, line eq = 1.1892*k - 13.614, exp eq = 0.3762*e^0.1426*k
			int b = a + floor(k/3);
			int line_len = a + (rand() % static_cast<int>(b - a + 1));
			// add a scrambler for list1 and list2 before iterating through each line to avoid repeititon
			random_shuffle(s_list1.begin(), s_list1.end());
			random_shuffle(s_list2.begin(), s_list2.end());

			for (int j = 0; j <= line_len; j++){ // iterates through each col in the line length
				if ( 0.30 > ((float) rand() / (RAND_MAX)) ){ // selects whether or not the coord displays something
					if ( 0.75 > ((float) rand() / (RAND_MAX)) ){
						std::cout << s_list1[j][i%s_list1[j].size()]; // print list1
					}else{
						std::cout << s_list2[j][i%s_list2[j].size()]; // print list2
					}
				}else{
					std::cout << " ";
				}
				if (j == line_len){
					std::cout << std::flush;
				}
			}
		}
		
		

		/*
		setPos(20,20);
  		std::cout << s_list1[0][i%s_list1[0].size()] << s_list1[1][i%s_list1[1].size()] <<
         s_list1[2][i%s_list1[2].size()] << "\n" << std::flush;

		setPos(20,21);

        std::cout << s_list2[0][i%s_list2[0].size()] << s_list2[1][i%s_list2[1].size()] <<
         s_list2[2][i%s_list2[2].size()] << std::flush;

        setPos(20,20);
        */

  		std::this_thread::sleep_for(duration_step);
        // add if statement for breaking animation to next screen for linux
		if (GetAsyncKeyState(VK_RETURN)){
        	break;
        }
	}
}


void welcome(){
	std::cout << " " << std::endl;
	std::fstream MenuArt;
	MenuArt.open("SovIMG3", std::ios::in);
	if (MenuArt.is_open()){
		std::string line;
		int current_line = 0;
		while(!MenuArt.eof()){				//while not end of line
			current_line++; 				//incriment line
			getline(MenuArt, line); 		//get line from file
			std::cout << line << std::flush << std::endl;
			if(current_line >= 10 && current_line < 17){
				std::chrono::milliseconds dura(20);
				std::this_thread::sleep_for(dura); 	//delay thread
				}else if(current_line >=17){
					std::chrono::milliseconds dura(70);
					std::this_thread::sleep_for(dura); 	//delay thread
			}
		}
				MenuArt.close();
        
	}
    
}

void loadingSymbol(){
	static const std::string sequence_L = "|/-\\";
	auto duration = 5s;
	auto duration_step = 250ms;
	for (auto i = 0; i < (duration/duration_step); ++i) {
  		std::cout << "\r" << sequence_L[i%sequence_L.size()] << std::flush;
  		std::this_thread::sleep_for(duration_step);
	}
}

int main(){
	COORD bufferSize = {170, 200};
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	SetConsoleActiveScreenBuffer(hConsole);
	
	SMALL_RECT windowSize = {0, 0, 170, 40};
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    welcome();
	Animation_section();
	std::cin.get();	//press key to continue
	std::system("cls");

	// user interface prompt

	std::string input;

    while (getline(std::cin, input) && input != "quit" && input != "\n") // "\n" exception makes sure the unrecognized command message isnt displayed after getting past the title screen
    {
        if (input == "Hello")
            std::cout << "Hello world!\n";
        else if (input == "balls")
        {
            std::cout << "Special message" << "\n";
        }
        else
            std::cout << "Unrecognized command: " << input << "\n";
    }


}