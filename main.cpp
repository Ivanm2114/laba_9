#include <iostream>
#include <string>

#define lmax 200

using namespace std;

bool is_needed_symbol(char c) {
    string symbols = "E1234567890.+-";
    for (int i = 0; i < symbols.length(); i++) {
        if (c == symbols[i]) {
            return true;
        }
    }
    return false;
}


int find_substrings(string input[], string out[], int origins[], int len_input) {
    int len_output = 0, first = -1,i,j;
    bool flag;

    for ( i = 0; i < len_input; i++) {
        first=-1;
        for (j = 0; j < input[i].length(); j++) {
            flag = is_needed_symbol(input[i][j]);
            if (flag && first < 0) {
                first = j;
            } else if (!flag && first >= 0) {
                out[len_output].assign(input[i], first, j - first);
                origins[len_output++] = i;
                first = -1;
            }
        }
    }
    if(first>=0){
        out[len_output].assign(input[i-1], first, j - first);
        origins[len_output++] = i;
    }
    return len_output;


}

int find_shortest(string input[], int len_input) {
    int minlen = input[0].length(), mini = 0;
    for (int i = 0; i < len_input; i++) {
        if (input[i].length() < minlen) {
            minlen = input[i].length();
            mini = i;
        }
    }
    return mini;
}

bool insert_end(string &input) {
    bool change = false;
    int i = input.length() - 1;
    while (i >= 0 && input[i] != '*') {
        --i;
    }
    if (i >= 0) {
        input.insert(i, "END");
        change = true;
    }
    return change;

}


int main() {
    string input[lmax], good_strs[lmax],s;
    int index_of_shortest_str, len_input, len_good_strs=0, indexes_of_origins[lmax];
    bool added_END = false;
    do {
        cout << "Enter number of lines: ";
        cin >> len_input;
        if (cin.fail()) cin.clear();
        getline(cin,s);
    } while (len_input <= 0);
    cout << "Enter " << len_input << " strings\n";
    for(int i=0;i<len_input;++i){
        getline(cin,input[i]);
    }
    cout << "-----------------------------------\nYour strings:\n";
    for(int i=0;i<len_input;i++) cout<<input[i]+"\n";
    len_good_strs= find_substrings(input,good_strs,indexes_of_origins,len_input);
    if(len_good_strs){
        cout << "-----------------------------------\nSuitable strings:\n";
        for(int i=0;i<len_good_strs;i++) cout<<good_strs[i]+"\n";
        index_of_shortest_str= find_shortest(good_strs,len_good_strs);
        cout<<"-----------------------------------\nShortest substring:\n" << good_strs[index_of_shortest_str]+"\n";
        added_END=insert_end(input[indexes_of_origins[index_of_shortest_str]]);
        if(added_END){
            cout<<"-----------------------------------\nEdited original string:\n" <<input[indexes_of_origins[index_of_shortest_str]];
        }
        else{
            cout<<"-----------------------------------\nThere is no * in string";
        }
    }
    else{
        cout <<"-----------------------------------\nNo suitable strings, can`t continue";
    }


    return 0;
}
