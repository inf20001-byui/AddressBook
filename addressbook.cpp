// Christopher Infante
// CSE 310 - Winter 2023

// This program is an Adress Book where you can add, delete, and display contacts.

// include input/output stream library
#include <iostream>

// include file stream library
#include <fstream>

// include string library (needed for transform function)
#include <bits/stdc++.h>

// include the stl vector library
#include <vector>

// include the string library
#include <string>

// include the standard library
#include <stdlib.h>

using namespace std;

fstream datahandler; // file pointer for Filestream Library  

// define global variables
string firstName;
string lastName;
string phoneNumber;
string email;
string notes;

// define the structure of the contact class

class contact {
    public:
          
    // creates a new contact
    void createNewContact()
    {
        cout << "Enter the first name: " ;
        cin >> firstName;
        cout << "Enter the last name: " ;
        cin.ignore();
        cin >> lastName;
        cout << "Enter the phone number: ";
        cin.ignore();
        cin >> phoneNumber;
        cout << "Enter the email: " ;
        cin.ignore();
        cin >> email;
        cout << "Enter the notes: " ;
        cin.ignore();
        getline(cin, notes);

        cout << "\n";
    }

    // displays the contact to the screen
    void printContact()
    {
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Email: " << email << endl;
        cout << "Notes: " << notes << endl;
    }

    string getPhone()
    {
        return phoneNumber;
    }
    
    string getName()
    {
        return firstName;
    }

    string getEmail()
    {
        return email;
    }   

    string getNotes()
    {
        return notes;
    }  
};

contact cont; // contact object to reference the contact class

// create a new contact and write it to a file
void saveContact()
{
    datahandler.open("addressbook.txt", ios::out|ios::app); // open the file in append mode
    cont.createNewContact(); // call to -> create a new contact
    string address = firstName + "," + lastName + "," + phoneNumber + "," + email + "," + notes + "\n";
    datahandler.write(address.data(), address.size()); // writes the contact to the file
    cout << address << endl;
    datahandler.close(); // close the file

    cout << endl <<"Contact has been added to the Addressbook" << endl;
}

// display all entries in the address book
void displayAll()
{
   system("cls"); // clear the screen

   cout << "    Displaying all contacts" << endl;
   cout << "--------------------------------" << endl;
   datahandler.open("addressbook.txt", ios::in); // open the file in read-only mode
   vector<string> *g1; // create a vector of strings
    g1 = new vector<string>[200]; 
    if (datahandler.is_open()) // check if the file is open
    {
        string str; // string to store the line entries

        // read the file line by line and store the line in the vector
        while (getline(datahandler, str)){ 
           stringstream linestream(str);
           getline(linestream, firstName, ',');
           getline(linestream, lastName, ',');
           getline(linestream, phoneNumber, ',');
           getline(linestream, email, ',');
           getline(linestream, notes, ',');  

           g1 -> push_back(str); // push the line into the vector
           cont.printContact();
           cout << "--------------------------------" << endl;
           
        }
    datahandler.close(); // close the file
    }
    // Print the vector - Used for testing only (Comment out when not testing)
    //cout << "\nVector elements are: ";
    //for (auto it = g1->begin(); it != g1->end(); it++)
    //    cout << *it << " ";
}


// Update a contact in the Addressbook
void editContact()
{
    string name; // string to store the name of the contact
    bool exists = false; // boolean to check if the contact exists
    string fileContent; // string to store the file content

    cout << "Enter the first name of the contact you want to edit: ";
    cin >> name;
    
    datahandler.open("addressbook.txt", ios::in|ios::in); // open the file in read mode
    if (datahandler.is_open()) // check if the file is open
    {
        string str; // string to store the line entries

        // read the file line by line until the end of the file using commas as delimiters
        while (getline(datahandler, str))
        { 
           stringstream linestream(str);
           getline(linestream, firstName, ',');
           getline(linestream, lastName, ',');
           getline(linestream, phoneNumber, ',');
           getline(linestream, email, ',');
           getline(linestream, notes, ',');  
    
            if(name == firstName) // if the name entered matches the name of a contact
            {
                cont.printContact(); // print the contact
                cout << "--------------------------------" << endl;
                cout << endl;
                
                cont.createNewContact(); // create a new contact
                string address = firstName + "," + lastName + "," + phoneNumber + "," + email + "," + notes + "\n";                
                fileContent += address; // add the new contact to the fileContent string

                /*int pos = -1 * sizeof(cont); // get the position of the contact
                datahandler.seekp(pos, ios::cur); // move the pointer to the position of the contact
                
                datahandler.write(address.data(), address.size()); // write the contact to the file
                cout << address << " has been updated at " << pos << endl;*/

                cout << "Contact has been updated in the Addressbook" << endl;
                exists = true;
            }
            else // if the name entered does not match the name of a contact
            {
                fileContent += str + "\n"; // add the line to the fileContent string
            }
        }
    datahandler.close(); // close the file 
    }
    if (exists == false) // if the contact does not exist
    {
        cout << endl << "Contact does not exist int the Addressbook" << endl;
        getchar();
    }
    else // if the contact exists
    {
        ofstream outFile("addressbook.txt"); // open the file in write mode
        outFile << fileContent; // write the fileContent string to the file
        outFile.close(); // close the file
    }
}

// Delete a contact from the Addressbook
void deleteContact()
{
    string name;
    bool exists = false;

    cout << endl << "Enter the first name of the contact you want to delete: ";
    cin >> name;

    datahandler.open("addressbook.txt", ios::in|ios::out); // open the file in read and write mode
    fstream tempFile; // create a temporary file
    tempFile.open("tempfile.txt", ios::out); // open the temporary file in write mode
    datahandler.seekg(0, ios::beg); // move the pointer to the beginning of the file
    
    string str; // string to store the line entries
    while (getline(datahandler, str)) // read the file record by record using commas as delimiters
        {
        stringstream linestream(str);
        getline(linestream, firstName, ',');
        getline(linestream, lastName, ',');
        getline(linestream, phoneNumber, ',');
        getline(linestream, email, ',');
        getline(linestream, notes, ',');

        if(name == cont.getName()) // if the name matches the name of the contact
        {
            cont.printContact(); // print the contact and show that it has been deleted
            cout << "--------------------------------" << endl;
            cout << endl;
            cout << "Contact deleted from Addressbook!" << endl;
            exists = true;
        }
        else // if the name does not match the name of the contact
        {
            // write the contact to the temporary file if it doesn't match the name entered
            string address = firstName + "," + lastName + "," + phoneNumber + "," + email + "," + notes + "\n";
            tempFile.write(address.data(), address.size()); // write the contact to the temporary file    
        }
    }
    datahandler.close(); // close the file
    tempFile.close(); // close the temporary file

    remove("addressbook.txt"); // remove the original file

    ifstream f1("tempfile.txt",ios::binary); // open the temporary file in read mode
    ofstream f2("addressbook.txt",ios::binary); // open the original file in write mode
    f2 << f1.rdbuf(); // copy the contents of the temporary file to the original file

    f1.close(); // close the temporary file
    f2.close(); // close the original file

    remove("tempfile.txt"); // remove the temporary file

    if (exists == false) // if the contact does not exist
    {
        cout << "Contact does not exist int the Addressbook" << endl;
    }
}

// Main processing section

int main(int argc, char *argv[]) 
{
    for(;;) // infinite loop to display the menu
    {
        int choice;
        cout << "Welcome to Chris' Addressbook" << endl;
        cout << "-----------------------------" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Display all contacts" << endl;
        cout << "3. Edit a contact" << endl;
        cout << "4. Delete a contact" << endl;
        cout << "5. Exit the Addressbook" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                saveContact();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                return 0;
                break;
            default:
                cout << "Invalid choice, please try again" << endl;
                break;
        }

        int option; // variable to store the user's choice
        cout << "Do you want to continue? (1 = Yes, 2 = No): ";
        cin >> option;
        system("cls");

        switch(option) // switch statement to continue or exit the program
        {
        case 1:
            continue;
        case 2:
            cout << endl << "Thank you for using Chris' Addressbook" << endl << endl;
            return 0;
            break;
        default:
            cout << "Invalid choice, Exiting the program!" << endl;
            return 0;
            break;
            
                
        }   
    }
    return 0;
}

