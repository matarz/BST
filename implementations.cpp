/* 
   Author: Zakaria Almatar
   Date: 08/08/09
   Class: CS163
   Assignment: Program#4
*/
/*
   File name: implementation.h
   Contains: This file has the class' member functions' implementations 
             and definitions 
*/

#include <cstdlib>
#include <iostream>
#include <string.h>
#include "header.h"

using namespace std;


/*************************************************************************
***                            Constructor                             ***
*************************************************************************/
//sets root and parent to NULL
cont_list::cont_list()
{
  root = NULL;
  parent =NULL;                      
}


/*************************************************************************
***                            Destructor                             ***
*************************************************************************/
//deallocates the tree 

cont_list::~cont_list()
{
  destroy_tree(root);
}


/*************************************************************************
***                                ADD                                 ***
*************************************************************************/
//calls insert and supply it with root and data. Always returns 1. 
int cont_list::add(char*&Fname, char*&Lname, char*&phone, char*&last_call)  
{
  insert(root, Fname, Lname, phone, last_call);
  return 1;  
}


/*************************************************************************
***                        Public Retrieve                             ***
*************************************************************************/
//calls display p_retrieve and supply it with root, first, and last name.
//returns a pointer to a node 
display_info *cont_list::retrieve(char*&Fname, char*&Lname)
{
  display_info *temp;    //a pointer to be returned to the calling routine
  p_retrieve(root, temp, Fname, Lname);               
  
  return temp;  
}


/*************************************************************************
***                         Public Display                             ***
*************************************************************************/
//calls display_all and supply it with root.
//returns a head pointer to a LLL

display_info *cont_list::display_all()
{
  display_info *head=NULL;
  display_info *cur;
  displayAll(root, head, cur);
  return head;        
}


/*************************************************************************
***                           Destroy tree                             ***
*************************************************************************/
//deallocates all nodes in a tree. 

void cont_list::destroy_tree(cont_info*&root1)
{
  if(root1)     
  {
     destroy_tree(root1->left);
     destroy_tree(root1->right);
     delete root1;                
  }
}




/*************************************************************************
***                        Private Display                             ***
*************************************************************************/
//Displays nodes in order. 

void cont_list::displayAll(cont_info*&root1, display_info*&head, display_info*&cur)
{
  if(root1)   //if tree is not empty
  {
    displayAll(root1->left, head, cur);    //go left

    if(head)   //if a LLL exists
    {
      cur->next = new display_info;   //add a node at the end
      cur = cur->next;
      //copy the data into the node
      assign_data2(cur, root1->Fname, root1->Lname, root1->phone, root1->last_call);         
      cur->next=NULL;
    }
    else      //if a LLL doesn't exist
    {
      head = new display_info;    //add a node to head
      //copy the data into the node
      assign_data2(head, root1->Fname, root1->Lname, root1->phone, root1->last_call);                  
      head->next=NULL;
      cur = head;  
    }

    displayAll(root1->right, head, cur);   //go right 
  }
}






/*************************************************************************
***                               Insert                                ***
*************************************************************************/
//stores a contact info

void cont_list::insert(cont_info *&root1, char*&Fname, char*&Lname, char*&phone, char*&last_call)
{
  int cmp1, cmp2;  //for comparisons 
    
  if(!root1)  //if empty
  {
    //allocate memory and copy data into the root
    root1=new cont_info;  
    assign_data1(root1, Fname, Lname, phone, last_call);
    root1->left = NULL;
    root1->right = NULL;
  }
  else // if not empty
  {
    cmp1 = strcmp(root1->Lname, Lname);    //compare
    if(cmp1 > 0)           //if node's data larger go left
      insert(root1->left, Fname, Lname, phone, last_call);
    else if(cmp1 < 0)       //if node's data smaller go right
      insert(root1->right, Fname, Lname, phone, last_call);
    else  //if the same do comparison with the first name
    {
      cmp2 = strcmp(root1->Fname, Fname);
      if(cmp2 > 0)        //if node's data larger go left
        insert(root1->left, Fname, Lname, phone, last_call);
      else                //else go right
        insert(root1->right, Fname, Lname, phone, last_call);
    }
  }
}


/*************************************************************************
***                       Private Retrieve                             ***
*************************************************************************/
//checks contacts by contact's name

void cont_list::p_retrieve(cont_info *&root1, display_info *&temp, char*&Fname, char*&Lname)
{
  int cmp1, cmp2;   //used for comparisons
    
  if(!root1)        //if empty
    temp = NULL;    //set temp to NULL
  else //if not
  {
    cmp1 = strcmp(root1->Lname, Lname); //compare
    if(cmp1 > 0)              //if larger go left
      p_retrieve(root1->left, temp, Fname, Lname);
    else if(cmp1 < 0)         //if smaller go right
      p_retrieve(root1->right, temp, Fname, Lname);
    else    //if the same do more comparisons
    {
      cmp2 = strcmp(root1->Fname, Fname);
      if(cmp2 > 0)        //if larger go left
        p_retrieve(root1->left, temp, Fname, Lname);
      else if(cmp2 < 0)      //if smaller go right
        p_retrieve(root1->right, temp, Fname, Lname);
      else   //if the same 
      {  
        temp = new display_info;  //allocate memory for temp 
        //copy data into temp
        assign_data2(temp, root1->Fname, root1->Lname, root1->phone, root1->last_call);
      }
    }
  }
}



/*************************************************************************
***                              Remove                                ***
*************************************************************************/
//removes a contact
//returns 1 for success, 0 for failure. 

int cont_list::remove(char *Fname, char *Lname)
{
  int flag; //1 for being the root- 2 for being right node of parent-3 for
            //being left node of a parent
  //temporary pointer-inorder successor-parent of inorder successor
  cont_info *temp, *successor, *successor_p; 
  
  //calling find which will return the a pointer to the node needed(if found)
  temp = find(root,root,Fname,Lname);

  if(!temp)     //if match wasn't find or tree was empty
    return 0;   //return failer
  else   //if node was found
  {
    if(temp == root)      //if it the root node set flag to 1
      flag =1;
    else if(temp==parent->right)  //if right node of the parent set flag to 2
      flag =2; 
    else if(temp==parent->left)
      flag =3;        //if it left node set flag to three

    if(!temp->right && !temp->left)  //if node has no children
    {
      delete temp;
      temp=NULL;

      if(flag==1)
        root = NULL;
      else if(flag==2)
        parent->right=NULL;
      else if(flag==3)
        parent->left=NULL;
    }  
    else if(!temp->right && temp->left)      //if node has left child
    {
      if(flag==1)
        root = temp->left;
      else if(flag==2)
        parent->right=temp->left;
      else if(flag==3)
        parent->left=temp->left;

      delete temp;
      temp=NULL;   
      return 1;
    }
    else if(temp->right && !temp->left)      //if node has right child
    {
      if(flag==1)
        root = temp->right;
      else if(flag==2)
        parent->right=temp->right;
      else if(flag==3)
        parent->left=temp->right;

      delete temp;
      temp=NULL;   
      return 1;
    }
    else if(temp->right && temp->left)      //if node has two children 
    {
      successor = temp->right;  //finding inorder successor
      if(!successor->left)  //if temp->right is the inorder successor
      {
        del_data(temp);      //delete the data in the node
        //cope data from successor into the deleted node
        assign_data1(temp, successor->Fname, successor->Lname, successor->phone, successor->last_call);
        temp->right=successor->right;
        delete successor;     //deallocate successor
        successor =NULL;
        return 1;
      }
      else
      {  
        do    //do loop to find the inorder successor and its parent
        {
          successor_p = successor;        
          successor = successor->left;        
        }
        while(successor->left);

        del_data(temp);    
        //copy data from successor into deleted node.
        assign_data1(temp, successor->Fname, successor->Lname, successor->phone, successor->last_call);
        successor_p->left = successor->right;
        delete successor;       //deallocate successor
        successor =NULL;
        return 1;
      }
    }
  }
}


/*************************************************************************
***                         Find a node                                ***
*************************************************************************/
//Finds a node for removal ans supplies the calling routine with a pointer 
//to the node (if found) or returns NULL

cont_info *cont_list::find(cont_info*&root, cont_info*&par, char *Fname, char *Lname)
{
  int num1, num2;   //used for comparisons 

  if(!root)           //if node 
    return NULL;     //returns NULL
  else  //if not
  {
    num1 = strcmp(Lname,root->Lname);    //compare
    if(num1>0)         //if data is larger than node's data go right
      return find(root->right,root,Fname,Lname);
    else if(num1<0)     //if data is smaller than node's data go left
      return find(root->left,root,Fname,Lname);  
    else  //if equal compare with first name
    {
      num2=strcmp(Fname,root->Fname);  
      if(num2>0)             //if larger go right
        return find(root->right,root,Fname,Lname);
      else if(num2<0)        //if smaller go left
        return find(root->left,root,Fname,Lname);  
      else   //if equal
      {
        parent = par; //set parent to parent of the node
        return root;     //return the node
      }
    }
  }
}



/*************************************************************************
***                           Delete Data                              ***
*************************************************************************/
//Deletes the data of a tree node;
void cont_list::del_data(cont_info*&root1)
{
  delete [] root1->Fname;       //deallocate first name
  delete [] root1->Lname;       //deallocate last name
  delete [] root1->phone;        //deallocate phone number
  delete [] root1->last_call;    ////deallocate last call
}


/*************************************************************************
***                           Assing Data 1                            ***
*************************************************************************/
//assigns data to a tree node;

void cont_list::assign_data1(cont_info *&root1, char*&Fname, char*&Lname, char*&phone, char*&last_call)
{
  //allocate memory
  root1->Fname = new char[strlen(Fname)+1];
  root1->Lname = new char[strlen(Lname)+1];
  root1->phone = new char[strlen(phone)+1];
  root1->last_call = new char[strlen(last_call)+1];

  //copy data
  strcpy(root1->Fname, Fname);
  strcpy(root1->Lname, Lname);
  strcpy(root1->phone, phone);
  strcpy(root1->last_call, last_call);
}

/*************************************************************************
***                           Assing Data 2                            ***
*************************************************************************/
//assigns data to a LLL node;
void cont_list::assign_data2(display_info *&node, char*&Fname, char*&Lname, char*&phone, char*&last_call)
{

  //allocate memory
  node->Fname = new char[strlen(Fname)+1];
  node->Lname = new char[strlen(Lname)+1];
  node->phone = new char[strlen(phone)+1];
  node->last_call = new char[strlen(last_call)+1];

  //copy data
  strcpy(node->Fname, Fname);
  strcpy(node->Lname, Lname);
  strcpy(node->phone, phone);
  strcpy(node->last_call, last_call);
}
