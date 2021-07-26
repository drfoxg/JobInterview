#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <list>
#include <map>

class Finder {

public:

	Finder(std::string long_str);
	~Finder();

	int get_length();
	int find();

private:
	int length;
	std::string long_str;
    std::map<int, std::string> words;

    void get_uniq_words();
    std::list<std::string> get_max_string();
};