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

int main(){


}


