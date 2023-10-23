//
// This project is to to build a C++ program to manage the bank accounts associated with UIC Bank v2.0
// This is done via the use of dynamic arrays
// The program interacts with the user to perform banking transactions, and supports the following commands:
// Deposit: + account amount
// Withdrawal: - account amount
// Check balance: ? account
// Find the account with the largest balance: ^
// List all accounts and balances: * low high
// List of accounts with a negative balance: <
// Total of all positive balances in the bank: $
// Add a new account: add
// Delete an existing account: del acct
// Exit: x
//
// Author: Rimsha Rizvi, 4th February 2021, UIC, Spring 2021
// Assignment: Project 02
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std; // using standard c++ library


//
// checkArrays
//
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more
// extensive checks to make sure the data was input correctly.
//
void checkArrays(int accounts[], double balances[], int N)
{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout << "** Checking arrays..." << endl;
    cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
    cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}


//
// search
//
// Given an array of N accounts in ascending order, searches for
// the account that matches "acct". If found, the index of that
// account is returned; if not found -1 is returned.
//
int search( int accounts[], int N, int acct){
    int i;
    for (i=0; i<N; ++i){
        if (accounts[i] == acct){
            return i;
        }
    }
    return -1;   
}


void updateBalance(int updateAcc, double amount, int accounts[], double balances[]){
    
    balances[updateAcc] += amount;
    cout << "Account "<<accounts[updateAcc]<<": balance $" << balances[updateAcc]<<endl;
}


void checkBalance(int i, int accounts[], double balances[])
{
    cout << "Account "<<accounts[i]<<": balance $" << balances[i]<<endl;
}


//
// maxBalance
// Given an array of N balances, searches for the highest balances
// and returns the index of this balance. If there's a tie, the
// first (smaller) index is returned. Assumes N > 0.
//
int maxBalance(double balances[], int N)
{
    int x;
    double max = 0.0;
    for (x=0; x<N; ++x){
        if (balances[x]>max){
            max = balances[x];
        }
    }
    
    int i;
    for (i=0; i<N; ++i){
        if (balances[i] == max){
            return i;
        }
    }
    return 0;
}

   
int main() 
{
    //
    // (1) Input banking filename, confirm file can be opened,
    // and the input N from the first line to set array size:
    //
    
    cout << "** Welcome to UIC Bank v2.0 **" << endl; 
    string filename; 
    cout << "Enter bank filename> " <<endl;
    cin >> filename;
    cout << "** Inputting account data..." << endl;
    
    ifstream infile;
    infile.open(filename);

    if (!infile.good()) 
    {
        cout << "**Error: unable to open input file '" << filename << "'" << endl;
        return 0;
    }
    
    int num;
    double num2;
    
    int N = 0;
    infile >> N;
    
    int* accounts;
    accounts = new int[N];
    
    double* balances;
    balances = new double[N];
    
    int i;
    for (i=0; i<N ; ++i){
        infile >> num;
        accounts[i] = num;
        infile >> num2;
        balances[i] = num2;
    }

    checkArrays(accounts, balances, N);
    
    
    cout << std::fixed; //Output with 2 digits to the right of the decimal point for balance
    cout << std::setprecision(2); // setup for output of the form .xx
    
    
    //
    // (2) Processing interactive commands in order to accept commands from user
    // user enters any number of banking commands until “x” is entered --- the exit command
    //
    
    cout << "** Processing user commands..." << endl;
    
    string command; 
    
    int updateAcc; //'updateAcc' and 'amount' variables are only used for deposit and withdraw
    double amount;
    
    int account; //'account' variable is used for finding a balance of a specific account
    
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " <<endl;
    cin >> command;
    
    while (command != "x"){
        if (command == "+"){
            cin >> updateAcc;
            cin >> amount;
            int i{search(accounts, N, updateAcc)};
            if (i!= -1){   //if return is -1, then this the following function won't proceed
                updateBalance(i, amount, accounts, balances);
            }
            else{
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "-"){
            cin >> updateAcc;
            cin >> amount;
            amount = -amount; //making the amount negative allows you to withdraw money using the same function as deposit
            int i{search(accounts, N, updateAcc)};
            if (i!= -1){
                updateBalance(i, amount, accounts, balances);
            }
            else{
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "?"){
            cin >> account;
            int i{search(accounts, N, account)};
            if (i!= -1){
                checkBalance(i, accounts, balances);
            }
            else{
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if (command == "^"){
            int i{maxBalance(balances, N)};
            cout << "Account "<< accounts[i] <<": balance $"<< balances[i] << endl;
        }
        
        else if (command == "*"){
            int low = 0;
            int high = 0;
            
            cin >> low;
            cin >> high;
            
            int i=0;
            
            for (i=0; i<N; ++i){
                if ((accounts[i]>= low) and (accounts[i]<=high)){
                    cout << "Account "<< accounts[i] <<": balance $"<< balances[i] << endl;
                }
            }
        }
        
        //
        //project 2 part 2
        //
        
        else if (command == "<"){
            int i;
            for (i=0; i<N; ++i){
                if (balances[i]<0.00){
                    cout << "Account "<< accounts[i] <<": balance $"<< balances[i] << endl;
                }
            }
        }
        
        else if (command == "$"){
            int i;
            double total_balances = 0.00;
            for (i=0; i<N; ++i){
                if (balances[i]>=0.00){
                    total_balances += balances[i];
                }
            }
            cout << "Total deposits: $" << total_balances << endl;
        }
        
        else if (command == "add"){
            int* temporary_a;
            double* temporary_b;
            
            temporary_a = new int[N+1];
            temporary_b = new double[N+1];
            
            int i;
            for (i=0; i<N; ++i){
                temporary_a[i] = accounts[i]; //copying the content from original to temporary arrays
                temporary_b[i] = balances[i];
            }
            
            int new_account_number = 0;
            double new_balance = 0.00;
            new_account_number = (accounts[N-1] +1);
            temporary_a[N] = new_account_number;
            temporary_b[N] = new_balance;
            
            cout << "Added account " << temporary_a[N] << ": balance $" << temporary_b[N] << endl;
            
            N += 1;
            
            delete[] accounts;
            accounts = temporary_a;
            
            delete[] balances;
            balances = temporary_b;
        }
        
        else if (command == "del"){
            //int x;
            cin >> account;
            int i{search(accounts, N, account)}; //'accounts' is array containing all accounts, 'account' is the specific account.
            if (i!= -1){
                N = N - 1; 
                for (int j=i; j<N; j++){ //making sure to shift the contents in the right place
                    accounts[j] = accounts[j+1];
                    balances[j] = balances[j+1];
                }
                cout << "Deleted account " << account << endl;
            }

            else{
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        
        else { //ensures that this is within the loop so even if a user enters invalid command, the user is prompted to enter another command
            cout << "** Invalid command, try again..."<<endl; 
         
        }
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl; 
        cin>> command; //in order to repeat the loop with another command to continue transation
    }

        //
        // (3) Writing the account data back out to the same banking file 
        // so the new balances are saved
        //
    
        if (command == "x"){ //if 'x' is entered, it will end the program here
            infile.close(); 
            
            cout <<"** Saving account data..." <<endl;
            ofstream outfile;
            outfile.open(filename);
            
            if (!outfile.good())
            {
                cout << "**Error: unable to open output file '" << filename << "'" << endl;
                delete[] accounts;
                delete[] balances;
                return 0;
            }
            
            outfile << std::fixed;
            outfile << std::setprecision(2);
            
            outfile << N << endl;
            int i;
            for (i=0; i<N ; ++i){
                outfile << accounts[i] << " " << balances [i] << endl;
                }
            outfile.close();
    
            cout <<"** Done **" <<endl;
            
        }
    delete[] accounts;
    delete[] balances;
    return 0; 
}