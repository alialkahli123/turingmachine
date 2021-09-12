
//
// Created by Ali Alkahli on 10/26/20.
//
#include <iostream>
#include <set>
#include "TuringMachine.h"
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;

TuringMachine::TuringMachine() {

    tape = {-1,0,1};
    marked = {};
    currentSquare = 0;


}
TuringMachine::TuringMachine(std::string tapeFile, std::string stateFile) {
    tape = {-2,-1,0,1 ,2 ,3};
    convertTapeFile(tapeFile);
    convertStateFile(stateFile);
    totalStates = totalStateCount();

}


void TuringMachine::moveLeft() {

    auto leftSide = tape.begin();
    if (currentSquare - 1 < *tape.begin() )
        tape.insert(leftSide, -(++left));
    currentSquare = currentSquare - 1;



}

void TuringMachine::moveRight() {
    auto rightSide = tape.find(0);
    tape.insert(tape.end(), ++right);
    currentSquare = currentSquare + 1;

}


void TuringMachine::makeMark() { marked.insert(currentSquare); }

void TuringMachine::removeMark() { marked.erase(currentSquare); }

bool TuringMachine::readSquare() const {
    for (auto it = marked.begin(); it != marked.end(); it++) {
        if (currentSquare == *it)
            return true;

    }
    return false;


}

std::string TuringMachine::tapeToString() const {
    std::string tempString = "[";

    for (auto itM = marked.begin(); itM!=marked.end() ; itM++) {
            tempString =  tempString + std::to_string(*itM) + ", ";



    }
    if (tempString.length() > 2)
        tempString = tempString.substr(0, tempString.length()-2);
    tempString = tempString + "]\nCurrent square:" + std::to_string(currentSquare);


    return tempString;
}





void TuringMachine::print(){
    std::string output = "[";

    for (int i: tape) {
        output= output + std::to_string(i) + ", ";

    }

    if (output.length() > 2)
        output = output.substr(0, output.length()-2);


    cout << output + "]"<<endl;

}

void TuringMachine::convertTapeFile(std::string tapeFile) {

    std::ifstream inputFile;
    inputFile.open(tapeFile);
    std::string currentSquareString;

    if (inputFile) {


        while (!inputFile.eof()) {


            std::string currentLine;


            getline (inputFile, currentLine);
            int length = currentLine.length();
            for (int i = 0; i < length; ++i) {
                if (currentLine.find(":") == i) {
                    currentSquareString = currentLine.substr(0, i);
                    currentLine = currentLine.substr(i+1, currentLine.length());
                }
            }
            insertToMarked(currentLine);
            std::stringstream convertStringToSquare(currentSquareString);
            convertStringToSquare >> currentSquare;

        }
        inputFile.close();

    }
    else
        cout << "Could not open file(s)" << endl;
}

void TuringMachine::convertStateFile(std::string stateFile) {

    std::ifstream inputFile;
    inputFile.open(stateFile);


    if (inputFile) {


        while (!inputFile.eof()) {


            std::string currentLine;
            std::string currentLineOther;
            getline (inputFile, currentLine);
            state.push_back(currentLine);
        }


        inputFile.close();

    }
    else
        cout << "Could not open file(s)" << endl;


}

void TuringMachine::insertToMarked(std::string stateString) {
    int length = stateString.length();
    for (int i = 0; i < length; i++) {
        int tempInt = 0;

        if (stateString.find(',') == i){
            std::string temp = stateString.substr(0, i);
            stateString = stateString.substr(i+1, stateString.length());

            std::stringstream convertStringToInt(temp);
            convertStringToInt >> tempInt;
            marked.insert(tempInt);
            i = 0;

        }


    }
    if (stateString.length() == 1){
        int tempInt = 0;
        std::stringstream convertStringToInt(stateString);
        convertStringToInt >> tempInt;
        marked.insert(tempInt);


    }



}

std::string TuringMachine::statesToString() const{

int stateCounter = 1;
std::string tempString;

    for (auto it = state.begin(); it != state.end(); it++) {

            tempString =  tempString  + "State "+ std::to_string(stateCounter)+": " + *it + "\n";
            stateCounter++;


    }


    return tempString;

}

void TuringMachine::update() {
    std::string currentState = state.at(this->currentState - 1);
    if (this->currentState == 0)
        return;


    if (readSquare()) {

        for (int i = 0; i < currentState.length(); i++) {

            if (currentState.find(':') == i) {
                currentState = currentState.substr(i + 1);
                break;
            }
        }



        if (currentState.at(0) == '0')
            removeMark();
        if (currentState.at(2) == 'R')
            moveRight();
        else if (currentState.at(2) == 'L')
            moveLeft();


    }

    else{


        for (int i = 0; i < currentState.length(); i++) {

            if (currentState.find(':') == i) {
                currentState = currentState.substr(0,i);
            }
        }


        if (currentState.at(0) == '1')
            makeMark();

        if (currentState.at(2) == 'R')
            moveRight();
        else if (currentState.at(2) == 'L')
            moveLeft();
    }

    int i=0;
    while (currentState.length() !=1){
        if (currentState.length() < i)
            i=0;

        if (currentState.find(',') == i) {
            currentState = currentState.substr(i  + 1);
        }
        i++;

    }

    if (currentState.length() == 1){
        int tempInt = 0;
        std::stringstream convertStringToInt(currentState);
        convertStringToInt >> tempInt;
        for (int i = 0; i < totalStates+2; i++) {
            if (tempInt == i){
                this->currentState = i;
                break;
            }

        }
    }

}

void TuringMachine::run() {

    while (currentState!=0)
        update();



}

int TuringMachine::totalStateCount() {
    int stateCounter= 0;
    for (auto it = state.begin(); it != state.end(); it++)
        stateCounter++;

    return  stateCounter;


}







