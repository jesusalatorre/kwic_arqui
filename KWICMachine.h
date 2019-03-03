#ifndef KWICMachine_h
#define KWICMachine_h
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class KWICMachine{
private:
    int input_size;
    string sentence;
    vector<string> input;


public:
    KWICMachine(){
        cout << "Ingresa la cantidad de oraciones a procesar: " << endl;
        cin >> input_size;

        cout << "Ingresa las " << input_size << " oraciones a procesar: " << endl;
        for(int i=0; i<=input_size; i++){
            getline(cin, sentence);
            input.push_back(prepareString(sentence));
        }
        for(int i=1; i<=input_size; i++){
            createRotations(input[i]);
        }

        sort(input.begin(), input.end());

        for(int i=1; i<input.size(); i++){
            cout << input[i] << endl;
        }
    }

    int wordCount(string s){
        bool inSpaces = true;
        int counter = 0;

        for(int i=0; i<=s.size(); i++)
        {
            if (s[i]==' ')
            {
                inSpaces = true;
            }
            else if (inSpaces)
            {
                counter++;
                inSpaces = false;
            }
        }
        return counter;
    }

    string prepareString(string s){
        string prepared_string;

       for(int i=0; i<s.length(); i++){
            if(isalnum(s[i])||s[i]==' '){
                prepared_string+=tolower(s[i]);
            }
        }
        return prepared_string;
    }

    void createRotations(string s){
        string first_word;
        string rest;
        string new_rotation=s+" ";
        int count = wordCount(s);

        for(int words=1; words<count; words++){
            first_word = new_rotation.substr(0, new_rotation.find(" ")+1);

            rest = new_rotation.substr(new_rotation.find(" ")+1);

            new_rotation = (rest + first_word);
            input.push_back(new_rotation);
        }
    }
};

#endif
