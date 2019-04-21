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
    int stop_size;
    string sentence;
    vector<string> input;
    vector<string> stop_words;
    char option;


public:
    KWICMachine(){

        getSentences();
        sentenceRemoval();

        defineStops();
        removeStops();

        cleanSpaces();

        rotater();

        sort(input.begin(), input.end());

        orderHandler();



    }

    void getSentences(){
     cout << "Ingresa la cantidad de oraciones a procesar: " << endl;
        cin >> input_size;

        cout << "Ingresa las " << input_size << " oraciones a procesar: " << endl;
        for(int i=0; i<=input_size; i++){
            getline(cin, sentence);
            input.push_back(prepareString(sentence));
        }
    }

    void rotater(){
        for(int i=1; i<=input_size; i++){
            createRotations(input[i]);
        }
    }


    void printIncreasing(){
        for(vector<string>::iterator it=input.begin(); it!=input.end(); ++it){
            cout << *it << endl;
        }
    }

    void printDecreasing(){
        for(vector<string>::iterator it=input.end()-1; it!=input.begin(); --it){
            cout << *it << endl;
        }
    }

    void orderHandler(){
        cout << endl << "Si desea que el ordenamiento sea INCREMENTAL, ingrese 'I' " << endl;
        cout << "Si desea que el ordenamiento sea DECREMENTAL, ingrese 'D' " << endl;
        while(option!='I' && option!='D'){
            cout << "Elija un tipo de ordenamiento (I/D): " << endl;
            cin >> option;

            if(option=='I'){
                cout << endl << "Elegiste ordenamiento incremental" << endl;

                sentenceRemoval();
                printIncreasing();

            }
            if(option=='D'){
                cout << endl << "Elegiste ordenamiento decremental" << endl;

                sentenceRemoval();
                printDecreasing();
            }
        }
    }

    void defineStops(){
        cout << "Ingresa la cantidad de 'stop words' deseadas: " << endl;
        cin >> stop_size;

        if(stop_size > 0){
            cout << "Ingresa las " << stop_size << " stop words que deseas:" << endl;
            for(int i=0; i<=stop_size; i++){
                getline(cin, sentence);
                stop_words.push_back(prepareString(sentence));
            }
        }
    }

    void sentenceRemoval(){
        int deleter;
        cout << endl << "Si deseas quitar una oracion de la lista, ingresa su numero. " << endl;
        cout << "Si no deseas quitar nada, o ya acabaste de quitarlas, ingresa 0: " << endl;
        displayList();
        cin >> deleter;
        while(deleter!=0){
            if(deleter>input.size() || deleter<0){
                cout << endl << "Seleccion fuera de rango, solo hay " << input.size() << " oraciones." << endl;
            }
            else{
                cout << endl <<"Eliminando oracion #" << deleter << endl;
                delSentence(deleter);
            }
            displayList();
            cin >> deleter;
        }


    }

    void delSentence(int choice){
        vector<string>::iterator it;
        it = input.begin()+choice;
        input.erase(it);
        input_size--;
    }

    void displayList(){
        cout << endl << "-------------------------------------------" << endl;
        for(int i=1; i<input.size(); i++){
            cout << "#" << i << "   " << input[i] << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void removeStops(){
        if(stop_size>0){
            int length;
            string space = " ";
            for(int i=1; i<=stop_size; i++){
                length = stop_words[i].length()+1;
                string stop = stop_words[i].append(space);
                for(int j=1; j<=input_size; j++){
                    string searched = input[j].append(space);
                    size_t found = searched.find(stop);
                    while(found != string::npos){
                        input[j].erase(found, length);
                        found = searched.find(stop_words[i].append(space));
                    }
                }
            }
        }
    }

    string clearSpaces(string s){
        size_t spaces = s.find("  ");
        while(spaces != string::npos){
            s.erase(spaces, 2);
            spaces = s.find("  ");
        }
        if(s[0]==' '){
            s.erase(0, 1);
        }
        if(s[s.length()-1] == ' '){
            s.erase(s.length()-1, 1);
        }
        return s;
    }

    void cleanSpaces(){
        for(int i=1; i<=input_size; i++){
            input[i] = clearSpaces(input[i]);
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
