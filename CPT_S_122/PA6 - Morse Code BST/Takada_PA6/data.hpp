#pragma once
#include "header.hpp"

template <class T1, class T2>
class Data {
public:
	//Constructor
	Data(T1 newChar = NULL, T2 newCode = NULL);
	//Destructor
	~Data();
	//Getters
	T1 getLetter()const;
	T2 getMorseCode()const;
	//Setters
	void setLetter(T1 &newLet);
	void setMorseCode(T2 &newCode);


private:
	T1 letter;
	T2 morseCode;
};

template <class T1, class T2>
Data<T1, T2>::Data(T1 newChar, T2 newCode) {
	this->letter = newChar;
	this->morseCode = newCode;
}

template<class T1, class T2>
Data<T1, T2>::~Data() {
	//Does Nothing
}

template <class T1, class T2>
T1 Data<T1, T2>::getLetter()const {
	return this->letter;
}

template <class T1, class T2>
T2 Data<T1, T2>::getMorseCode()const {
	return this->morseCode;
}

template <class T1, class T2>
void Data<T1, T2>::setLetter(T1 &newLet) {
	this->letter = newLet;
}

template<class T1, class T2>
void Data<T1, T2>::setMorseCode(T2& newCode) {
	this->morseCode = newCode;
}