#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


using namespace std;

int main(void)
{
	cout << endl;
	cout << "Let's have MySQL count from 10 to 1..." << endl;

	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *result;
	sql::PreparedStatement *add;
	sql::PreparedStatement *read;
	sql::PreparedStatement  *delet;
	sql::PreparedStatement *update;
	sql::PreparedStatement *pupdate;
	try
	{

		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "Gaur!@!985");

	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("np1");
	cout << "Connected to the Mysql database" << endl;

	int choice;
	string cname, cmodel;
	int cyear, cprice;
	do
	{
		//options to choose
		cout << "Pleas choose your option!" << endl;
		cout << "1. Add new data" << endl;
		cout << "2. Read the data" << endl;
		cout << "3. Delete a car" << endl;
		cout << "4. Update information (Price)" << endl;
		cout << "5. Update price with 10% increase (Price)" << endl;
		cout << "6. Update price with 20% reduction (Price)" << endl;
		cout << "0. Exit" << endl;
		cout << "Choose: ";
		cin >> choice;
		system("CLS");
		if (choice == 1)
		{
			//Add to the database using INSERT
			cout << "Which car: ";
			cin >> cname;
			cout << "Which model: ";
			cin >> cmodel;
			cout << "Which year: ";
			cin >> cyear;
			cout << "What is the price: ";
			cin >> cprice;
			add = con->prepareStatement("INSERT INTO bilar(brand, model, year, price) VALUES(?,?,?,?)");
			add->setString(1, cname);
			add->setString(2, cmodel);
			add->setInt(3, cyear);
			add->setInt(4, cprice);
			add->executeUpdate();
			cout << "Information has been saved." << endl;

			//delete pstmt;
			//delete con;
			system("pause");
			system("CLS");
		}
		if (choice == 2)
		{
			// Read the database using SELECT
			read = con->prepareStatement("SELECT * FROM bilar;");
			result = read->executeQuery();

			while (result->next())
				printf("Reading from table=(%d, %s,, %s, %d, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getString(3).c_str(), result->getInt(4), result->getInt(5));

			//delete result;
			//delete read;
			//delete con;
			system("pause");
			system("CLS");
		}
		if (choice == 3)
		{
			//Delete from database using DELETE
			string deletecar;
			cout << "Which car do you want to remove: ";
			cin >> deletecar;

			//delete
			delet = con->prepareStatement("DELETE FROM bilar WHERE brand = ?");
			delet->setString(1, deletecar);
			result = delet->executeQuery();
			printf("The car is removed from database!\n");

			system("pause");
			system("CLS");
		}
		if (choice == 4)
		{
			//Update the database
			string updatecar;
			int newprice;
			cout << "Which car do you want to change price for: ";
			cin >> updatecar;
			cout << "What is the new price: ";
			cin >> newprice;

			//update
			update = con->prepareStatement("UPDATE bilar SET pris = ? WHERE brand = ?");
			update->setInt(1, newprice);
			update->setString(2, updatecar);
			update->executeQuery();
			printf("The new price of the car is now updated!\n");

			system("pause");
			system("CLS");
		}
		if (choice == 5)
		{
			//update
			pupdate = con->prepareStatement("UPDATE bilar SET price = price * 1.1 WHERE id !='0'");
			result = pupdate->executeQuery();

			delete pupdate;
			system("pause");
			system("CLS");
		}
	
		if (choice == 5)
		{
			//update
			pupdate = con->prepareStatement("UPDATE bilar SET price = price * 0.8 WHERE id !='0'");
			result = pupdate->executeQuery();

			delete pupdate;
			system("pause");
			system("CLS");
		}
		
		else
		{
			cout << "Wrong choice !\n" << endl;
		}
		

	} while (choice != 0);


	system("pause");
	return 0;
}