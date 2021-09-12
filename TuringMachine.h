
//
// Created by Ali Alkahli on 10/26/20.
//
#include <iostream>
#include <set>
#include <vector>
#include <fstream>

#ifndef TURINGMACHINE_TURINGMACHINE_H
#define TURINGMACHINE_TURINGMACHINE_H



class TuringMachine{
private:
    int currentSquare = 0;
    int left = 0;
    int right = 0;
    int currentState = 1;
    int totalStates;
    std::set<int> marked = {};
    std::set<int> tape = {0};
    std::vector<std::string> state;


    void convertTapeFile(std::string tapeFile);
    void convertStateFile(std::string stateFile);
    void insertToMarked(std::string stateString);
    int totalStateCount();


public:
    TuringMachine();
    TuringMachine(std::string tapeFile, std::string stateFile);

    void moveLeft();
    void moveRight();
    void makeMark();
    void removeMark();
    bool readSquare() const;
    std::string tapeToString() const;
    std::string statesToString() const;
    void update();
    void run();
    void print();
    bool freeze();






};



#endif //TURINGMACHINE_TURINGMACHINE_H
