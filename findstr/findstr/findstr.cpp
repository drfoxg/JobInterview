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

    cout << "Compiler version: " << _MSC_VER << endl;
    
    // /Zc:__cplusplus https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
    cout << "C++ version: " << __cplusplus << endl;
        
    cout << "Введити строку:" << endl;
	cin >> input_str;

	Finder fd(input_str);
    
    fd.find();

}
