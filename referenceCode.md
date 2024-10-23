#include <iostream>
#include <fstream>
#include <string>

void writeMemberToFile(const std::string& name, const std::string& membershipID, 
                       const std::string& phoneNumber, const std::string& email) {
    std::ofstream outFile("members.csv", std::ios::app);
    
    if (outFile.is_open()) {
        outFile << name << "," << membershipID << "," << phoneNumber << "," << email << "\n";
        outFile.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

void registerMember(const std::string& name, const std::string& membershipID, 
                    const std::string& phoneNumber, const std::string& email) {
    writeMemberToFile(name, membershipID, phoneNumber, email);
}

void viewAllMembers() {
    std::ifstream inFile("members.csv");
    std::string line;

    // Check if the file is open
    if (inFile.is_open()) {
        std::cout << "Member Details:\n";
        std::cout << "-----------------------------------------\n";
        
        // Read each line and display
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }

        inFile.close(); // Close the file
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }
}

int main() {
    std::string name, membershipID, phoneNumber, email;
    int choice;

    while (true) {
        std::cout << "1. Register Member\n2. View All Members\n3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            // Get user input for member registration
            std::cout << "Enter member name: ";
            std::getline(std::cin, name);
            std::cout << "Enter membership ID: ";
            std::getline(std::cin, membershipID);
            std::cout << "Enter phone number: ";
            std::getline(std::cin, phoneNumber);
            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            // Register the member
            registerMember(name, membershipID, phoneNumber, email);
            std::cout << "Member details added successfully.\n";
        } else if (choice == 2) {
            // View all members
            viewAllMembers();
        } else if (choice == 3) {
            break; // Exit the loop
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
