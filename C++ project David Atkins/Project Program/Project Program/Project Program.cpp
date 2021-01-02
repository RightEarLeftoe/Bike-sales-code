// Project Program.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;
#include <tchar.h>
#include <Windows.h>
#include "EASendMailObj.tlh"
using namespace EASendMailObjLib;
int main();
int around = 0;
int sign = 0;
//==============================================================================================================================================
struct names {//This is a struct which is used both on the email and exit function to address the user
	std::string LFirst_name;//here they will enter there first and last name will be stored. it will be user on the emails to address the users name
	std::string LLast_name;
}FLN;
//==============================================================================================================================================
const int ConnectNormal = 0;
const int ConnectSSLAuto = 1;
const int ConnectSTARTTLS = 2;
const int ConnectDirectSSL = 3;
const int ConnectTryTLS = 4;
//==============================================================================================================================================
void exit(struct names FLN) {//this i the exit function which is where the user will go at the end of the code to decide whether they wish to exit or go carry on using it
	string exitC;
	cout << "would you like to exit y/n";
	getline(cin, exitC);
	if (exitC == "y") {
		names FNL;
		std::cout << "Thanks for using the code " << FLN.LFirst_name;
		std::cout <<" "<< FLN.LLast_name << endl;
		std::exit(EXIT_FAILURE);
	}
	else {
		main();//takes user back to main
	}
}
//==============================================================================================================================================////much of the code in the _tmain function was gotten from AdminSystem from there email section. link in delcaration

int _tmain()//email function which as the name suggest will be used to send custome emails to the user
{
	string Lname1;
	string name2;//this code is used to get the users first and last name
	cout << "Please enter your first name";
	getline(cin, Lname1);
	cout << "Please enter your last name";
	getline(cin, name2);
	names FLN;
	FLN.LFirst_name = Lname1;//send information to struct
	FLN.LLast_name = name2;
	around++;
	char Lemail[256];
	std::cout << "Please, enter your email";// user inputs there email
	std::cin.getline(Lemail, 256);

	::CoInitialize(NULL);

	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));
	oSmtp->LicenseCode = _T("TryIt");

	// Set your sender email address
	oSmtp->FromAddr = _T("bikecodeorder@gmail.com");

	// Add recipient email address
	oSmtp->AddRecipientEx(_T(email), 0);

	// Set email subject
	oSmtp->Subject = (_T(name1),"Bike order");

	// Set HTML body format
	oSmtp->BodyFormat = 1;
	
	if (around > 1) {
		oSmtp->BodyText = _T("hello In the document below is the list of the bikes you have ordered. (-50% for second purchase)");
	}
	else {
		oSmtp->BodyText = _T("Hello the document below is the list of the bikes you have ordered. Thanks for your purchase");
	}
	
	// Add attachment from local disk
	if (oSmtp->AddAttachment(_T("text.txt")) != 0)
	{
		_tprintf(_T("Failed to add attachment with error: %s\r\n"),
			(const TCHAR*)oSmtp->GetLastErrDescription());
	}

	// Your SMTP server address
	oSmtp->ServerAddr = _T("smtp.gmail.com");

	// User and password for ESMTP authentication, if your server doesn't
	oSmtp->UserName = _T("bikecodeorder@gmail.com");
	oSmtp->Password = _T("Bike@Code82");
	oSmtp->ConnectType = ConnectTryTLS;
	_tprintf(_T("Start to send HTML email ...\r\n"));

	if (oSmtp->SendMail() == 0)
	{
		_tprintf(_T("email was sent successfully!\r\n"));
	}
	else
	{
		_tprintf(_T("failed to send email with the following error: %s\r\n"),
			(const TCHAR*)oSmtp->GetLastErrDescription());
	}
	exit(FLN);
}
//==============================================================================================================================================
void purchase() {//purchase function will be used to allow the user to select what bikes they wish to purchase
	int BikeN;
	int times = 0;
	string bikes[20] = {};
	string bikesin;//the arrays below are used to tell the code all the bikes which can be purchaed
	string  MpurchaseOp[20] = {"Mbike1", "Mbike2", "Mbike3", "Mbike4", "Mbike5", "Mbike6", "Mbike7", "Mbike8", "Mbike9", "Mbike10", "Mbike11", "Mbike12", "Mbike13", "Mbike14", "Mbike15", "Mbike16", "Mbike17", "Mbike18", "Mbike19", "Mbike20" };
	string  RpurchaseOp[20] = { "Rbike1", "Rbike2", "Rbike3", "Rbike4", "Rbike5", "Rbike6", "Rbike7", "Rbike8", "Rbike9", "Rbike10", "Rbike11", "Rbike12", "Rbike13", "Rbike14", "Rbike15", "Rbike16", "Rbike17", "Rbike18", "Rbike19", "Rbike20" };
	
	

	cout << "Please enter how many bikes you would like to order";//enters how many bikes they wish to order
	cin >> BikeN;
	cin.ignore(INT_MAX, '\n');
	while (times < BikeN) {
		cout << "Please enter the bikes you wish to purchase e.g. Rbike1, Mbike8...";
		getline(cin, bikesin);
		if (std::find(std::begin(MpurchaseOp), std::end(MpurchaseOp), bikesin) != std::end(MpurchaseOp)) {//checks to see if inputted bikes are in teh arrays. if not it will send the user back to the start of this function. This code was gotten from Cplusplus link in delcaration
			bikes[times] = bikesin;
			times++;
		}
		else if (std::find(std::begin(RpurchaseOp), std::end(RpurchaseOp), bikesin) != std::end(RpurchaseOp)) {//This code was gotten from Cplusplus link in delcaration
			bikes[times] = bikesin;
			times++;
		}
		else { cout << "Incorrect input please enter correct names e.g. Rbike1 - Rbike20, Mbike1 - Mbike20"; 
		purchase();//sends user back to start of function if a mistake is made
		}
	}
	ofstream myfile("text.txt");//adds the bikes the user selected to a text file for later use
	cout << "file writen operation" << endl;
	for (int i = 0; i < times; i++) {
		myfile << bikes[i] << "\n";

	}
	myfile.close();//closes the text file
	_tmain();//takes the user to the email function
}
//==============================================================================================================================================
void mountain(int budget) {//this code is used to display all the mountain bikes
	if (budget < 6) {
		int options[7] = { 1, 5, 9, 14, 18, 22, };//this is ued to select the line on the text file
		int LINE = options[budget];
		int times = 0;
		while (times < 4) {//prints out the selected bikes the user wanted.
			std::ifstream f("MountBikes.txt");
			std::string s;
			for (int i = 1; i <= LINE; i++)
				std::getline(f, s);
			std::cout << s << endl;
			times++;
			LINE++;
		}
	}
	else if (budget==6) {//this section of the code is used so that if the user wants to see all the options for mountain bikes they can
		string line;
		ifstream myfile("MountBikes.txt");//opens file
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				cout << line << '\n';
			}
			myfile.close();//closes file
		}

		else cout << "Unable to open file"<< endl;
	}
	else {
		cout << "inavlid input. please enter between 1-6" << endl;
		main();//takes user back to main if there is an incorrect input
	}
}
//==============================================================================================================================================
void road(int budget) {//this function is ued to display all of the road bike options on the code
	if (budget < 6) {
		int options[7] = { 1, 5, 9, 14, 18, 22, };//this array is used to select which line in the file is to be prinnted. 
		int LINE = options[budget];
		int times = 0;
		while (times < 4) {
			std::ifstream f("RoadBikes.txt");//opens file
			std::string s;
			for (int i = 1; i <= LINE; i++)
				std::getline(f, s);
			std::cout << s << endl;
			times++;
			LINE++;
		}
	}
	else if (budget == 6) {
		string line;
		ifstream myfile("RoadBikes.txt");//opens file
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				cout << line << '\n';
			}
			myfile.close();//closes file
		}

		else cout << "Unable to open file" << endl;
	}
	else {
		cout << "inavlid input. please enter between 1-6" << endl;
		main();//takes user bck to main if a mistake is made
	}
}

//==============================================================================================================================================
bool accountNew() {// this is where the user will go to make an account and sign into and account
	int i;
	string username;
	string password;
	string accountc;
	cout << "Do you have an account y/n" << endl;
	getline(cin, accountc);
	if (accountc == "n") {

		ofstream myfile("users.txt");//opens the username and password files
		ofstream myfile2("pass.txt");

		cout << "please create a username";//asks the user to create a user name
		getline(cin, username);
		cout << "please create a password";//asks the user to create a password
		getline(cin, password);

		for (i = 0; (i < 100 && username[i] != '\0'); i++)
			username[i] = username[i] + 2; //this section of the code will encrypt the username. code gotten from TRYTOPROGRAM link in decleration
//		cout << "\nEncrypted string: " << username << endl;

		for (i = 0; (i < 100 && password[i] != '\0'); i++)
			password[i] = password[i] + 2; //this section of the code will encrypt the password. code gotten from TRYTOPROGRAM link in decleration
//		cout << "\nEncrypted string: " << password << endl;

		myfile2 << password << "\n";
		myfile << username << "\n";
		myfile.close();//this code adds the user inputs to the files and then closes them until needed later
		myfile2.close();
		accountNew();//this takes the user back to the start if the function so that they can enter the usernames and passwords they have just created
	}
	else if (accountc != "y") {
		cout << "incorrect input please enter either y/n";
		accountNew();//this is validation so if the incrroect inputted is iputted they are sent back to the beginning of the function
	}
	else {
		string username2;
		cout << "please enter username";
		getline(cin, username2);
		for (i = 0; (i < 100 && username2[i] != '\0'); i++)
			username2[i] = username2[i] + 2; //this code encrypts the code username so that i can be then checked against what is in the file. code gotten from TRYTOPROGRAM link in decleration
//		cout << "\nEncrypted string: " << username2 << endl;
//==============================================================================================================================================
		int offset;
		int times1 = 0;
		string line;
		ifstream Myfile;//opens file and sets it to this varible
		Myfile.open("users.txt");

		if (Myfile.is_open())
		{
			while (!Myfile.eof())
			{
				while (times1 < 1) {
					getline(Myfile, line);
					times1++;
				}
				if ((offset = line.find(username2, 0))!= string::npos)//checks to see if the usernme input is in teh file from stack overflow link in decleration
				{
//					cout << "found '" << username2 << "\n\n" << line << endl;
//==============================================================================================================================================
					string password2;
					cout << "please enter password";//if the username is correct than it will move onto the checking the password using the same method
					getline(cin, password2);
					for (i = 0; (i < 100 && password2[i] != '\0'); i++)
						password2[i] = password2[i] + 2;// encrypts the password so it can be checked against the file. code gotten from TRYTOPROGRAM link in decleration
//					cout << "\nEncrypted string: " << password2 << endl;

					int offset2;
					int times2 = 0;
					string line2;
					ifstream Myfile2;//opens the file containing the passwords
					Myfile2.open("pass.txt");

					if (Myfile2.is_open())//
					{
						while (!Myfile2.eof())
						{
							while (times2 < 1) {
								getline(Myfile2, line2);
								times2++;
							}
							if ((offset2 = line2.find(password2, 0)) != string::npos)//checks to see if inputted password is in file from stack overflow link in decleration
							{
//								cout << "found '" << password2 << "\n\n" << line2 << endl;
								main();//if corrects takes it to main to start the rest of the program
								return true;
							}
							else {
								cout << "password incorrect" << endl;
								accountNew();//if fail take back to start of function
							}
						}
						Myfile2.close();
					}
					else
						cout << "Unable to open this file." << endl;
				}
					else {
						cout << "username incorrect" << endl;
						accountNew();//if username incorrect takes back to start of function
					}
			}
			Myfile.close();//closes file
		}
		else
			cout << "Unable to open this file." << endl;
	}
}
//==============================================================================================================================================

	int main() {
		if (sign < 1) {
			sign++;//checks to see if user has already entered theere username and password
			accountNew();//if the havent it will take them to account function
		}
		else if (sign >= 1) {
			cout << "already logged in" << endl;
			string desision;
			string choice;
			int budget;
			cout << "would you like to look at road or mountain bikes (road/mount)";//asks the user what kinds of bike they wish to look at
			getline(cin, choice);
			if (choice != "road" && choice != "mount") {//validation for last input
				main();
			}
			else {
				cout << "Do you have a budget at all?" << "\n" << "6 - none budget " << "\n" << "0 - £0 - £200 " << "\n" << "1 - £200 - £400" << "\n" << "2 - £400 - £600" << "\n" << "3 - £600 - £800" << "\n" << "4 - £800 - £1000" << "\n" << "5 - £1000 +";//asks the user what budget they want
				cin >> budget;
					if (choice == "mount") {//the folllowing if and else statments take the user to the correct function depending on what they have so far inputted.
						mountain(budget);
					}
					else if (choice == "road") {
						road(budget);
					}
					else if (choice == "all") {
						mountain(budget);
						road(budget);
					}
					else {
						cout << "In correct input please re enter information " << endl;
						main();//if input is incorrect takes uer back to the beginning
					}

					cout << "Would you like to keep browsing(b) or purchae(p) some bikes? b/p";//once the users have gone through the functions looking at the bikes they will have the option to select either the order some bikes or keep broswing.
					cin.ignore();
					getline(cin, desision);
					if (desision == "b") {
						main();//takes user back to start
					}
					else if (desision == "p") {
						purchase();//takes user to purchase function
					}

					_tmain();
			}
		}
	}

