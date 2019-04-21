#ifndef KWICMachine_h
#define KWICMachine_h
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <algorithm>

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

        if(input_size>0){

            sentenceRemoval();

            defineStops();
            if(stop_size>0){
                removeStops();
                cleanSpaces();
            }

            rotater();

            sort(input.begin(), input.end());

            orderHandler();
        }

    }

    void getSentences(){
        cout << "tamaño del vector es " << input.size() << endl;
     cout << "Ingresa la cantidad de oraciones a procesar: " << endl;
        cin >> input_size;

        if(input_size>0){
        cout << "Ingresa las " << input_size << " oraciones a procesar: " << endl;
        for(int i=0; i<=input_size; i++){
            getline(cin, sentence);
            input.push_back(prepareString(sentence));
        }
        recenter();
        cout << "tamaño del vector es " << input.size() << endl;
        }
    }

    void rotater(){
        for(int i=0; i<input_size; i++){
                cout << "rotating " << input[i] << endl;
            createRotations(input[i]);
        }
    }

    void printResult(){
         cout << "El resultado final es: " << endl;
         cout << "-------------------------------------------" << endl;
        for(vector<string>::iterator it=input.begin(); it!=input.end(); ++it){
            cout << *it << endl;
        }
        cout << "-------------------------------------------" << endl;
    }


    void orderHandler(){
        cout << endl << "Si desea que el ordenamiento sea INCREMENTAL, ingrese 'I' " << endl;
        cout << "Si desea que el ordenamiento sea DECREMENTAL, ingrese 'D' " << endl << endl;

        cout << "Elija un tipo de ordenamiento (I/D): " << endl;
        cin >> option;


            if(option=='I'){
                cout << endl << "Elegiste ordenamiento incremental" << endl;

                sentenceRemoval();

            }
            if(option=='D'){
                cout << endl << "Elegiste ordenamiento decremental" << endl;

                reverse(input.begin(), input.end());
                sentenceRemoval();
            }
            else{
                cout << "Eleccion no reconocida, ordenando de manera incremental..." << endl;
                sentenceRemoval();
            }

         printResult();
    }

    void defineStops(){
        cout << "Ingresa la cantidad de 'stop words' a borrar de las oraciones: " << endl;
        cin >> stop_size;

        if(stop_size>0){
            cout << "Ingresa la(s) " << stop_size << " stop word(s) que deseas:" << endl;
            for(int i=0; i<=stop_size; i++){
                getline(cin, sentence);
                stop_words.push_back(prepareString(cleanStop(sentence)));
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
        it = input.begin()+choice-1;
        input.erase(it);
        input_size--;
    }

    void displayList(){
        int i=1;
        cout << endl << "-------------------------------------------" << endl;
        for( vector<string>::iterator it=input.begin(); it!=input.end(); it++){
            cout << "#" << i << "   " << *it << endl;
            i++;
        }
        cout << "-------------------------------------------" << endl;
    }

    void recenter(){
        for( vector<string>::iterator it=input.begin(); it!=input.end(); ++it){
            string check = *it;
            if(check.empty()){
                input.erase(it);
            }
        }
    }

       void removeStops(){
        if(stop_size>0){
            string lookup;
            string e;
            for(int i=1; i<=stop_size; i++){
                lookup=stop_words[i];
                for(int j=0; j<input_size; j++){
                    e=input[j];
                    input[j]=eliminate(lookup, e);
                }
            }
        }
    }

    string eliminate(string to, string from){
        string look = " " + to + " ";
        string result = " " + from + " ";
        size_t found = result.find(look);
        while(found != string::npos){
            result.erase(found, look.length()-1);
            found = result.find(look);
        }
        return result;

    }

    string cleanStop(string stop){
        string clean;
        for(int i=0; i<stop.size(); i++){
            if(stop[i]!=' '){
                clean+=stop[i];
            }
        }
        return clean;
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
        for(int i=0; i<input.size(); i++){
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
