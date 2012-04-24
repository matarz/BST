/* 
   Author: Zakaria Almatar
   Date: 08/08/09
   Class: CS163
   Assignment: Program#4

   Purpose: The purpose of this progarm is to keep a save someone's contacts
            and have them sorted alphabetically. 
*/
/*
   File name: main.cpp
   Contains: This file has the client program and all interactions with
             the user(s)
*/


#include <cstdlib>
#include <iostream>
#include <string.h>
#include "header.h"

using namespace std;


int u_add(cont_list &cnts);          //Add
int u_retrieve(cont_list &cnts);     //check
int u_remove(cont_list &cnts);       //remove
int u_display_all(cont_list &cnts);  //display
int main_menu();                     //main menu



/*************************************************************************
***                               Main                                 ***
*************************************************************************/
//user's functions
int main()
{
  int choice;
  cont_list contacts;
  cont_info *temp;


  do 
  {
    choice = main_menu();  //get the user's choice

	if(choice == 1)  // Store
      choice= u_add(contacts);
    else if(choice ==2) // Retrieve
      choice= u_retrieve(contacts);
    else if(choice == 3)  // Remove
      choice= u_remove(contacts);
    else if(choice == 4)  // Remove
      choice= u_display_all(contacts); 
    else if(choice == 5)  // quit
      cout<<"\nQuitting...";

  }while(choice ==0); 

  return 0;
}



/*************************************************************************
***                       Main menu function                           ***
*************************************************************************/
// This function's purpose is to get the user's choice and return it. 

int main_menu()
{
  int choice;  // to hold the user's choice
  do
  { 
    cout <<"\n\n  +---------------------------------------------+" <<endl;
    cout <<"     1- Add a contact." <<endl;
    cout <<"     2- Check a contact's information." <<endl;
    cout <<"     3- Remove a contact." <<endl;
    cout <<"     4- Display all." <<endl;
    cout <<"     5- Quit." <<endl;
    cout <<"  +---------------------------------------------+" <<endl;
    cout << endl;

    cout <<"Please, enter the number of your choice: "; 
    cin>>choice;    //get choice

  }while (choice<1 || choice>5);

 return choice;
}



/*************************************************************************
***                           User's Add                               ***
*************************************************************************/
//user's funtion

int u_add(cont_list &cnts)
{
  int result;
  char *Fname = new char[25];
  char *Lname = new char[25];
  char *phone = new char[20];
  char *last_call= new char[15];

  cin.ignore();
  
  cout<<"\nEnter the contact's first name: ";
  cin.get(Fname,25);
  cin.ignore();
  
  cout<<"\nEnter the contact's last name: ";
  cin.get(Lname,25);
  cin.ignore();
  
  cout<<"\nEnter the contact's phone number: ";
  cin.get(phone,20);
  cin.ignore();
  
  cout<<"\nEnter the last call's date: ";
  cin.get(last_call,15);
  cin.ignore();
    
//  result = cnts.add(Fname, Lname, phone, last_call);
    cnts.add(Fname,Lname,phone,last_call);

  if (result==1)
    cout<<"\nInformation was stored successfully";
  else
    cout<<"\n No information was stored. Make sure the date is in the right format";

  return 0;
}



/*************************************************************************
***                        User's Retrieve                             ***
*************************************************************************/
//user's funtion
int u_retrieve(cont_list &cnts)
{
  display_info *temp;
  char *Fname = new char[25];
  char *Lname = new char[25];  

  cin.ignore();
  
  cout<<"\nEnter the contact's first name: ";
  cin.get(Fname,25);
  cin.ignore();
  
  cout<<"\nEnter the contact's last name: ";
  cin.get(Lname,25);
  cin.ignore();

  temp= cnts.retrieve(Fname, Lname);

  if(temp == NULL)
    cout<<"\nNo match was found!\n";
  else
  {
    cout<<endl;
    cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
    cout<<"Last name: "<<temp->Lname<<endl;
    cout<<"First name: "<<temp->Fname<<endl;
    cout<<"Phone number: "<<temp->phone<<endl;
    cout<<"Last call: "<<temp->last_call<<endl;
    cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
  }

  return 0;   
}


/*************************************************************************
***                       User's Display All                           ***
*************************************************************************/
//user's funtion
int u_display_all(cont_list &cnts)
{
  display_info *head, *cur;
  head = cnts.display_all();
  cur = head;
  while(cur)
  {
    cout<<endl;
    cout<<"Last name: "<<cur->Lname<<endl;
    cout<<"First name: "<<cur->Fname<<endl;
    cout<<"Phone number: "<<cur->phone<<endl;
    cout<<"Last call: "<<cur->last_call<<endl;
    cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
    cur=cur->next;
  }
  
  return 0;
}

/*************************************************************************
***                          User's Remove                             ***
*************************************************************************/
//user's funtion

int u_remove(cont_list &cnts)
{
  int flag;
  char *Fname = new char[25];
  char *Lname = new char[25];  

  cin.ignore();
  
  cout<<"\nEnter the contact's first name: ";
  cin.get(Fname,25);
  cin.ignore();
  
  cout<<"\nEnter the contact's last name: ";
  cin.get(Lname,25);
  cin.ignore();

  flag = cnts.remove(Fname, Lname);

  if(flag == 0)
    cout<<"\nNo match was found!\n";
  else
    cout<<"\nThe contact was deleted successfully.!\n";

  return 0;    
}
