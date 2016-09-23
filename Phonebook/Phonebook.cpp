// Phonebook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
static int currentEntry = 0;
char phoneBook[10][2][50];

void showMenu() {
	cout << "---------------------" << endl;
	cout << "What do you want to do:" << endl;
	cout << "---------------------" << endl;
	cout << "[A]dd new entry -- enter A" << endl;
	cout << "[D]isplay -- enter D" << endl;
	cout << "[Q]uit -- enter Q" << endl;
}

void addPhoneBook() {
	if (currentEntry >= 10) {
		cout << "Your Phone book is full." << endl;
		return;
	}
	cout << "Entry: ";
	int entry;
	cin >> entry;

	if (entry != currentEntry + 1) {
		cout << "You entered Invalid number." << endl;
		entry = 0;
		return;
	}
	char name[50];
	cout << currentEntry << " Please enter name: ";
	cin >> name;
	for (int i = 0; i <= currentEntry; i++) {
		if (strcmp(phoneBook[i][0], name) == 0) {
			cout << name << " This name already exists in your phonebook!" << endl;
			return;
		}
	}

	cout << "Please enter phone number:";
	char phone[50];
	cin >> phone;
	strcpy_s(phoneBook[currentEntry][0], name);
	strcpy_s(phoneBook[currentEntry][1], phone);
	currentEntry++;
}
void display() {
	for (int i = 0; i < currentEntry; i++) {
		cout << "Entry " << i + 1 << " Name: " << phoneBook[i][0] << " Number: " << phoneBook[i][1] << endl;
	}
}

int main() {
	char option = ' ';
	while (option != 'Q') {
		showMenu();
		cin >> option;
		switch (option)
		{
		case 'A':
			addPhoneBook();
			break;
		case 'D':
			display();
			break;
		case 'Q':
			break;
		default:
			break;
		}
		cout << endl;
	}



	return 0;
}

