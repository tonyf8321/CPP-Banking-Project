/* ******************************************************
*	Author: Tony Fountain				*
*	Date:	February 27, 2020			*
*	Synopsis:	This file, banking.cpp, is the	*
*	header file that will store the implementation	*
*	for the class and struct.			*
****************************************************** */
#ifndef BANKING_IMPL_
#define BANKING_IMPL_

//-------------------------------------------------------
void insert_beginning(string f_name, string l_name, int idInp, int place_track)
{ /* inserts profile node at beginning of list */
	Profile* temp = new Profile;
	temp->firstName = f_name;
	temp->lastName = l_name;
	temp->id = idInp;
	temp->balance = 0;
	temp->push_tracker = place_track;
	if(head == NULL)
	{
		temp->next = NULL;
		head = temp;
		return;
	}
	if( check_id(idInp) && get_id_length(idInp) >= 6 )
	{
		temp->id = idInp;
	}
	else
	{
		taken_id_redo();
	}

	temp->next = head;
	head = temp;
}
//-------------------------------------------------------
bool check_id(int idInp)
{ /* this function will check to make sure there are no other identical id values */
	Profile* temp = head;
	if( (*temp).id == idInp && ( (*temp).firstName != Fname && (*temp).lastName != Lname ) )
	{
		cout << endl << "ERROR, id taken." << endl;
		return false;
	}
	while( (*temp).next != NULL )
	{
		if( (*temp).id == idInp && ( (*temp).firstName != Fname && (*temp).lastName != Lname ) )
		{
			cout << "ERROR, id taken" << endl;
			return false;
		}
		temp = (*temp).next;
	}
	return true;
}
//-------------------------------------------------------
void taken_id_redo()
{
	Profile* temp = head;
	int dif_id;
	while( temp->firstName != Fname && temp->lastName != Lname )
	{
		temp = temp->next; /* get to the correct profile node to redo id */
	}
	cout << endl << "Enter different id#(min. length of 6 digits): ";
	cin >> dif_id;
	if( check_id(dif_id) && get_id_length(dif_id) >= 6 )
	{
		temp->id = dif_id;
		cout << "\nId successfully set." << endl;
		return;
	}
	else
		taken_id_redo();
}
//-------------------------------------------------------
int get_id_length(int idInp)
{ /* this function checks id length to ensure its at least 6 integer length */
	int id_length = 0;
	while( idInp != 0 )
	{
		idInp = idInp / 10;
		id_length++;
	}
	if( id_length < 6 )
	{
		cout << endl << "ERROR, id needs to be at least 6 characters long." << endl;
		return 0; /* id does not meet requirements as stated in cout statement above */
	}
	return id_length;
}
//-------------------------------------------------------
void create_new_prof()
{
	
}
//-------------------------------------------------------
bool check_ans_WDP(char ans_check)
{
	return	ans_check != 'n' && ans_check != 'N' && ans_check != 'y' && ans_check != 'Y';
}
//-------------------------------------------------------
void start_screen()
{
	string firstN, lastN;
	int id_set, push_track = 0;
	char opt_sel, ans;
	vector<Bank_Profiles> profiles;
	Profile* temp = NULL;

	do
	{
		cout << "Enter a number that corresponds with an option." << endl;
		cout << "Reminder: enter number to select" << endl;

		cout << "Option #1: -Log into existing profile-" << endl;
		cout << "Option #2: -Create new profil-" << endl;
		cout << "Option #3: --" << endl;
		cout << "Option #4: -End session-" << endl;
		cout << "Select Option #: ";
		cin >> opt_sel;
		cout << endl << endl;

		switch(opt_sel)
		{
			case '1':
				temp = head;
				if(temp == NULL)
				{
					cout << "ERROR: no existing profiles." << endl;
					continue;
				}
				cout << "Enter first name: ";
				cin >> Fname;
				cout << "Enter last name: ";
				cin >> Lname;

				while( temp->firstName != Fname && temp->lastName != Lname
					&& temp != NULL)
				{
					temp = temp->next;
				}
				if( temp->firstName == Fname && temp->lastName == Lname)
				{
					cout << "Enter your id: ";
					cin >> id_set;
					if( temp->id == id_set )
					{
						profiles[temp->push_tracker].access_on();
						profiles[temp->push_tracker].select_menu();
						profiles[temp->push_tracker].access_off();
					}
					else
					{
						cout << "ERROR, incorrect id" << endl;
						cout << "Going back to start screen." << endl << endl;
					}
				}
				continue;
			case '2':
				profiles.push_back( Bank_Profiles() );
				profiles[push_track].set_info(push_track);
				if( profiles[push_track].proceed_prfMenu() )
				{
					profiles[push_track].select_menu();
				}
				push_track++;
				break;
			case '4':
				return;
		}//end switch

		cout << "Go back to start screen? y/n: ";
		cin >> ans;
		if( check_ans_WDP(ans) )
		while( check_ans_WDP(ans) )
		{
			cout << "\nERROR: enter y to go to start screen or n to terminate whole program: ";
			cin >> ans;
		}
		if(ans == 'y' || ans == 'Y')
			continue;
		else
			break;
	} while(1);
}
//-------------------------------------------------------
int get_push_tracker(int idInp)
{
	
}
//-------------------------------------------------------
//*******************************************************
Bank_Profiles::Bank_Profiles()
{
	access = false;
//	secret1 = '';
}
//*******************************************************
void Bank_Profiles::withdraw()
{
	if(access == true)
	{
		Profile* temp = head;
		while( temp->firstName != Fname && temp->lastName != Lname )
		{
			temp = temp->next; /* get to correct profile node */
		}
		double withdraw, new_bal;
		char ans;
		
		cout << "\nEnter amount to withdraw: $";
		cin >> withdraw;
		cout << "Proceed withdraw of $" << withdraw << " y/n: ";
		cin >> ans;
		while( check_ans_WDP(ans) )
		{
			cout << "\nERROR: enter y to proceed or n to cancel withdraw: ";
			cin >> ans;
		}
		if(ans == 'y' || ans == 'Y')
		{
			new_bal = temp->balance - withdraw;
			if( check_overDraft(new_bal) )
			{
				temp->balance = new_bal;
				cout << "\nWithdraw successful, balance now: $" << temp->balance << endl;
				return;
			}
			else
			{
				cout << "\nERROR: Overdraft, withdraw canceled" << endl;
				return;
			}
		}
		else
		{
			cout << "\nWithdraw canceled" << endl;
			return;
		}


	}
	
}
//*******************************************************
void Bank_Profiles::deposit()
{
	if(access == true)
	{
		Profile* temp = head;
		while( temp->firstName != Fname && temp->lastName != Lname )
		{
			temp = temp->next; /* get to correct profile node */
		}

		double deposit;
		char ans;
		if( access == true)
		{
			cout << "\nEnter amount to deposit: $";
			cin >> deposit;
			cout << "Proceed deposit of $" << deposit << " y/n: ";
			cin >> ans;

			while( check_ans_WDP(ans) )
			{
				cout << "\nERROR: enter y to proceed or n to cancel deposit: ";
				cin >> ans;
			}
			if(ans == 'y' || ans == 'Y')
			{
				temp->balance = temp->balance + deposit;
				cout << "\nDeposit successful, balance now: $" << temp->balance << endl;
				return;
			}
			else
			{
				cout << "\nDeposit canceled" << endl;
				return;
			}
		}
	}		
}
//*******************************************************
bool Bank_Profiles::check_overDraft(double check_bal)
{
	return check_bal >= 0;
}
//*******************************************************
double Bank_Profiles::get_balance()
{
	if(access == true)
	{
		Profile* temp = head;
		while( temp->firstName != Fname && temp->lastName != Lname )
		{
			temp = temp->next; /* get to correct profile node */
		}
		return temp->balance;
	}
}
//*******************************************************
void Bank_Profiles::set_info(int index_helper)
{
	string first, last;
	int id_set;
	char ans;

	cout << "\nEnter first name: ";
	cin >> first;
	cout << "\nEnter last name: ";
	cin >> last;
	cout << "\nEnter id#(min. of 6 digits): ";
	cin >> id_set;
	cout << "\nInitial balance set to zero, use deposit to add money to the account." << endl;

	Fname = first;
	Lname = last;

	insert_beginning(first, last, id_set, index_helper);
}
//*******************************************************
bool Bank_Profiles::proceed_prfMenu()
{
	char ans;
	cout << "\nContinue to menu for profile: " << Fname << ' ' << Lname << " y/n: ";
	cin >> ans;
	while( check_ans_WDP(ans) )
	{
		cout << "\nERROR: enter y for profile options or n to log out of profile: ";
		cin >> ans;
	}
	if(ans == 'y' || ans == 'Y')
	{
		access_on();
		return true;
	}
	else
	{
		cout << "Now ending session with -" << Fname << ' ' << Lname << '-';
		access_off();
		return false;
	}
}
//*******************************************************
void Bank_Profiles::select_menu()
{
	bool redo = true;
	char opt_sel;
	if(access == true)
	{
		while(redo)
		{
			cout << endl;
			cout << "Enter a number that corresponds with an option." << endl;
			cout << "Reminder: enter number to select" << endl;
			cout << "Option #1: -Deposit-" << endl;
			cout << "Option #2: -Withdraw-" << endl;
			cout << "Option #3: -View Balance-" << endl;
			cout << "Option #4: -Logout-" << endl;
			cout << "Select Option #: ";
			cin >> opt_sel;

			switch(opt_sel)
			{
				case '1':
					deposit();
					break;
				case '2':
					withdraw();
					break;
				case '3':
					cout << "\nBalance: $" << get_balance() << endl;
					break;
				case '4':
					access = false;
					Fname = "";
					Lname = "";
					redo = false;
					break;
				default:
					cout << "ERROR, incorrect option entered." << endl;
					continue;
			}
		}
	}
}
//*******************************************************
void Bank_Profiles::start()
{
	set_info(1);
	cout << endl;
	select_menu();
}
//*******************************************************
void Bank_Profiles::login()
{
	cout << "\nEnter id: ";
}
//*******************************************************
void Bank_Profiles::access_on()
{
	access = true;
}
//*******************************************************
void Bank_Profiles::access_off()
{
	access = false;
}
//*******************************************************
//=======================================================
Admin::Admin()
{
//	password = '';
	access = init_status = false;
}
//=======================================================
void Admin::start_create()
{
	
}
//=======================================================
void Admin::create_profile()
{
	
}
//=======================================================
void init_admin()
{
	
}
//=======================================================
//*******************************************************
//-------------------------------------------------------


#endif //BANKING_IMPL_
