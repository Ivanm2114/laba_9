#include <iostream>

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
    int len_output = 0, first = -1;
    bool flag;

    for (int i = 0; i < len_input; i++) {
        for (int j = 0; j < input[i].length(); j++) {
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

bool insert_end(string& input) {
    bool change = false;
    int i = input.length() - 1;
    while (i > 0 && input[i] != '*') {
        --i;
    }
    if (i >= 0) {
        input.insert(i, "END");
        change=true;
    }
    return change;

}

int main() {
    string abc="asda434*sds";
    insert_end(abc);
    cout << abc;
    return 0;
}
