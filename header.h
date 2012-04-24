/* 
   Author: Zakaria Almatar
   Date: 08/08/09
   Class: CS163
   Assignment: Program#4
*/
/*
   File name: header.h
   Contains: This file has the class and structures declarations
*/


#include <cstdlib>
#include <iostream>
#include <string.h>

using namespace std;

struct cont_info  //structure which holds information of one contact
{
  char *Fname, *Lname, *phone, *last_call;
  cont_info *right;
  cont_info *left;
};  

struct display_info  //structure which holds information of one contact
{
  char *Fname, *Lname, *phone, *last_call;
  display_info *next;
};

class cont_list
{
  public:
    cont_list();        //sets root to NULL
    ~cont_list();       //deallocates the tree and sets root to NULL
    int add(char*&Fname, char*&Lname, char*&phone, char*&last_call);  //adds a contact 
    display_info *retrieve(char*&Fname, char*&Lname);                 //checks a contact's information
    int remove(char *Fname, char *Lname);                             //removes a contact
    display_info *display_all();                                      //displays all contacts
        
  private:
    void remove(cont_list *&root1, char*&Fname, char*&Lname);                                          //removes a contact
    void displayAll(cont_info*&root1, display_info*&head, display_info*&cur);                          //displays all contacts
    void insert(cont_info *&root1, char*&Fname, char*&Lname, char*&phone, char*&last_call);            //stores a contact info
    void assign_data1(cont_info *&root1, char*&Fname, char*&Lname, char*&phone, char*&last_call);      //assigns data to a tree node;
    void assign_data2(display_info *&root1, char*&Fname, char*&Lname, char*&phone, char*&last_call);   //assigns data to a LLL node;
    void p_retrieve(cont_info *&root1, display_info *&temp, char*&Fname, char*&Lname);                //checks a contacts info
    void del_data(cont_info*&root1);                     //deletes data from a node
    void destroy_tree(cont_info*&root1);                 //deletes a tree
    cont_info *find(cont_info*&root, cont_info*&par, char *Fname, char *Lname);    //finds a node and it's parent
    cont_info *root;      //root pointer
    cont_info *parent;    //used for removal
};
