// Phonebook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "stdlib.h"
#include <list>
#include <string>
#include <regex>
#include <algorithm>


using namespace std;

class PhoneBookApp
{
public:
	string ContactName;
	list<string> ContactNo;
};


class PhoneBookMethods
{
public:
	string PhoneNo;
	list<PhoneBookApp> Contacts;
	PhoneBookApp ObjContact;
	double NoOfContacts();
	string GetName();
	string GetNo();
	void AddContacts();
	void DisplayContacts();
	void SearchContact();
	void AddNewContact(PhoneBookApp&);
	int DisplaySpecificContacts(string);
	char MergeContacts(string);
	bool CheckExistingContact(string);
	int SearchByName(string);
};


bool SortMethod(PhoneBookApp a, PhoneBookApp b);
int j{ 0 };
int main()
{
	PhoneBookMethods ObjPhoneBookMethods;
	char choice{ '0' };
	while (choice != '6')
	{

		cout << "\n\n\t\b\b\b MAIN";
		cout << "\n\n\t\t\tChoose an option:\n\n\t\t\t1. Add Contact(s)\n\n\t\t\t2. Display Contacts\n\n\t\t\t3. Search Contact\n\n\t\t\t4. Exit\n\n\t\t\tPlease Enter your choice: ";
		(cin >> choice).get();
		switch (choice)
		{
		case '1':
			system("cls");
			ObjPhoneBookMethods.AddContacts();
			cout << "\n\n\t\t\b\b\b";
			system("pause");
			system("cls");
			break;

		case '2':
			system("cls");
			ObjPhoneBookMethods.Contacts.sort(SortMethod);
			ObjPhoneBookMethods.DisplayContacts();
			cout << "\n\n\t\t\b\b\b";
			system("pause");
			system("cls");
			break;

		case '3':
			system("cls");
			ObjPhoneBookMethods.SearchContact();
			system("cls");
			break;

		case '4':
			break;

		default:
			system("cls");
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
	return 0;
}

double PhoneBookMethods::NoOfContacts()
{
	double NoOfEntries;
	while ((cout << "\n\n\t\tEnter the number of entries you want to be made: ") && !(cin >> NoOfEntries) || (NoOfEntries < 0))
	{
		cout << "\n\t\t\tPlease enter valid number.";
		cin.clear();
		cin.ignore(numeric_limits< streamsize>::max(), '\n');
	}
	return NoOfEntries;
}

string PhoneBookMethods::GetName()
{
	string FName, LName, Name;
	cout << "\n\n\t\tFirst Name: ";
	cin >> FName;
	cin.ignore();
	cout << "\n\n\t\tLast Name: ";
	getline(cin, LName, '\n');
	Name = (FName + " " + LName);
	transform(Name.begin(), Name.end(), Name.begin(), toupper);

	return Name;
}

string PhoneBookMethods::GetNo()
{
	string PhoneNo;
	cout << "\n\n\t\tPhone No.: ";
	regex r("^(([0]|(\\+91-)|(\\+91))\\ d{10})|\\d{10}$");
	cin >> PhoneNo;
	while (!regex_match(PhoneNo, r))
	{
		cout << "\n\n\t\tPlease Enter a valid no.";
		cout << "\n\n\t\tPhone No.: ";
		cin >> PhoneNo;
	}
	if (PhoneNo.at(0) == '+' && PhoneNo.length() > 10)
	{
		if (PhoneNo.at(3) == '-')
		{

		}
		else
		{
			PhoneNo.replace(0, 3, "+91-");
		}
	}
	if (PhoneNo.at(0) == '0')
	{
		PhoneNo.replace(0, 1, "+91-");
	}
	if (PhoneNo.at(0) != '0' && PhoneNo.at(0) != '+')
	{
		PhoneNo = "+91-" + PhoneNo;
	}
	return PhoneNo;
}

bool SortMethod(PhoneBookApp a, PhoneBookApp b)
{
	if (a.ContactName == b.ContactName)
	{
		return a.ContactNo < b.ContactNo;
	}
	else
	{
		return a.ContactName < b.ContactName;
	}
}

void PhoneBookMethods::AddContacts()
{

	cout << "\n\n\t\b\b\bADD CONTACT";
	char ch{ 'a' };
	int temp = (int)NoOfContacts();
	int i;
	for (i = 1; i <= temp; i++)
	{
		cout << "\n\n\t\tEntry No. " << i;
		PhoneBookApp AddContact;
		ObjContact.ContactName = GetName();
		if (CheckExistingContact(ObjContact.ContactName))
		{
			cout << "\n\n\t\tContact Name already in Phone Book.\n\n\t\tDo you want to add a new contact no to existing contact?";
			cout << "\n\n\t\ty = Yes add more numbers.\n\n\t\tn = No. Add as a new contact.\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				if (DisplaySpecificContacts(ObjContact.ContactName) > 1)
				{
					cout << "\n\n\t\tEnter the Existing Contact No of the Contact: ";
					PhoneNo = GetNo();
					for (PhoneBookApp& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							for (string No : ExistingContact.ContactNo)
							{
								if (No == PhoneNo)
								{
									cout << "\n\n\t\tEnter the New Contact No.:";
									PhoneNo = GetNo();
									ch = MergeContacts(PhoneNo);
									while (ch != 'n' && ch != 'N')
									{
										if (ch == 'y' || ch == 'Y')
										{
											ExistingContact.ContactNo.push_back(PhoneNo);
											cout << "\n\n\t\tDo you want to add more contact numbers to " << ObjContact.ContactName << "?";
											cout << "\n\n\t\ty = Yes & n = No\n\n\t\tyour choice: ";
											cin >> ch;
											if (ch == 'y' || ch == 'Y')
											{
												PhoneNo = GetNo();
											}
										}
									}
									ch = 'c';
									break;
								}
							}
						}
						if (ch == 'c')
						{
							break;
						}
					}
				}
				else
				{
					for (PhoneBookApp& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							cout << "\n\n\t\tEnter the New Contact No.:";
							PhoneNo = GetNo();
							ch = MergeContacts(PhoneNo);
							while (ch != 'n' && ch != 'N')
							{
								if (ch == 'y' || ch == 'Y')
								{
									ExistingContact.ContactNo.push_back(PhoneNo);
									cout << "\n\n\t\tDo you want to add more contact no to " << ObjContact.ContactName << "?";
									cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
									cin >> ch;
									if (ch == 'y' || ch == 'Y')
									{
										PhoneNo = GetNo();
									}
								}
							}
							ch = 'x';
							break;
						}
					}
				}
			}
			if (ch == 'n' || ch == 'N')
			{
				AddNewContact(AddContact);
				j++;
			}
		}
		else
		{
			AddNewContact(AddContact);
			j++;
		}
	}
	cout << "\n\n\t\t" << j << " Contacts Added.\n\n\t\t";
	j = 0;
}

void PhoneBookMethods::DisplayContacts()
{
	cout << "\n\n\t\b\bCONTACT DETAILS";
	if (Contacts.empty())
	{
		cout << "\n\n\t\t\b\b\bNo Contacts in the phone book.";
	}
	else
	{
		cout << "\n\n\t\t\b\b\bThe details of " << Contacts.size() << " contacts are: \n";
		for (PhoneBookApp& DisplayContacts : Contacts)
		{
			cout << "\n\n\t\t\b\b\bContact Name: " << DisplayContacts.ContactName;
			cout << "\n\n\t\t\b\b\bContact No(s): ";
			DisplayContacts.ContactNo.sort();
			DisplayContacts.ContactNo.unique();
			for (string N : DisplayContacts.ContactNo)
			{
				cout << N << " ";
			}
			cout << "\n";
		}
	}
}

void PhoneBookMethods::SearchContact()
{
	char ch{ 'a' };
	while (ch != '3')
	{
		cout << "\n\n\t\b\b\bSEARCH CONTACT";
		cout << "\n\n\t\t\tChoose an option:\n\n\t\t\t1. Search Contact By Name\n\n\t\t\t2. Search Contact By No.\n\n\t\t\t3. Main Menu\n\n\t\t\tEnter your choice: ";
		(cin >> ch).get();

		switch (ch)
		{
		case '1':
			system("cls");
			cout << "\n\n\t\tEnter the Contact Name to be searched: ";
			getline(cin, ObjContact.ContactName);
			transform(ObjContact.ContactName.begin(), ObjContact.ContactName.end(), ObjContact.ContactName.begin(), toupper);
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				if (system("cls") || SearchByName(ObjContact.ContactName) > 0)
				{
					cout << "\n\n\t\t";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "\n\n\t\t\b\b\bNo Contacts with " << ObjContact.ContactName << " availbale.";
				}
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(ObjContact.ContactName);
			}

			break;

		case '2':
			system("cls");
			cout << "\n\n\t\tEnter the Contact No. to be searched: ";
			PhoneNo = GetNo();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\n\t\t\b\b\bNo Contacts with " << PhoneNo << " availbale.";
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(PhoneNo);
			}
			break;

		case '3':
			break;


		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}

void PhoneBookMethods::AddNewContact(PhoneBookApp& NewContact)
{
	char ch = 'a';
	NewContact.ContactName = ObjContact.ContactName;
	PhoneNo = GetNo();
	NewContact.ContactNo.push_back(PhoneNo);
	ch = MergeContacts(PhoneNo);
	if (ch == 'n')
	{
		j--;
	}
	else if (ch == 'y')
	{
		while (ch != 'n' && ch != 'N')
		{
			cout << "\n\n\t\tDo you want to add more contact numbers to " << NewContact.ContactName << "?";
			cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				NewContact.ContactNo.push_back(GetNo());
			}
			if (ch == 'n' || ch == 'N')
			{
				Contacts.push_back(NewContact);
			}
		}
	}
}

int PhoneBookMethods::DisplaySpecificContacts(string Detail)
{
	int i = 0;
	cout << "\n\n\t\b\b\bDISPLAY SPECIFIC CONTACT";
	if (Detail.at(0) == '+')
	{
		cout << "\n\n\t\tThe Contact Details are: \n";
		for (PhoneBookApp DisplayContact : Contacts)
		{
			for (string DisplayNo : DisplayContact.ContactNo)
			{
				if (DisplayNo == Detail)
				{
					cout << "\n\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
					for (string DisplayNo : DisplayContact.ContactNo)
					{
						cout << "\n\t\tContact No(s): ";
						cout << DisplayNo << " ";
					}
					i++;
					cout << "\n\n";
				}
			}
		}
	}
	else
	{
		cout << "\n\n\t\tThe Contact Details are: \n";
		for (PhoneBookApp DisplayContact : Contacts)
		{
			if (DisplayContact.ContactName == Detail)
			{
				cout << "\n\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
				for (string DisplayNo : DisplayContact.ContactNo)
				{
					cout << "\n\t\tContact No(s): ";
					cout << DisplayNo << " ";
				}
				i++;
				cout << "\n\n";
			}
		}
	}
	return i;
}

char PhoneBookMethods::MergeContacts(string PhoneNo)
{
	char ch;
	for (PhoneBookApp& MergeContact : Contacts)
	{
		for (string& MergeNo : MergeContact.ContactNo)
		{
			if (MergeNo == PhoneNo)
			{
				DisplaySpecificContacts(PhoneNo);
				cout << "\n\n\t\tContact with same Contact No. Already Exist.";
				cout << "\n\n\t\tDo you wish to merge it with existing contact?";
				cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					return 'n';
				}
				else if (ch == 'n' || ch == 'N')
				{
					return 'y';
				}
			}
		}
	}
	return ch = 'y';
}

bool PhoneBookMethods::CheckExistingContact(string Name)
{
	for (PhoneBookApp CheckContact : Contacts)
	{
		if (CheckContact.ContactName == Name)
		{
			return true;
		}
	}
	return false;
}

int PhoneBookMethods::SearchByName(string Detail)
{
	cout << "\n\n\t\b\b\bSEARCH CONTACT";
	int Counter = 0;
	for (PhoneBookApp SearchContact : Contacts)
	{
		if (!SearchContact.ContactName.find(Detail))
		{
			cout << "\n\n\t\tContact Name: " << SearchContact.ContactName << "\n";
			for (string DisplayNo : SearchContact.ContactNo)
			{
				cout << "\n\t\tContact No(s): ";
				cout << DisplayNo << " ";
			}
			cout << "\n\n";
			Counter++;
		}
	}
	return Counter;
}

string GetRandomString()
{
	string s1, s2, s;
	for (int i = 1; i <= 10; i++)
	{
		while (s1.length() != 5)
		{
			char c = ((rand() % 26) + 65);
			s1 += c;
		}
		while (s2.length() != 2)
		{
			char c = ((rand() % 26) + 65);
			s2 += c;
		}
		s = s1 + " " + s2;
	}
	return s;
}