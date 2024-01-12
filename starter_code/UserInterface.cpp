#include <iostream>
#include <stdexcept>
#include <exception>

// #include "my_debugger.h"
#include "Database.h"


const string Logger::msDebugFileName = "debugfile.txt";


using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);

Database makeNewDatabase();

int main()
{
    log("started");

	Database employeeDB;
    string dbFileName = "saved_db.csv";

	bool done = false;
	while (!done) {
		int selection = displayMenu();
		switch (selection) {
		case 0:
            log("case 0");
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
        case 7:
			employeeDB = makeNewDatabase();
			break;
        case 8:
			employeeDB.saveToFile(dbFileName);
			break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Make new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database form file" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
}

void doHire(Database& db)
{
    log("start");
    string firstName;
    string lastName;

    cout << "First name? ";
    cin >> firstName;
    cout << "Last name? ";
    cin >> lastName;
    
    db.addEmployee(firstName, lastName);
    log("end");
}

void doFire(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
}

Database makeNewDatabase()
{
    log("start");
    vector<string> arrFirst {
        "first1", "Ann", "Bob", "first2", "Cathy" 
        "first3", "Ann2", "Bob2", "first10", "Cathy2"
        "first4", "Ann3", "Bob3", "first11", "Cathy3"
        "first5", "Ann4", "Bob4", "first12", "Cathy4"
    };

    vector<string> arrMiddle {
        "middle1", "Don", "Bob", "first2", "Cathy" 
        "middle3", "Don2", "Bob2", "first10", "Cathy2"
        "middle4", "Don3", "Bob3", "first11", "Cathy3"
        "middle5", "Don4", "Bob4", "first12", "Cathy4"
    };

    vector<string> arrLast {
        "last1", "Smith", "Smith2", "last2", "last3" 

    };

    Database db;
    int count = 0;
    for (const string& firstName: arrFirst) {
        for (const string& middleName: arrMiddle) {
            for (const string& lastName: arrLast) {

                // random streetNumber,
                // string
                count++;
                string countStr = to_string(count);
                Employee& empl = db.addEmployee(
                    firstName, middleName, lastName);
                string address = countStr + " street#" + countStr;
                empl.setAddress(address);
            }
        }
    }
    log("end");
    return db;
}
