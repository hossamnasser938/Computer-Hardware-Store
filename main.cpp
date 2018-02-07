/*
Faculty Of Electronic Engineering
Menofia University
Computer Hardware Store Software
Written By : Hosam Abdelnaser Mahmood
Under The Supervision Of Eng / Ahmad Ghozia
*/

#include <iostream>                        //Header file for using cin and cout functions
#include <fstream>                        //Header file for storing and reading data in and from a file
#include <iomanip>                       //Header file for using setw function
#include <cstdlib>                      //Header file for pausing the program
#include <conio.h>                     //Header file for using getch() function to hide the password the user enters

using namespace std;

struct item                                              //Declaring item's data by a structure
{
    string name;
    int quantity;
    float price;
};

char password[11];                       //Declaring global variable holds the password
char checkPassword[11];                 //Declaring array of characters to hold the password the user enters

//Functions declaration
void preparingidentity ();                             //A function gets password from the file to the memory
bool checkIdentity ();                                //A function checks the identity of the user
void changeIdentity ();                              //A function allows the user to change user name and password
void copyingDataFromFileToMemory ();                //A function copies the data from the file in the hard disk to the array in memory
void userAction ();                                //A function takes action from the user
void SavingData ();                               //A function saves the data after work
void addNewItem ();                              //A function allows the user to add new item in the store
void updateStore ();                            //A function allows the user to add extra quantity to the existing items in the store
void viewItems ();                             //A function allows the user to display all items on the screen
void sellItem ();                             //A function allows the user to sell a specific item with a specific quantity
void checkEmptySpace ();                     //A function allows the user to know how many items in the store and how many items he will be able to enter besides the old ones
bool compstring (string ,string );          //A function helps me to search for an item to be sold by comparing between the name the user enters and the names of the items
void printLineInTable();                   //A unction helps me print a line in the table to help form it
bool testPassword (char [],char []);      //A function tests the password the user enters
void getPasswordFromUser ();             //A function gets password from the user
void getPasswordFromUserAgain (char []);//A function asks for the password again for certainty
void addSeparateLine ();               //A function adds line to separate things
void takingActionAfterFunction ();    //A function takes action from user after performing a complete process


item* pointerToItems = new item [100];               //Declaring array of items by memory allocation

int counter=0;                                       //Declaring global counter to know the number of items in the array
char hyphenMinus='-',verticalBar='|';               //Declaring global characters to help make the table

//Start of main function
int main()
{
    preparingidentity ();                      //Getting password from the file to test it
    if(checkIdentity () == false)             //Testing the password from the user
    {
        cout<<"\n\nSorry,wrong password\n\n";    //If the user enters wrong password close the program
        system ("pause");
        return 0;
    }
    copyingDataFromFileToMemory ();          //getting data from the file to the ram
    userAction ();                          //Taking action from the user
    system("pause");                      //Do not close the program till i do
    return 0;
}
//End of main function

//start of preparingIdentity function
void preparingidentity ()
{
    char letter;
    ifstream identity_file("identity.txt");        //Open the file in which the password exists
    if(identity_file.is_open())
    {
        int i=0;
        while(identity_file>>letter)
        {
            password[i]=letter;                  //Copy the password from the file to the variable password
            i++;
        }
    }
    else
    {
        cout<<"Sorry,File is not open\n";
    }
}
//End of preparingIdentity function

//Start of getIdentity function
bool checkIdentity ()
{
    cout<<"Password:";                                 //Asking the user for password
    getPasswordFromUser ();

    if(testPassword(checkPassword,password)==true)     //Checking user name and password
    {
        return true;
    }
    return false;
}
//End of getIdentity function

//Start of changeIdentity function
void changeIdentity ()
{
    cout<<"Please, Enter the old password\n\n";   //Asking the user for the old password
    if(checkIdentity () == false)                //Checking it
    {
        cout<<"\n\nWrong password";
        takingActionAfterFunction();
    }
    cout<<"\n\nPlease, Enter password from 10 characters";
    cout<<"\n\nNew password : ";                                 //Asking the user for the new password
    getPasswordFromUser ();                                     //Getting it
    cout<<"\n\nEnter new password again please\n\n";
    cout<<"New password again : ";                              //Asking for it again for certainty
    char PasswordAgain [11];
    getPasswordFromUserAgain (PasswordAgain);                  //Getting it again
    if(testPassword(PasswordAgain,checkPassword)==true)       //Checking the two passwords
    {
    ofstream identity_file("identity.txt");
    for(int i=0;i<10;i++)
    {                                                           //Opening the file in which we will store the new password
          identity_file<<checkPassword[i];                     //Storing it
    }

    system ("cls");
    cout<<"\n\nChanged successfully";
    }
    else                                                  //If they do not match
    {
        cout<<"\n\nSorry,The two passwords do not match";
    }
    takingActionAfterFunction();
}
//End of changeIdentity function

//Start of copyingDataFromFileToMemory function
void copyingDataFromFileToMemory ()
{
    system ("cls");
    //getting data from the file to the memory in the beginning of the program
    string tempName;                     //Declaring temporary variables to copy the data from the file to the memory
    int tempQuantity;
    float tempPrice;
    ifstream in_file ("items.txt");      //Opening the file from the hard disk
    if(in_file.is_open())
    {
        while(in_file>>tempName>>tempQuantity>>tempPrice)        //Copying the data from the file to the memory
        {
            (*(pointerToItems+counter)).name=tempName;
            (*(pointerToItems+counter)).quantity=tempQuantity;
            (*(pointerToItems+counter)).price=tempPrice;
            counter++;
        }
    }
    else
    {
        cout<<"Sorry, file is not open\n\n";
    }
}
//End of copyingDataFromFileToMemory function

//Start of userAction function
void userAction ()
{
    cout<<"\n                                       Welcome To Your Computer Hardware Store Software                                       ";
    addSeparateLine();
    short choice;               //Declaring a variable to hold the choice of the user
    //getting action from the user
    do
    {
        cout<<"Enter Your Choice, Please :-\n\n";
        cout<<"1 Add New Item\n";
        cout<<"2 Update Store\n";
        cout<<"3 View Items\n";
        cout<<"4 Sell Item\n";
        cout<<"5 Check Empty Space\n";
        cout<<"6 Change Password\n";
        cout<<"7 Save and Exit\n\n";
        addSeparateLine();
        cout<<"choice:";
        cin>>choice;
        //Avoiding user's mistakes in entering values
        while(!cin)
        {
            cout<<"Sorry, You entered wrong choice\n";
            cout<<"Enter again, please\n";
            cout<<"choice:";
            cin.clear();
            cin.ignore(256,'\n');
            cin>>choice;
        }

        //Checking the choice of the user
        switch(choice)
        {
            case 1 :
                {
                    system("cls");                     //Clearing the screen
                    addNewItem();                     //Calling a function to add item
                }
                break;
            case 2 :
                {
                    system("cls");                  //Clearing screen
                    updateStore();                 //Calling a function to change the quantity or price of an item
                }
                break;
            case 3 :
                {
                    system("cls");                     //Clearing the screen
                    viewItems();                      //Calling a function to display items with their quantity and price
                }
                break;
            case 4 :
                {
                    system("cls");                     //Clearing the screen
                    sellItem();                       //Calling a function to sell an item
                }
                break;
            case 5 :
                {
                    system("cls");                     //Clearing the screen
                    checkEmptySpace();                //Calling a function to give the user information about the number of items and the space which he has
                }
                break;
            case 6 :
                {
                    system ("cls");                   //Clearing screen
                    changeIdentity();                //Calling a function to change the password
                }
                break;
            case 7 :
                {
                    system("cls");                 //Clearing screen
                    SavingData();                 //Calling a function to save data at the end of the program
                }
                break;                         //Get out from switch when the user choose save and exit to carry out the function that saves data
            default :
                cout<<"Sorry, You entered a wrong number, Please try again\n\n";  //Avoiding user's mistakes
        }
    }
    while(choice!=7);                 //When the user hit 5 get out from the loop
    //End of do while loop

}
//End of userAction function

//Start of savingData function
void SavingData ()
{
    //saving data in the file in the end of the program
    ofstream out_file ("items.txt");          //Open file again to save the data in it
    if(out_file.is_open())
    {
        for(int i=0;i<counter;i++)           //Storing the data from memory into the file
        {
            out_file<<setw(20)<<setiosflags(ios::left)<<(*(pointerToItems+i)).name;
            out_file<<setw(10)<<setiosflags(ios::left)<<(*(pointerToItems+i)).quantity;
            out_file<<setw(10)<<setiosflags(ios::left)<<(*(pointerToItems+i)).price<<endl;;
        }
        cout<<"\nData saved successfully \n";
    }
    else
    {
        cout<<"Sorry, file is not open\n";
    }

    delete [] pointerToItems;           //Freeing memory after saving data
    exit(0);
}
//End of savingData function

//Start of addNewItem function
void addNewItem ()
{
    float floatTemp;                        //Tow temporary variables to avoiding entering float number instead of integer by the user
    int intTemp;
    if(counter != 99)                   //Checking whether the array is full or not
    {
        cout<<"\nEnter item data, please\n\n";
        cout<<"To return to main menu enter \"0\" anywhere\n\n";
        cout<<"Name:";       cin>>(*(pointerToItems+counter)).name;
        if((*(pointerToItems+counter)).name=="0")    //If the user enters 0 clear screen, leave the function and go back to maim menu
        {
            system("cls");
            return;
        }
        cout<<"Quantity:";   cin>>floatTemp;
        while(!cin)                //Avoiding user's mistakes by entering string instead of integer value
        {
            cout<<"Sorry, You entered wrong quantity\n";
            cout<<"Enter again, please\n";
            cout<<"Quantity:";
            cin.clear();
            cin.ignore(256,'\n');
            cin>>floatTemp;
        }
        intTemp=floatTemp;
        while(floatTemp-intTemp!=0)        //Avoiding user's mistakes by entering float value instead of integer one
        {
            cout<<"Sorry, You entered wrong quantity\n";
            cout<<"Enter again, please\n";
            cin.clear();
            cin.ignore(256,'\n');
            cin>>floatTemp;
            intTemp=floatTemp;
        }
        (*(pointerToItems+counter)).quantity=intTemp;        //Getting the correct value
        if((*(pointerToItems+counter)).quantity==0)
        {
        system("cls");                                     //If the user enters 0 clear screen, leave the function and go back to the main menu
        return;
        }
        cout<<"Price:";      cin>>(*(pointerToItems+counter)).price;
        if((*(pointerToItems+counter)).price==0)
        {
            system("cls");                                 //If the user enters 0 clear screen, leave the function and go back to the main menu
            return;
        }
        while(!cin)                                        //Avoiding user's mistakes by entering string instead of float one
        {
            cout<<"Sorry, You entered wrong price\n";
            cout<<"Enter again, please\n";
            cout<<"Price:";
            cin.clear();
            cin.ignore(256,'\n');
            cin>>(*(pointerToItems+counter)).price;
         }
         counter++;                                        //Increment the counter after adding a new item
         cout<<"Added successfully\n";
    }
    else
    {
        cout<<"Sorry, No more space\n";
    }
    takingActionAfterFunction ();             //Taking next user action
}
//End of addNewItem function

//Start of updatesTore function
void updateStore ()
{
    string itemUpdatedName;                 //Declaring a variable to hold the name of the item to be updated
    int itemUpdatedQuantity;               //Declaring a variable to hold the new quantity of the item to be updated
    float itemUpdatedPrice;               //Declaring a variable to hold the new price of the item to be updated
    short userChoice;                    //Declaring a variable to take choice from the user to whether update the quantity or the price or both  of them
    cout<<"\n\nEnter the item name which you want to update\n\n";
    cout<<"To return to main menu enter \"0\" anywhere\n\n";
    cout<<"Name:";          cin>>itemUpdatedName;
    if(itemUpdatedName=="0")                 //If the user hit 0 go back to the main menu
        {
            system("cls");
            return;
        }
    for(int i=0;i<counter;i++)            //Searching for the item that is gonna be sold
    {
        if(compstring(itemUpdatedName,(*(pointerToItems+i)).name)==true)            //Comparing names
        {
            cout<<"Update :\n"<<"1 Quantity\n"<<"2 Price\n"<<"3 Both of them\n"<<"Choice:";
            cin>>userChoice;                  //getting choice from the user to whether update the quantity or the price or both  of them
            switch(userChoice)
            {
            case 1 :                 //Update the quantity of the item
                {
                    cout<<"New Quantity:";     cin>>itemUpdatedQuantity;
                    if(itemUpdatedQuantity==0)          //If the user hit 0 go back to the main menu
                    {
                        system("cls");
                        return;
                    }
                    while(!cin)                  //Avoiding user's mistakes
                    {
                         cout<<"Sorry, You entered wrong quantity\n";
                         cout<<"Enter again, please\n";
                         cout<<"Quantity:";
                         cin.clear();
                         cin.ignore(256,'\n');
                         cin>>itemUpdatedQuantity;
                   }
                   (*(pointerToItems+i)).quantity=itemUpdatedQuantity;
                }
                break;
            case 2:                //Update the price of the item
                {
                    cout<<"New Price:";     cin>>itemUpdatedPrice;
                    if(itemUpdatedPrice==0)          //If the user hit 0 go back to the main menu
                    {
                        system("cls");
                        return;
                    }
                    while(!cin)                  //Avoiding user's mistakes
                    {
                         cout<<"Sorry, You entered wrong price\n";
                         cout<<"Enter again, please\n";
                         cout<<"Quantity:";
                         cin.clear();
                         cin.ignore(256,'\n');
                         cin>>itemUpdatedPrice;
                   }
                   (*(pointerToItems+i)).price=itemUpdatedPrice;
                }
                break;
            case 3:              //Update both the quantity and price of the item
                {
                    cout<<"New Quantity:";     cin>>itemUpdatedQuantity;
                    if(itemUpdatedQuantity==0)          //If the user hit 0 go back to the main menu
                    {
                        system("cls");
                        return;
                    }
                    while(!cin)                  //Avoiding user's mistakes
                    {
                         cout<<"Sorry, You entered wrong quantity\n";
                         cout<<"Enter again, please\n";
                         cout<<"Quantity:";
                         cin.clear();
                         cin.ignore(256,'\n');
                         cin>>itemUpdatedQuantity;
                   }
                   (*(pointerToItems+i)).quantity=itemUpdatedQuantity;
                    cout<<"New Price:";     cin>>itemUpdatedPrice;
                    if(itemUpdatedPrice==0)          //If the user hit 0 go back to the main menu
                    {
                        system("cls");
                        return;
                    }
                    while(!cin)                  //Avoiding user's mistakes
                    {
                         cout<<"Sorry, You entered wrong price\n";
                         cout<<"Enter again, please\n";
                         cout<<"Quantity:";
                         cin.clear();
                         cin.ignore(256,'\n');
                         cin>>itemUpdatedPrice;
                   }
                   (*(pointerToItems+i)).price=itemUpdatedPrice;
                }
                break;
                default :
                    cout<<"\n\nSorry, You entered a wrong number\n\n";
            }
            cout<<"\n\nUpdated successfully\n\n";
            takingActionAfterFunction ();             //Taking next user action
      }
    }
    cout<<"\n\nItem not found\n\n";
}
//End of updateStore function

//Start of viewItems function
void viewItems ()
{
    if(counter!=0)                                //If the counter is not equal to zero it means that the array has items to be displayed on the screen
    {
        //Making the table
        printLineInTable();
        cout<<verticalBar<<"        Name        "<<verticalBar<<" Quantity "<<verticalBar<<"  Price   "<<verticalBar<<endl;
        for(int i=0;i<counter;i++)
            {
                printLineInTable();
                //Displaying data in the table
                cout<<verticalBar<<setiosflags(ios::left)<<setw(20)<<(*(pointerToItems+i)).name;
                cout<<verticalBar<<setiosflags(ios::left)<<setw(10)<<(*(pointerToItems+i)).quantity;
                cout<<verticalBar<<setiosflags(ios::left)<<setw(10)<<(*(pointerToItems+i)).price<<verticalBar<<endl;
                if(i==counter-1)
                {
                     printLineInTable();
                }
                //Finishing the table}
            }
    }
    else
    {
        cout<<"\n\nNo, items to be viewed\n\n\n";        //If counter equals zero it means that there are no items in the array to be displayed on the screen
    }
    takingActionAfterFunction ();             //Taking next user action
}
//End of viewItems function

//Start of SellItem function
void sellItem ()
{
    if(counter!=0)                       //If counter does not equal zero there are items in the array to be sold
    {
    string itemSoldName;                 //Declaring variable to hold the name of the item that is gonna sold
    int itemSoldQuantity;
    cout<<"\nEnter item data, please\n\n";
    cout<<"To return to main menu enter \"0\" anywhere\n\n";
    cout<<"Name:";          cin>>itemSoldName;
    if(itemSoldName=="0")                 //If the user hit 0 go back to the main menu
        {
            system("cls");
            return;
        }
    for(int i=0;i<counter;i++)            //Searching for the item that is gonna be sold
    {
        if(compstring(itemSoldName,(*(pointerToItems+i)).name)==true)            //Comparing names
        {
            cout<<"Quantity:";      cin>>itemSoldQuantity;
        if(itemSoldQuantity==0)          //If the user hit 0 go back to the main menu
        {
            system("cls");
            return;
        }
            while(!cin)                  //Avoiding user's mistakes
            {
               cout<<"Sorry, You entered wrong quantity\n";
               cout<<"Enter again, please\n";
               cout<<"Quantity:";
               cin.clear();
               cin.ignore(256,'\n');
               cin>>itemSoldQuantity;
            }
            if(itemSoldQuantity<=(*(pointerToItems+i)).quantity)       //Checking for existing quantity and the quantity required
            {
                (*(pointerToItems+i)).quantity-=itemSoldQuantity;     //Updating the quantity after selling
                cout<<"\n\nTotal price : "<<itemSoldQuantity*(*(pointerToItems+i)).price;    //Displaying the total price to the user
                cout<<"\n\nSold successfully\n\n";
                takingActionAfterFunction ();             //Taking next user action
            }
            else
            {
                cout<<"\n\nNo enough Quantity\n\n";
                takingActionAfterFunction ();             //Taking next user action
            }
        }
    }
    cout<<"\n\nItem not found\n\n";
    takingActionAfterFunction ();             //Taking next user action
    }
    else
    {
        cout<<"\n\nThe list is empty, No items to be sold\n\n";         //If the counter is equal to zero, there are no items to be sold
        takingActionAfterFunction ();             //Taking next user action
    }

}
//End of sellItem function

//Start of checkEmptySpace function
void checkEmptySpace ()
{
    if(counter==99)             //If the counter equals to 99 the array is complete
    {
        cout<<"\n\nNo more empty space\n\n";
    }
    else
    {
        cout<<"\n\nYou have "<<counter<<" items in the store";
        cout<<"\n\nAnd You have space for "<<100-counter<<" items\n\n";
    }
    takingActionAfterFunction ();             //Taking next user action
}
//End of checkEmptySpace function

//Start of compstring function
bool compstring (string s1,string s2)
{
    unsigned j=s1.size();               //Comparing the number of characters first
    if(j==s2.size())
    {
        for(unsigned i=0;i<j;i++)
        {
            if(int(s1[i])==int(s2[i])||int(s1[i])==(int(s2[i])-32)||int(s1[i])==(int(s2[i])+32))
                {
                    //Comparing by using asci code of the small and capital letters
                }
            else
                return false;
        }
        return true;
    }
    else
        return false;
}
//End of compstring function

//Start of printLineInTable function
void printLineInTable()
{
    cout<<verticalBar;
    for(int j=0;j<40;j++)
    {
        cout<<hyphenMinus;
        if(j==19||j==29)
            cout<<verticalBar;
    }
    cout<<verticalBar<<endl;
}
//End of printLineInTable function

//Start of getPasswordFromUser function
void getPasswordFromUser ()
{
    int x;                                           //Declaring integer variable to hold what getch() function returns
    char y;                                         //Declaring char variable to hold the letter entered by the user
    for(int i=0;i<10;i++)
    {
        x = getch();                                //Get letter from the user and hide it
        cout<<"*";                                 //display stars instead of letters entered by the user
        y=x;                                      //Convert from asci code to letter itself
        checkPassword[i]=y;                      //Store what the user enters in array of characters
    }
}
//End of getPasswordFromUser function

//Start of getPasswordFromUserAgain function
void getPasswordFromUserAgain (char checkPasswordAgain[])
{
    int x;                                           //Declaring integer variable to hold what getch() function returns
    char y;                                         //Declaring char variable to hold the letter entered by the user
    for(int i=0;i<10;i++)
    {
        x = getch();                                //Get letter from the user and hide it
        cout<<"*";                                 //display stars instead of letters entered by the user
        y=x;                                      //Convert from asci code to letter itself
        checkPasswordAgain[i]=y;                      //Store what the user enters in array of characters
    }
}
//End of getPasswordFromUserAgain function

//Start of testPassword function
bool testPassword (char userPassword[],char exactPassword[])
{
    for(int i=0;i<10;i++)
    {
        if(userPassword[i]==exactPassword[i])
        {
            //Comparing letter after letter
        }
        else
            return false;
    }
    return true;
}
//End of testPassword function

//Start of addSeparateLine function
void addSeparateLine ()
{
    cout<<"\n\n";
    for(int i=0;i<120;i++)
    {
        cout<<"-";
    }
    cout<<"\n\n";
}
//End of addSeparateLine function

//Start of takingActionAfterFunction function
void takingActionAfterFunction ()
{
    addSeparateLine();
    cout<<"What next :-\n\n";
    cout<<"0 Return to main menu\n"<<"1 Save and exit\n\n";
    short lastChoice;
    do
    {
        cout<<"Choice : ";
        cin>>lastChoice;
        while(!cin)                //Avoiding user's mistakes by entering string instead of integer value
        {
            cout<<"Sorry,You entered a wrong choice\n";
            cout<<"Enter again, please\n";
            cout<<"Choice : ";
            cin.clear();
            cin.ignore(256,'\n');
            cin>>lastChoice;
        }
        switch(lastChoice)
        {
        case 0 :
            {
                system("cls");
                userAction();
            }
            break;
        case 1 :
           {
                system ("cls");
                SavingData();
           }
        default :
            cout<<"Sorry,You entered a wrong choice, enter again please\n";
        }
    }
    while(lastChoice!=0&&lastChoice!=1);
}
//End of takingActionAfterFunction function

