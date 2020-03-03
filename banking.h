/* ******************************************************
*	Author: Tony Fountain				*
*	Date:	February 27, 2020			*
*	Synopsis:	This  file, banking.h, is the	*
*	header file that will store the declarations	*
*	for the class and struct.			*
****************************************************** */
#ifndef BANKING_H_
#define BANKING_H_

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Profile
{ /* used to create linked list to store profiles */
public:
	string firstName, lastName;
	double balance;
	int id, push_tracker;
	Profile* next;
};

Profile* head = NULL; /* used to store all the profiles */

void insert_beginning(string f_name, string l_name, int idInp);
bool check_id(int idInp);
int get_id_length(int idInp);
void taken_id_redo();
bool check_ans_WDP(char ans_check);
void get_push_tracker();

void create_new_prof();

string Fname, Lname;

class Bank_Profiles
{
public:
	Bank_Profiles(); /* constructor, nothing in it though */
	void start();
	void out_active_user();
	void withdraw();
	void deposit();
	bool check_overDraft();
	double get_balance();
	void access_on();
	void access_off();
	void set_info(int index_helper);
	void login();
	bool check_overDraft(double check_bal);
	void select_menu();
	bool proceed_prfMenu();
private:
	bool access;
//	string secret1;
};

class Admin
{
public:
	Admin();
	void start_create();
	void create_profile();
private:
//	string password;
	bool access;
	bool init_status;
};

#endif //BANKING_H_
//*******************************************************
#include "banking.cpp"
