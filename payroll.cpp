#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <windows.h>
using namespace std;


class Login {
private:
    string LoginID,Password;
public:
    Login(){
        LoginID="";
        Password="";
    }

    void setID(string id)
    {
        LoginID = id;
    }

    void setPW(string pw)
    {
        Password = pw;
    }

    string getID()
    {
        return LoginID;
    }

    string getPW()
    {
        return Password;
    }
};

void registration(Login &log)
 {
    system("cls");
    string id,pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;
    log.setID(id);

start:
    cout<<"\tEnter A Strong Password (min 8 chars): ";
    cin>>pw;
    if(pw.length()>=8)
    {
        log.setPW(pw);
    }
    else
    {
        cout<<"\tEnter Minimum 8 Characters!" <<endl;
        goto start;
    }
    ofstream outfile("Login.txt", ios::app);
    if (!outfile)
    {
        cout<<"\tError: File Can't Open!"<<endl;
    }
    else
    {
        outfile<<id<<":"<<pw<<endl;
        cout<<"\tUser Registered Successfully!"<<endl;
    }
    outfile.close();
    Sleep(2000);
}

bool login()
 {
    system("cls");
    string id, pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;

    cout <<"\tEnter Password: ";
    cin>>pw;

    ifstream infile("Login.txt");
    if (!infile)
    {
        cout<<"\tError: File Can't Open!"<<endl;
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string userID,userPW;
        getline(ss,userID,':');
        getline(ss,userPW);

        if (id==userID&&pw==userPW)
        {
            cout<<"\tLogin Successful! Welcome "<<id<<"!"<<endl;
            infile.close();
            Sleep(2000);
            return true;
        }
    }

    cout <<"\tError: Incorrect Login ID or Password!"<<endl;
    infile.close();
    Sleep(2000);
    return false;
 }

class Employee {
private:
    int id;
    string name;
    double hourlyRate;
    double hoursWorked;

public:
    Employee(int empId,string empName,double rate,double hours)
    {
        id=empId;
        name=empName;
        hourlyRate=rate;
        hoursWorked=hours;
    }

    Employee(){
      id=0;
      name="";
      hourlyRate=0.0;
      hoursWorked=0.0;
    }

    int getId() const {
         return id;
    }
    string getName() const {
        return name;
    }
    double getHourlyRate() const {
         return hourlyRate;
    }
    double getHoursWorked() const {
         return hoursWorked;
    }

    void setId(int newId)
     {
         id = newId;
     }
    void setName(const string &newName)
     {
         name = newName;
     }
    void setHourlyRate(double newRate)
     {
         hourlyRate = newRate;
     }
    void setHoursWorked(double newHours)
     {
         hoursWorked = newHours;
     }

    double calculateSalary() const {
        return hourlyRate * hoursWorked;
    }

    void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << endl;
    }

    string toFileString() const {
        stringstream ss;
        ss << id << "," << name << "," << hourlyRate << "," << hoursWorked;
        return ss.str();
    }

    static Employee fromFileString(const string &line) {
        Employee emp;
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        emp.id = stoi(token);
        getline(ss, emp.name, ',');
        getline(ss, token, ',');
        emp.hourlyRate = stod(token);
        getline(ss, token, ',');
        emp.hoursWorked = stod(token);

        return emp;
    }
};

class PayrollSystem {
private:
    vector<Employee> employees;
    const string employeeFile = "Employees.txt";

    void saveToFile() {
        ofstream outfile(employeeFile, ios::trunc);
        if (!outfile)
        {
            cout <<"Error: Unable to open file for saving employee data!"<<endl;
            return;
        }
        for (const auto &emp:employees)
        {
            outfile<<emp.toFileString()<<endl;
        }
        outfile.close();
    }

    void loadFromFile()
    {
        ifstream infile(employeeFile);
        if (!infile)
        {
            cout<<"No employee data found. Starting fresh!"<<endl;
            return;
        }
        string line;
        while (getline(infile, line))
        {
            employees.push_back(Employee::fromFileString(line));
        }
        infile.close();
    }

    int findEmployeeIndex(int id)
     {
        for (size_t i=0;i<employees.size();i++)
        {
            if (employees[i].getId()==id)
            {
                return i;
            }
        }
        return -1;
    }

public:
    PayrollSystem() {
        loadFromFile();
    }

    void addEmployee(int id, string name, double hourlyRate, double hoursWorked)
    {
        if (findEmployeeIndex(id)!=-1) {
            cout <<"Employee with ID "<<id<<" already exists.\n";
            return;
        }
        employees.emplace_back(id,name,hourlyRate,hoursWorked);
        saveToFile();
        cout <<"Employee added successfully!\n";
    }

    void displayPayroll()
    {
        if (employees.empty())
        {
            cout<<"No employees found.\n";
            return;
        }
        cout <<left<<setw(10)<<"ID"<<setw(20)<<"Name"
             <<setw(15)<<"Hourly Rate"<<setw(15)<<"Hours Worked"
             <<setw(15)<<"Salary"<<endl;
        cout<<string(75,'-')<<endl;

        for (const auto &emp:employees)
        {
            emp.displayDetails();
        }
    }

    void updateEmployee(int id, string newName, double newRate, double newHours)
    {
        int index = findEmployeeIndex(id);
        if (index == -1)
        {
            cout << "Employee with ID " << id << " not found.\n";
            return;
        }
        employees[index].setName(newName);
        employees[index].setHourlyRate(newRate);
        employees[index].setHoursWorked(newHours);
        saveToFile();
        cout<<"Employee updated successfully!\n";
    }

    void deleteEmployee(int id)
    {
        int index = findEmployeeIndex(id);
        if (index==-1) {
            cout<<"Employee with ID "<<id<< " not found.\n";
            return;
        }
        employees.erase(employees.begin()+index);
        saveToFile();
        cout<<"Employee deleted successfully!\n";
    }
};


int main() {
    Login log;
    PayrollSystem payroll;
    bool loggedIn=false;

    while (!loggedIn)
    {
        system("cls");
        int choice;
        cout<<"Welcome to the System\n";
        cout<<"1. Register\n";
        cout<<"2. Login\n";
        cout<<"3. Exit\n";
        cout<<"Enter choice: ";
        cin>> choice;

        if (choice==1)
        {
            registration(log);
        }
        else if (choice == 2)
        {
            loggedIn = login();
        }
        else if (choice == 3)
        {
            cout << "Exiting...\n";
            return 0;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }


    int option;
    do {
        system("cls");
        cout<<"\nPayroll System Menu:\n";
        cout<<"1. Add Employee\n";
        cout<<"2. Display All Employees\n";
        cout<<"3. Update Employee\n";
        cout<<"4. Delete Employee\n";
        cout<<"5. Logout\n";
        cout<<"Enter your choice: ";
        cin>> option;

        switch (option)
        {
            case 1: {
                int id;
                string name;
                double hourlyRate,hoursWorked;
                cout<<"Enter ID: ";
                cin>>id;
                cin.ignore();
                cout<<"Enter Name: ";
                getline(cin, name);
                cout<<"Enter Hourly Rate: ";
                cin>>hourlyRate;
                cout<<"Enter Hours Worked: ";
                cin>>hoursWorked;
                payroll.addEmployee(id,name,hourlyRate,hoursWorked);
                break;
            }
            case 2:
                payroll.displayPayroll();
                break;
            case 3: {
                int id;
                string newName;
                double newRate,newHours;
                cout<<"Enter Employee ID to Update: ";
                cin>>id;
                cin.ignore();
                cout<<"Enter New Name: ";
                getline(cin,newName);
                cout<<"Enter New Hourly Rate: ";
                cin>>newRate;
                cout<<"Enter New Hours Worked: ";
                cin>>newHours;
                payroll.updateEmployee(id, newName, newRate, newHours);
                break;
            }
            case 4: {
                int id;
                cout<<"Enter Employee ID to Delete: ";
                cin>>id;
                payroll.deleteEmployee(id);
                break;
            }
            case 5:
                loggedIn=false;
                break;
            default:
                cout<<"Invalid choice! Try again.\n";
        }
        system("pause");
    }
    while (option != 5);

}


