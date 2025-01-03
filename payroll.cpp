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
protected:
    int id;
    string name;
    double hourlyRate;
    double hoursWorked;
    string type;
    string level;

public:
    Employee(int empId, string empName, double rate, double hours, string empType, string empLevel)
    {
        id=empId;
        name=empName;
        hourlyRate=rate;
        hoursWorked=hours;
        type=empType;
        level=empLevel;
    }

    Employee(){
     id=0;
     name="";
     hourlyRate=0.0;
     hoursWorked=0.0;
     type="";
     level="";
    }

    virtual ~Employee() {}

    int getId()const{
         return id;
    }
    string getName()const{
        return name;
    }
   // string getType() const { return type; }
    //string getLevel() const { return level; }
    void setHourlyRate(double rate){
        hourlyRate = rate;
    }
    double getHourlyRate()const{
        return hourlyRate;
    }

    void setHoursWorked(double hours){
        hoursWorked = hours;
    }
    double getHoursWorked()const{
        return hoursWorked;
    }

    void setType(const string& type){
        this->type=type;
    }
    string getType()const{
        return type;
    }

    void setLevel(const string& level) {
        this->level=level;
    }
    string getLevel() const {
        return level;
    }
    virtual double calculateSalary() const {
        return hourlyRate * hoursWorked;
    }

    virtual void displayDetails() const {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }

    virtual string toFileString() const {
        stringstream ss;
        ss << id << "," << name << "," << hourlyRate << "," << hoursWorked << "," << type << "," << level;
        return ss.str();
    }

    static Employee* fromFileString(const string &line) {
        stringstream ss(line);
        string token;
        int id;
        string name, type, level;
        double rate, hours;
        getline(ss, token, ',');
        id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ',');
        rate = stod(token);
        getline(ss, token, ',');
        hours = stod(token);
        getline(ss, type, ',');
        getline(ss, level);

        return new Employee(id, name, rate, hours, type, level);
    }
};


class FullTimeEmployee : public Employee {
public:
    FullTimeEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Full-Time", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked * 1.1;
    }
};


class PartTimeEmployee : public Employee {
public:
    PartTimeEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Part-Time", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked;
    }
};


class InternEmployee : public Employee {
public:
    InternEmployee(int empId, string empName, double rate, double hours, string empLevel)
        : Employee(empId, empName, rate, hours, "Intern", empLevel) {}

       virtual double calculateSalary() const override {

        return hourlyRate * hoursWorked * 0.5;
    }
};


class EntryLevel : public Employee {
public:
    EntryLevel(int empId, string empName, double rate, double hours, string empType)
        : Employee(empId, empName, rate, hours, empType, "Entry-Level") {}

    virtual double calculateSalary() const override {
        return Employee::calculateSalary();
    }

    virtual void displayDetails() const override {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }
};


class SeniorLevel : public Employee {
public:
    SeniorLevel(int empId, string empName, double rate, double hours, string empType)
        : Employee(empId, empName, rate, hours, empType, "Senior-Level") {}

    virtual double calculateSalary() const override {
        return hourlyRate * hoursWorked + 1000;
    }

    virtual void displayDetails() const override {
        cout << left << setw(10) << id << setw(20) << name
             << setw(15) << hourlyRate << setw(15) << hoursWorked
             << setw(15) << calculateSalary() << setw(15) << type << setw(15) << level << endl;
    }
};

class PayrollSystem {
private:
    vector<Employee*> employees;

    void saveToFile() {
        ofstream outFile("employees.txt");
        for (const auto& emp : employees) {
            outFile << emp->toFileString() << endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("employees.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                Employee* emp = Employee::fromFileString(line);
                if (emp) {
                    employees.push_back(emp);
                }
            }
            inFile.close();
        }
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


