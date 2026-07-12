#include<iostream>
#include<bits/stdc++.h>

using namespace std;

unordered_map<string, int> wordToDigit = {{"ZERO", 0}, {"ONE", 1}, {"TWO", 2}, {"THREE", 3}, {"FOUR", 4}, {"FIVE", 5}, {"SIX", 6}, {"SEVEN", 7}, {"EIGHT", 8}, {"NINE", 9}};

int stringToNum(string s) {
    try {
        stringstream ss(s);
        string word;
        vector<string> digits;
        
        while(ss >> word) {
            digits.push_back(word);
        }
        if(digits.size() > 3) throw 400;
        
        int num = 0;
        for(auto i : digits) {
            num += wordToDigit[i];
            num *= 10;
        }
        return num / 10;
    } catch(int error) {
        if(error == 400) throw "Not Possible!";
    }
    throw "Failed!";
}

int main() {
    try{
        string n = "";
        cout << "Enter numbers in words (space separated): ";
        getline(cin, n);
        for(int i = 0; i < n.length(); i++) {
            n[i] = toupper(n[i]);
        }
        cout << stringToNum(n);
    } catch(string error) {
        cout << error;
    }
    return 0;
}
