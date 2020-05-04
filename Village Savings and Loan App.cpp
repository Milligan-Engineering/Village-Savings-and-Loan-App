//File Name: VSL.cpp
//Author: Zula Coley
//Email Address: zgcoley@my.milligan.edu
//EENG 221 Semester Project
//Description: Program used to track Village Savings and Loans groups' data and organize groups' daily operations.
//Last Changed: May 3, 2020

#include<iostream>
#include<string>
#include<numeric>
#include<ctime>
#include<fstream>
#include<search.h>
#include<algorithm>
#include<vector>
#include "stdio.h"
#include<tchar.h>

using namespace std;

int GroupNumber, Member1Savings, Member2Savings, Member3Savings, TotalGroupSavings;
int const GROUP_MAX = 11;
int const NAME_LENGTH = 40;
// Program Milestone 10B: implement a multidimensional array
// Allows the user to input names for each member of the group, as well as each borrower with a loan (line 33)
// Actual user input (lines 70-74 and 201-208)
char member[GROUP_MAX][NAME_LENGTH];
double contribution[GROUP_MAX];
int i = 1, k = 0, j = 0, m = 0, n = 0, p = 0, q = 0;
int choice, voting, yesvotes, novotes;
double groupstartingbalance = 0, groupendingbalance = 0, groupcurrentbalance = 0;
string GroupName, CommunityLocation;
const int MAX_LOANS = 10;
char loan_names[GROUP_MAX][NAME_LENGTH];
int loan_number[MAX_LOANS];
double loan_amount[MAX_LOANS];
int target, listsize;
string votingdescription;
int result;
char answer2;
int loannumber;
double loanamount;
double owedbalance;
double interestrate;
int term;
double contribution_percentage[GROUP_MAX];
double percentage;
double roundedpercentage;
char answer3;
struct LoanData
{
	int loannumber;
	double loanamount;
	double owedbalance;
	double interestrate;
	int term;
};
class MultipleLoans
{
public:
	void output();
	void input();
	string applicant;
	int term;
	string gethistory();
	int getcurrent();
	int getpastloans();
private:
	string history;
	int current;
	int pastloans;
};

void membercontributionCalculation(double contribution[], double groupstartingbalance);
void fillArray(int loan_number[], int MAX_LOANS, int& listsize);
int search(const int loan_number[], int listsize, int target);
void loanData(LoanData& Loans);

int main()
{
	//Program Milestone 05: implement a menu
	//Allows a user to choose to either begin a profile from the beginning or to enter specific group data
	do
	{
		cout << endl
			<< "Choose 1 to begin a group profile for the first time.\n"
			<< "Choose 2 to enter your group data for this month.\n"
			<< "Enter either 1 or 2 and press 'Enter'.\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "What is the name of your VSL group?\n";
			cin >> GroupName;

			cout << "What community is your VSL group from?\n";
			cin >> CommunityLocation;

			cout << "How many members are in your group?\n";
			cin >> GroupNumber;

			if (GroupNumber < GROUP_MAX)
			{
				while (i - 1 < GroupNumber)
				{
					cout << "Enter member " << i << "'s name:";
					cin >> member[j];
					cout << "\n" << endl;
					i++;
					j++;
				}
			}
			else
			{
				cout << "Your group is too large. Please enter a number equal to or less than 10.\n";
				cout << "How many members are in your group ?\n";
				cin >> GroupNumber;
				if (GroupNumber < GROUP_MAX)
				{
					while (i - 1 < GroupNumber)
					{
						cout << "Enter member " << i << "'s name:";
						cin >> member[j];
						cout << "\n" << endl;
						i++;
						j++;
					}
				}
				else
				{
					cout << "ERROR: Your group is too large. Please start again.";
					return 0;
				}
			}

			cout << "Your group members are:";
			cout << "\n";
			while (k < GroupNumber)
			{
				cout << k + 1 << ":" << member[k];
				cout << "\n" << endl;
				k++;
			}
			cout << endl;
			break;
		case 2:
			cout << "How many members are participating in your group this month?\n";
			cin >> GroupNumber;

			{
				if (GroupNumber < GROUP_MAX)
				{
					while (i - 1 < GroupNumber)
					{
						cout << "Enter member " << i << "'s name:";
						cin >> member[j];
						cout << "\n" << endl;
						i++;
						j++;
					}
				}
				else
				{
					cout << "Your group is too large. Please enter a number equal to or less than 10.\n";
					cout << "How many members are in your group ?\n";
					cin >> GroupNumber;
					if (GroupNumber < GROUP_MAX)
					{
						while (i - 1 < GroupNumber)
						{
							cout << "Enter member " << i << "'s name:";
							cin >> member[j];
							cout << "\n" << endl;
							i++;
							j++;
						}
					}
					else
					{
						cout << "ERROR: Your group is too large. Please start again.";
						return 0;
					}
				}
				{
					cout << "Your group members are:";
					cout << "\n";
					while (k < GroupNumber)
					{
						cout << k + 1 << ":" << member[k];
						cout << "\n" << endl;
						k++;
					}
					cout << endl;
				}
				break;
			}
		}
	} while (choice == 1 && choice == 2);
	{
		cout << "What has each member contributed this month?";
		cout << "\n";
		while (m < GroupNumber)
		{
			cout << member[m] << ":";
			cin >> contribution[m];
			cout << "\n" << endl;
			m++;
		}
	}
	{
		{
			int n = GroupNumber;
			for (int o = 0; o < n; o++)
			{
				groupstartingbalance += contribution[o];
			}
		}
		cout << "Your group's total savings amount this month is: " << groupstartingbalance << "\n" << "\n";
	}
	{
		cout << "What was your group's balance at the end of last month?\n";
		cin >> groupendingbalance;
		cout << "\n";
		groupcurrentbalance = groupstartingbalance + groupendingbalance;
		cout << "Your group's current balance is: " << groupcurrentbalance << "\n";
		cout << "\n";
	}
	{
		cout << "How many loans is your group managing this month?\n";
		cin >> listsize;
		cout << "\n";

		if (listsize < MAX_LOANS)
		{
			while (n + 1 <= listsize)
			{
				cout << "For loan number " << (n + 1) << " enter the borrower's name." << "\n";
				cin >> loan_names[p];
				cout << "\n" << endl;
				cout << "For loan number " << (n + 1) << " enter the amount still owed.\n";
				cin >> loan_amount[q];
				n++;
				p++;
				q++;
			}
		}
		else
		{
			cout << "Your group cannot manage that many loans. Please enter a number equal to or less than 10.\n";
			cout << "How many loans does your group have this month?\n";
			cin >> listsize;
			if (listsize < MAX_LOANS)
			{
				while (n + 1 < listsize)
				{
					cout << "\n" << "For loan number " << (n + 1) << "enter the borrower's name.\n";
					cin >> loan_names[p];
					cout << "\n" << endl;
					cout << "For loan number " << (n + 1) << " enter the amount owed.\n";
					cin >> loan_amount[q];
					cout << "\n" << endl;
					n++;
					p++;
					q++;
				}
			}
			else
			{
				cout << "ERROR: Your group cannot manage that many loans. Please start again.\n";
				return 0;
			}
		}
	}
	// Program Milestone 06: incorporate a user-defined function and a predefined function
	// Calculates and stores the percentage that each member has contributed to the monthly balance so that at the end of the cycle each member gets the appropriate percentage of profits
	// Predefined function (nearbyint()) is included in the user-defined function (membercontributionCalculation)
	{
		void membercontributionCalculation(double contribution[], double groupstartingbalance);

		cout << "\nEach member's percentage of the monthly contributions will be calculated and stored for the end of the cycle.\n";
		i = 0;
		while (i < GroupNumber)
		{
			cout << "\n" << member[i] << "'s contribution percentage for this month is (%): ";
			membercontributionCalculation(contribution, groupstartingbalance);
			cout << "\nConfirm that this is the correct percentage by entering it in exactly as shown above:";
			cin >> contribution_percentage[i];
			i++;
		}
	}
	// Program Milestone 08: read & write at least one value to a file
	// Reads the date from a text file ("date.txt")
	// Writes a short report using the information entered by the user to a text file ("questionaire.txt")
	{
		ifstream inStream;
		ofstream outStream;
		inStream.open("date.txt");
		outStream.open("questionaire.txt");
		int day, month, year;
		inStream >> day >> month >> year;
		outStream << "Date: " << day << "/" << month << "/" << year
			<< "This month, there are " << GroupNumber << " participants in the group.\n"
			<< "The total financial contribution this month is " << groupstartingbalance << ".\n"
			<< "Combined with last month's ending balance of " << groupendingbalance << ", this month the group's current balance is " << groupcurrentbalance << ".\n"
			<< "The group is managing " << listsize << " loans this month.\n";
	}
	// Program Milestong 09: implement character based input/output
	// Allows the user to enter the title/description of the vote their group takes
	{
		cout << "Does your group have any issues to vote on?\n";
		cout << "Choose 1 for 'Yes' or 2 for 'No' and press 'Enter'\n";
		cin >> voting;
		if (voting == 1)
		{
			cout << "Type the title of the issue you are voting on. When you are done, press 'Enter':\n";
			cin.ignore(1,'\n');
			getline(cin, votingdescription);

			cout << "\n";

			cout << "How many 'yes' votes are there?\n";
			cin >> yesvotes;
			cout << "How many 'no' votes are there?\n";
			cin >> novotes;

			if ((yesvotes + novotes == GroupNumber))
			{
				if (yesvotes > novotes)
				{
					cout << "The decision on the issue (" << votingdescription << ") is yes.\n";
				}
				else
				{
					cout << "The decision on the issue (" << votingdescription << ") is no.\n";
				}
			}
			else
			{
				cout << "Your total number of votes does not equal your group number. Please start again.\n";
				return 0;
			}
		}
		else
		{
			cout << "Your group has chosen to skip the voting portion of this meeting.\n";
		}
		
	}
	// Program Milestone 10A: implement a search routine
	// Allows the user to search the entered loan numbers to find who owes it and how much is owed
	{
		cout << "\n";
		fillArray(loan_number, MAX_LOANS, listsize);

		char answer;
		int result;
		do
		{
			cout << "Enter the loan number you want to find.\n";
			cin >> target;
			result = search(loan_number, listsize, target);
			if (result == -1)
				cout << "Loan number " << target << " is not currently on the list.\n";
			else
				cout << "Loan number " << target << " is owed by " << loan_names[result] << ".";
				cout << "The amount still owed (not including interest) is " << loan_amount[result] << ".\n" << "\n";
				cout << "Do you want to search another loan number? Enter Y for 'Yes' or N for 'No'\n";
				cin >> answer;
		} while ((answer != 'n') && (answer != 'N'));
	}
	// Program Milestone 11A: determine some possible collections of variables that could be implemented as structures
	// (A) loans (person/amount/interest rate/timeline)
	// (B) contributions (person/contribution for the month/percentage of total monthly balance)
	// (C) monthly data (month/participants/income/borrowers/loans)
	{
		cout << "\n";
		cout << "Now you can enter more data for the loans your group is managing and calculate the total amount owed (including interest).";
		LoanData loan;
		do
		{
			loanData(loan);
		} 
		while ((answer2 != 'n') && (answer2 != 'N'));
	}

	// Program Milestone 11B: 
	// (a) include a class (with 2 member variables and 1 member function)
	// (b) move the class so its declarations are in a header file and its definitions are in its own source file (utilize standard header file stdafx.h)
	// (c) make 1 of the member variables of the class private and create the necessary accessor and mutator functions for the variable
	// Allows the user to input history/current data for approving multiple loans protocols
	{ 
		do
		{
			MultipleLoans applicant;
			applicant.input();
			applicant.output();
		} 
		while ((answer3 != 'N') && (answer3 != 'n'));
	}
	return 0;
}
// User Function Definitions
void membercontributionCalculation(double contribution[], double groupstartingbalance)
{
	percentage = (contribution[i] / groupstartingbalance)*100;
	roundedpercentage = nearbyint(percentage);
}
void fillArray(int loan_number[], int MAX_LOANS, int& listsize)
{
	using namespace std;
	cout << "Enter up to " << MAX_LOANS << " whole numbers (starting at 1 and increasing by 1) for as many loans as your group is managing this month.Press 'Enter' after each number.\n";
	cout << "Mark the end of the list with a negative number.\n";
	int next, index = 0;
	cin >> next;
	while ((next >= 0) && (index < MAX_LOANS))
	{
		loan_number[index] = next;
		index++;
		cin >> next;
	}
	listsize = index;
}
int search(const int loan_number[], int listsize, int target)
{
		int index = 0;
		bool found = false;
		while ((!found) && (index < listsize))
			if (target == loan_number[index])
				found = true;
			else
				index++;

		if (found)
			return index;
		else
			return -1;
}
void loanData(LoanData& Loans)
{
	cout << "Enter the loan number: ";
	cin >> target;
	result = search(loan_number, listsize, target);
	if (result == -1)
		cout << "That loan number is not currently on the list. Please exit and start over if you would like to add it.\n";
	else
		cout << "\nLoan Number: " << target
		<< "\nBorrower: " << loan_names[result]
		<< "\nOriginal Loan Amount: ";
		cin >> Loans.loanamount;
		cout << "\nInterest Rate % (monthly): ";
		cin >> Loans.interestrate;
		cout << "\nLoan Term (in months): ";
		cin >> Loans.term;
		cout << "\nTotal Amount Owed:" << ((Loans.loanamount * (Loans.interestrate/100)) + Loans.loanamount);
		cout << "\nDo you have another loan that you would like to enter specific data for? Enter 'Y' for Yes or 'N' for No.\n";
		cin >> answer2;
}
void MultipleLoans::output()
{
	cout << "The applicant's name is " << applicant
		<< " and they have borrowed " << pastloans << " from your group in the past.\n";
	if (history == "yes")
		cout << "So far, " << history << ", they have paid these past loans on time.\n";
	else
		cout << "So far, " << history << ", they have not paid these past loans on time.\n";
	cout << "Also, currently, they have " << current << " loans from this group.\n";
	if ((history == "yes") && (current < 3))
		cout << "Due to " << applicant << "'s history of paying past loans on time "
		<< "and the fact that they have fewer than 3 other current loans, "
		<< applicant << "'s application for an additional loan is approved.";
	else
		cout << "Due to " << applicant << "'s history of not paying past loans on time "
		<< "and/or the fact that they have 3 or more other current loans, "
		<< applicant << "'s application for an additional loan is not approved.";
	cout << "\nDo you have another application for multiple loans that you would like to enter? Enter 'Y' for Yes or 'N' for No.";
	cin >> answer3;
}
void MultipleLoans::input()
{
	cout << "\nEnter the applicant's name:\n";
	cin >> applicant;
	cout << "\nEnter the number of past loans that this person has had:\n";
	cin >> pastloans;
	cout << "\nHas this person paid these past loans on time? Enter 'yes' or 'no'\n";
	cin >> history;
	cout << "\nHow many other loans does this person have currently?\n";
	cin >> current;

}
int MultipleLoans::getcurrent()
{
	return current;
}
string MultipleLoans::gethistory()
{
	return history;
}
int MultipleLoans::getpastloans()
{
	return pastloans;
}