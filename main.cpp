// C++ program to show difference between
// definition and declaration of a 
// variable
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void write_csv(const string& filename, const vector<vector<string>>& data) {
    ofstream file(filename,ios::app);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}

void write_csv_header(const string& filename) {
    ofstream file(filename);  // This will overwrite the file
    file << "Name,Passcode\n";
}


void admin(){
    cout << "\tEnter Your Name: \n\t";

    string Name;
    cin >> Name;

    string Passcode;
    cout << "\tEnter Your passcode: \n\t";
    cin >> Passcode;

    string strName = "Anthony";
    string strPasscode = "00000000";

    // if (Name==strName){
    //     cout << "Your name is " << Name << " and Passcode is " << Passcode;
    // }else
    // {
    //     cout << "Wrong staff nigga";
    // }
    
    //added Header manually - make it automatic
    vector<vector<string>> data = {
        {Name, Passcode},
    };
    write_csv("admin.csv", data);

    cout << "Added to csv db";
    
}

class Staff {
    public:
    void libraryStaffMenu(){
        cout << "\tCreate Library User\n";
        createLibraryUser();
    }

    private:
    void createLibraryUser(){
        cout << "\tEnter a suitable username\n\t";
        string username;
        cin >> username;

        cout << "\tEnter a valid password\n\t";
        string password;
        cin >> password;

        cout << "Your password is " << password << " and your username is " << username;

        vector<vector<string>> data = {
            {username, password},
        };
        write_csv("LibraryStaff.csv", data);
    }
}; 

int main(){
    char text[] = "Welcome";

    cout << "Library Management system\n";

    cout << text << " - Choose Your preferred option: \n";

    cout << "\t1.Admin\n\t2.Library Staff\n\t3.Library Member\n\t4.Exit\n\t";

    int option;

    cin >> option;

    switch(option)
    {
        case 1:
            admin();
            break;
        case 2:
            Staff staffobj;
            staffobj.libraryStaffMenu();
            break;
        case 3:
            cout << "\tYou are in Members section";
            break;
        case 4:
            cout << "\tYou chose Exit";
            break;
    }

    return 0;
}
