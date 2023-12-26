#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
class Hotel {
private:
    int room_no;
    char name[30];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

void Hotel::main_menu() {
    int choice;
    while (true) {
        std::system("clear"); // For Linux/Mac, use "cls" for Windows
        std::cout << "\n\t\t\t*************";
        std::cout << "\n\t\t\t* MAIN MENU *";
        std::cout << "\n\t\t\t*************";
        std::cout << "\n\n\n\t\t\t1. Book A Room";
        std::cout << "\n\t\t\t2. Customer Record";
        std::cout << "\n\t\t\t3. Rooms Allotted";
        std::cout << "\n\t\t\t4. Edit Record";
        std::cout << "\n\t\t\t5. Exit";
        std::cout << "\n\n\t\t\tEnter Your Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: exit(0);
            default: std::cout << "\n\n\t\t\tWrong choice.....!!!";
        }
    }
}

void Hotel::add() {
    int r, flag;
    std::ofstream fout("Record.dat", std::ios::app | std::ios::binary);

    std::cout << "\n Enter Customer Details";
    std::cout << "\n ----------------------";
    std::cout << "\n\n Room no: ";
    std::cin >> r;
    flag = check(r);

    if (flag) {
        std::cout << "\n Sorry..!!! Room is already booked please book another room";
    } else {
        room_no = r;
        std::cout << " Name: ";
        std::cin.ignore(); // Consume newline character left in the buffer
        std::cin.getline(name, sizeof(name));
        std::cout << " Address: ";
        std::cin.getline(address, sizeof(address));
        std::cout << " Phone No: ";
        std::cin.getline(phone, sizeof(phone));
        std::cout << " No of Days to Checkout: ";
        std::cin >> days;
        fare = days * 900.0; // 900 is the default price per day
        fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        std::cout << "\n Dear "<<name<<" Room no "<< room_no<<" is booked...!!!";
    }

    std::cout << "\n Press any key to continue.....!!";
    std::cin.ignore(); // Consume newline character left in the buffer
    std::cin.get();
    fout.close();
}

void Hotel::display() {
    int r, flag = 0;
    std::ifstream fin("Record.dat", std::ios::binary);

    std::cout << "\n Enter room no: ";
    std::cin >> r;

    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            std::cout << "\n Customer Details";
            std::cout << "\n ----------------";
            std::cout << "\n\n Room no: " << room_no;
            std::cout << "\n Name: " << name;
            std::cout << "\n Address: " << address;
            std::cout << "\n Phone no: " << phone;
            std::cout << "\n Days: " << days;
            std::cout << "\n Total Fare: " << fare;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        std::cout << "\n Sorry Room no. not found or vacant....!!";
    }

    std::cout << "\n\n Press any key to continue....!!";
    std::cin.ignore(); // Consume newline character left in the buffer
    std::cin.get();
    fin.close();
}

void Hotel::rooms() {
    std::ifstream fin("Record.dat", std::ios::binary);

    std::cout << "\n\t\t\t    List Of Rooms Allotted";
    std::cout << "\n\t\t\t    ----------------------";

    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        std::cout << "\n Room no: " << room_no << "\n Name: " << name;
        std::cout << "\n Address: " << address << "\n Phone: " << phone;
        std::cout << "\n Days: " << days << "\n Total: " << fare;
        std::cout << "\n**********************************";
    }

    std::cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    std::cin.ignore(); // Consume newline character left in the buffer
    std::cin.get();
    fin.close();
}

void Hotel::edit() {
    int choice, r;

    std::cout << "\n EDIT MENU";
    std::cout << "\n ---------";
    std::cout << "\n\n 1. Modify Customer Record";
    std::cout << "\n 2. Delete Customer Record";
    std::cout << "\n Enter your choice: ";
    std::cin >> choice;

    std::cout << "\n Enter room no: ";
    std::cin >> r;

    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        default: std::cout << "\n Wrong Choice.....!!";
    }

    std::cout << "\n Press any key to continue....!!!";
    std::cin.ignore(); // Consume newline character left in the buffer
    std::cin.get();
}

int Hotel::check(int r) {
    int flag = 0;
    std::ifstream fin("Record.dat", std::ios::binary);

    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }

    fin.close();
    return flag;
}

void Hotel::modify(int r) {
    std::fstream file("Record.dat", std::ios::in | std::ios::out | std::ios::binary);

    while (file.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            std::cout << "\n Enter New Details";
            std::cout << "\n -----------------";
            std::cout << "\n Name: ";
            std::cin.ignore(); // Consume newline character left in the buffer
            std::cin.getline(name, sizeof(name));
            std::cout << " Address: ";
            std::cin.getline(address, sizeof(address));
            std::cout << " Phone no: ";
            std::cin.getline(phone, sizeof(phone));
            std::cout << " Days: ";
            std::cin >> days;
            fare = days * 900.0;

            file.seekg(-static_cast<int>(sizeof(Hotel)), std::ios::cur);
            file.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            std::cout << "\n Record is modified....!!";
            break;
        }
    }

    file.close();
}

void Hotel::delete_rec(int r) {
    std::ifstream fin("Record.dat", std::ios::binary);
    std::ofstream fout("temp.dat", std::ios::binary | std::ios::app);

    char ch;
    while (fin.read(reinterpret_cast<char*>(this), sizeof(Hotel))) {
        if (room_no == r) {
            std::cout << "\n Name: " << name;
            std::cout << "\n Address: " << address;
            std::cout << "\n Phone No: " << phone;
            std::cout << "\n Days: " << days;
            std::cout << "\n Total Fare: " << fare;
            std::cout << "\n\n Do you want to delete this record (y/n): ";
            std::cin >> ch;

            if (ch == 'n') {
                fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
            }
            break;
        } else {
            fout.write(reinterpret_cast<char*>(this), sizeof(Hotel));
        }
    }

    fin.close();
    fout.close();

    remove("Record.dat");
    rename("temp.dat", "Record.dat");
}

void intro(){
	std::cout<<"\n\n\t            ";
	std::cout<<"     C++ Project On Hotel Management System";
	std::cout<<"\n\n\t\t\t\t     MADE BY";
	std::cout<<"\n\n°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	std::cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n\n";
	std::cout<<"\t\t\t\tMuhammad Numan     \n";
	std::cout<<"\t\t\t\t FA22-BCS-033   \n\n";
	std::cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
	std::cout<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°";
}
int main() {
    Hotel h;
    intro();
    std::cout << "\n\n\n\t\t\tPress any key to continue....!!";
    std::cin.ignore(); // Consume newline character left in the buffer
    std::cin.get();
    std::system("clear"); // For Linux/Mac, use "cls" for Windows
    h.main_menu();

    return 0;
}