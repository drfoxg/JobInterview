
#include "Finder.h"

using namespace std;

/*

найти самые длинные подстроки из двух одинаковых символов
*длина строки может быть несколько гигабайт

*/

Finder::Finder(std::string long_str) {

	this->length = long_str.length();
	this->long_str = long_str;
}


Finder::~Finder() {
	
}


int Finder::get_length() {
	
	return length;

}

void Finder::get_uniq_words() {
    
    string word;
    int word_sum = 0;
    
    for (int i = 0; i < this->length - 1; i++) {

        word.assign(this->long_str, i, 2);
        
        if (word[0] != word[1]) {

            word_sum = static_cast<int> (word[0]) + static_cast<int> (word[1]);
            words.insert(pair<int, string>(word_sum, word));

        }

    }

    // debug
    /*    
    for (auto it = words.begin(); it != words.end(); it++) {

        cout << it->second << ' ' << it->first << endl;

    }
    */

}

list<string> Finder::get_max_string() {

    regex rx;
    string rx_s;
    int max_length = 0;
    list <string> result_ls;

    for (auto it = words.begin(); it != words.end(); it++) {

        // debug
        cout << it->second << ' ' << it->first << endl;
        
        // ([gf]+)
        rx_s = "[";
        rx_s += it->second[0];
        rx_s += it->second[1];
        rx_s += "]+";

        rx = rx_s;

        // debug
        // cout << "rx_s:" << rx_s << endl;

        sregex_iterator iter(this->long_str.begin(), this->long_str.end(), rx);
        sregex_iterator end;

        while (iter != end) {
            
            // debug
            // cout << "iter size: " << iter->size() << endl;

            for (unsigned i = 0; i < iter->size(); i++) {

                // debug
                // cout << "the " << i + 1 << "th match" << ": " << (*iter)[i] << endl;

                if ((*iter)[i].length() > max_length) {

                    result_ls.clear();

                    max_length = (*iter)[i].length();
                    result_ls.push_back((*iter)[i]);

                }
                else if ((*iter)[i].length() >= max_length) {

                    result_ls.push_back((*iter)[i]);

                }

            }
            
            iter++;
        
        }

    }
    
    
    return result_ls;

}

int Finder::find() {
    

    if (this->length < 2) {

        return -1;

    }    

    get_uniq_words();

    list <string> result_ls = get_max_string();
   
    list <string>::iterator it;
    for (it = result_ls.begin(); it != result_ls.end(); it++) {

        cout << "Результат:" << (*it) << endl;

    }
        
    return 0;

}
