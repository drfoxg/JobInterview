#include <iostream>
#include <string>
#include <regex>

#include <Windows.h>

#include "Finder.h"

using namespace std;

int main() {

	string input_str;
    
    //SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
        
    cout << "Введити строку:" << endl;
	cin >> input_str;

	Finder fd(input_str);
    
    fd.find();

}
