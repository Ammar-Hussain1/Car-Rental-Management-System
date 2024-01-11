#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <String>
#include <string.h>
#include <fstream>
#include <cmath>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct customer {
	string username;
	string password;
	string username_input;
	string password_input;

	bool login() {
		system("CLS");
		cout << "Enter User Name: ";
		cin >> username_input;
		cout << "Enter Password: ";
		cin >> password_input;
		bool found = false;
		string checking;
		ifstream check_customer_existance;
		check_customer_existance.open("Customer Data\\Customer List.txt");
		int i = 0;
		while (!check_customer_existance.eof()) {
			getline(check_customer_existance, checking);
			if (checking == username_input) {
				found = true;
				break;
			}
			i++;
		}
		if (found == false) {
			return false;
		}
		check_customer_existance.close();

		ifstream read_customer_info;
		read_customer_info.open("Customer Data\\" + username_input + ".txt");
		read_customer_info >> username;
		read_customer_info >> password;
		read_customer_info.close();

		if (username == username_input && password == password_input) {
			return true;
		}
		else {
			return false;
		}
	}

	void view_available_cars() {
		system("CLS");
		string car_model;
		string no_plate;
		string rate_per_hour;
		char status;
		int count = 0;
		int location = -1;

		string trash;

		ifstream counter;
		counter.open("Car Data\\list_of_cars.txt");
		while (getline(counter, trash)) {
			count++;
		}
		counter.close();

		string* list_of_cars = new string[count];

		ifstream read_data_for_cars;
		read_data_for_cars.open("Car Data\\list_of_cars.txt");
		for (int k = 0; k < count; k++) {
			getline(read_data_for_cars, list_of_cars[k]);
		}
		read_data_for_cars.close();

		cout << "\t\t\tLIST OF AVAILABLE CARS WITH DETAILS\n";
		for (int i = 0; i < count; i++) {
			string file_name = list_of_cars[i] + ".txt";
			read_data_for_cars.open("Car Data\\" + file_name);
			getline(read_data_for_cars, car_model);
			getline(read_data_for_cars, no_plate);
			getline(read_data_for_cars, rate_per_hour);
			read_data_for_cars >> status;
			if (status == 'a' || status == 'A') {
				cout << "******************************************************************\n";
				cout << "MODEL : " << car_model << endl;
				cout << "NUMBER PLATE : " << no_plate << endl;
				cout << "RATE PER HOUR : " << rate_per_hour << endl;
				cout << "STATUS : " << "Available" << endl;
				cout << "******************************************************************\n";
			}
			read_data_for_cars.close();
		}
		cout << "Press Enter to Continue!\n";
		char ch;
		ch = _getch();
	}

	int Calculate_price(int rate_per_hour, int sd, int sm, int sy, int ed, int em, int ey) {
		int Total_Amount = 0;
		const int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
		long int dayCount1 = (sy * 365);
		dayCount1 += monthDays[sm];
		dayCount1 += sd;
		long int dayCount2 = (ey * 365);
		dayCount2 += monthDays[em];
		dayCount2 += ed;
		Total_Amount = rate_per_hour * 24 * abs(dayCount1 - dayCount2);

		return Total_Amount;
	}

	void rent_car() {
		system("CLS");
		int sd, sm, sy, ed, em, ey, rate_per_hour, Damage_Count = 0, Rented_count = 0;
		string starting_date;
		string ending_date;
		string starting_time;
		string ending_time;
		string no_plate_input;
		string car_model, no_plate;
		char status;
		bool found = false;
		cout << "\t\t\t\tRent A Car\n";
		view_available_cars();

	not_found:
		cin.ignore();
		cout << "Enter The Number Plate of The Car you want to Rent : ";
		getline(cin, no_plate_input);
		ifstream check_data_of_cars;
		check_data_of_cars.open("Car Data\\list_of_cars.txt");
		while (!check_data_of_cars.eof()) {
			getline(check_data_of_cars, no_plate);
			if (no_plate == no_plate_input) {
				found = true;
				break;
			}
		}
		check_data_of_cars.close();
		if (found == false) {
			cout << "Invalid Input\n";
			goto not_found;
		}
		cout << "Press Enter Key to Continue";
		cin.ignore();
		ifstream read_data_for_cars;
		string file_name = no_plate_input + ".txt";
		read_data_for_cars.open("Car Data\\" + file_name);
		getline(read_data_for_cars, car_model);
		getline(read_data_for_cars, no_plate);
		read_data_for_cars >> rate_per_hour;
		read_data_for_cars >> status;
		read_data_for_cars >> Damage_Count;
		read_data_for_cars >> Rented_count;
		read_data_for_cars.close();
	retry:
		cout << "How long do you want to rent the Car\n";
		cout << "1) Days\n";
		cout << "2) Hours\n";
		cout << "Press 1 to rent it for Days and 2 to rent it for Hours\n";
		int option;
		cin >> option;
		if (option == 1) {
			cout << "\t\t\t\tDAYS\n";
			cin.ignore();
			cout << "When do you want to rent this Car ( Starting Date ) in this format (23 05 2023) ( separate by spaces ) : ";
			cin >> sd;
			cin >> sm;
			cin >> sy;
			cout << "When do you want to rent this Car ( Ending Date ) in this format (23 05 2023) ( separate by spaces ) : ";
			cin >> ed;
			cin >> em;
			cin >> ey;
			int Total_Amount = Calculate_price(rate_per_hour, sd, sm, sy, ed, em, ey);
			cout << "Your total Bill is " << Total_Amount << " PKR\n";
			ofstream write_customer_data_list;
			write_customer_data_list.open("Customer Record\\list_of_customers.txt", ios::app);
			write_customer_data_list << username << endl;
			write_customer_data_list.close();

			ofstream write_customer_record;
			write_customer_record.open("Customer Record\\" + username + ".txt", ios::app);
			write_customer_record << no_plate_input << endl;
			write_customer_record << sd << " " << sm << " " << sy << endl;
			write_customer_record << ed << " " << em << " " << ey << endl;
			write_customer_record << Total_Amount << endl;
			write_customer_record.close();
			Sleep(3000);
			ofstream write_data_for_cars;
			string file_name = no_plate_input + ".txt";
			write_data_for_cars.open("Car Data\\" + file_name);
			write_data_for_cars << car_model << endl;
			write_data_for_cars << no_plate << endl;
			write_data_for_cars << rate_per_hour << endl;
			write_data_for_cars << 'r' << endl;
			write_data_for_cars << Damage_Count << endl;
			write_data_for_cars << ++Rented_count;
			write_data_for_cars.close();
			char ch;
			cout << "Press Enter To Continue:";
			ch = _getch();
		}
		else if (option == 2) {
			int sh, sm, eh, em;
			int total_price;
			cout << "\t\t\t\tHOURS\n";
			cin.ignore();
			cout << "When do you want to rent this Car ( Starting Time ) in 24 hours format (15 30) ( separate by spaces ) : ";
			cin >> sh;
			cin >> sm;
			cout << "When do you want to rent this Car ( Ending Time ) in 24 hours format (16 30) ( separate by spaces ) : ";
			cin >> eh;
			cin >> em;
			total_price = (eh - sh) * rate_per_hour + float(em - sm) * float(rate_per_hour / 60.0);
			cout << "Your total Bill is " << total_price << " PKR\n";
			ofstream write_customer_data_list;
			write_customer_data_list.open("Customer Record\\list_of_customers.txt", ios::app);
			write_customer_data_list << username;
			write_customer_data_list.close();

			ofstream write_customer_record;
			write_customer_record.open("Customer Record\\" + username + ".txt", ios::app);
			write_customer_record << no_plate_input << endl;
			write_customer_record << sh << " " << sm << endl;
			write_customer_record << eh << " " << em << endl;
			write_customer_record << total_price << endl;
			write_customer_record.close();

			ofstream write_data_for_cars;
			string file_name = no_plate_input + ".txt";
			write_data_for_cars.open("Car Data\\" + file_name);
			write_data_for_cars << car_model << endl;
			write_data_for_cars << no_plate << endl;
			write_data_for_cars << rate_per_hour << endl;
			write_data_for_cars << 'r' << endl;
			write_data_for_cars << Damage_Count << endl;
			write_data_for_cars << ++Rented_count;
			write_data_for_cars.close();

			char ch;
			cout << "Press Enter To Continue!";
			ch = _getch();
		}
		else {
			cout << "Invalid Input";
			Sleep(2000);
			goto retry;
		}
	}

	void return_car() {
		string no_plate_input, Total_Amount, starting, ending, car_model, no_plate, rate_per_hour;
		char status;
		bool found = false;
		int DamageCount = 0, Rented_count = 0;
		system("CLS");
		cout << "\t\t\t\tRETURN A CAR\n";
		cout << "You have Rented Following Cars From the Dealership\n";
		ifstream read_customer_record, runner;
		ifstream read_car_details;
		string line;
		read_customer_record.open("Customer Record\\" + username + ".txt");
		runner.open("Customer Record\\" + username + ".txt");
		while (getline(runner, line))
		{
			for (int i = 0; i < 3; i++)
			{
				getline(runner, line);
			}
			getline(read_customer_record, no_plate_input);
			getline(read_customer_record, starting);
			getline(read_customer_record, ending);
			getline(read_customer_record, Total_Amount);

			read_car_details.open("Car Data\\" + no_plate_input + ".txt");
			getline(read_car_details, car_model);
			getline(read_car_details, no_plate);
			getline(read_car_details, rate_per_hour);
			read_car_details >> status;
			read_car_details >> DamageCount;
			read_car_details >> Rented_count;
			if (status == 'r' || status == 'R') {
				cout << "******************************************************************\n";
				cout << "MODEL : " << car_model << endl;
				cout << "NUMBER PLATE : " << no_plate << endl;
				cout << "RATE PER HOUR : " << rate_per_hour << endl;
				cout << "Your Bill is :" << Total_Amount << endl;
				cout << "******************************************************************\n";
			}
			read_car_details.close();
		}
		runner.close();

		read_customer_record.close();
		cout << "Press Enter key to continue!\n";
		not_found:
		cin.ignore();
		cout << "Enter the Number Plate of the Car you want to return: ";
		getline(cin, no_plate_input);
		ifstream check_data_of_cars;
		check_data_of_cars.open("Car Data\\list_of_cars.txt");
		while (!check_data_of_cars.eof()) {
			getline(check_data_of_cars, no_plate);
			if (no_plate == no_plate_input) {
				found = true;
				break;
			}
		}
		check_data_of_cars.close();
		if (found == false) {
			cout << "Invalid Input\n";
			goto not_found;
		}
		char choice;
		cout << "Was car got Damaged?(Y/N): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			DamageCount++;
		}
		cout << "You have Successfully Returned the Car\n";

		ofstream write_data_for_cars;
		string file_name = no_plate_input + ".txt";
		write_data_for_cars.open("Car Data\\" + file_name);
		write_data_for_cars << car_model << endl;
		write_data_for_cars << no_plate << endl;
		write_data_for_cars << rate_per_hour << endl;
		write_data_for_cars << 'a' << endl;
		write_data_for_cars << DamageCount << endl;
		write_data_for_cars << Rented_count;
		write_data_for_cars.close();
		char ch;
		cout << "Press any key to continue";
		ch = _getch();
	}

	void rental_report() {
		cout << "\t\t\t\tRENTAL REPORT\n";
		string no_plate, starting, ending, total_cost, rate_per_hour, model, line;
		char status;
		ifstream read_data_for_report, runner;
		runner.open("Customer Record\\" + username + ".txt");
		read_data_for_report.open("Customer Record\\" + username + ".txt");
		while (getline(runner, line)) {
			for (int i = 0; i < 3; i++)
			{
				getline(runner, line);
			}
			getline(read_data_for_report, no_plate);
			getline(read_data_for_report, starting);
			getline(read_data_for_report, ending);
			getline(read_data_for_report, total_cost);


			ifstream read_car_details;
			read_car_details.open("Car Data\\" + no_plate + ".txt");

			getline(read_car_details, model);
			getline(read_car_details, no_plate);
			getline(read_car_details, rate_per_hour);
			read_car_details >> status;
			cout << "*******************************************\n";
			cout << "MODEL : " << model << endl;
			cout << "NUMBER PLATE : " << no_plate << endl;
			if (status == 'r' || status == 'R') {
				cout << "STATUS : STILL RENTED" << endl;
			}
			else {
				cout << "STATUS : RETURNED" << endl;
			}
			cout << "RATE PER HOUR : " << rate_per_hour << endl;
			cout << "RENTED FROM : " << starting << endl;
			cout << "TILL : " << ending << endl;
			cout << "TOTAL COST : " << total_cost << endl;
			cout << "*******************************************\n";

			read_car_details.close();
		}
		read_data_for_report.close();
		runner.close();
		char ch;
		cout << "PRESS ENTER KEY TO CONTINUE!";
		ch = _getch();
	}

	void dashboard() {
		while (1) {
		label:
			system("CLS");
			cout << "\t\t\t\t\tDASHBOARD\n";
			cout << "1) Rent a Car\n";
			cout << "2) Return a Rented Car\n";
			cout << "3) View Available Cars\n";
			cout << "4) Generate Rental Reports\n";
			cout << "5) Quit\n";
			cout << "Enter the option you want to use:";
			int option;
			cin >> option;
			if (option == 1) {
				rent_car();
			}
			else if (option == 2) {
				return_car();
			}
			else if (option == 3) {
				view_available_cars();
			}
			else if (option == 4) {
				rental_report();
			}
			else if (option == 5) {
				break;
			}
			else {
				cout << "Invalid Input";
				Sleep(2000);
				goto label;
			}
		}
	}
};

struct admin {
	string username;
	string password;
	string username_input;
	string password_input;
	int num_of_customers = 0;

	bool login() {
		ifstream read_admin_info;
		read_admin_info.open("admin.txt");
		read_admin_info >> username;
		read_admin_info >> password;
		read_admin_info.close();
		cout << "Enter User Name: ";
		cin >> username_input;
		cout << "Enter Password: ";
		cin >> password_input;
		if (username == username_input && password == password_input) {
			return true;
		}
		else {
			return false;
		}
	}

	void change_password() {
	retry:
		system("CLS");
		cout << "Enter Old Password: ";
		cin >> password_input;
		if (password == password_input) {
			cout << "Enter New Password:";
			cin >> password;
			ofstream write_admin_info;
			write_admin_info.open("admin.txt");
			write_admin_info << username << endl;
			write_admin_info << password;
			write_admin_info.close();
		}
		else {
			cout << "Incorrect Password\n";
		wrong:
			cout << "Do you want to retry (Y/N):";
			char option;
			cin >> option;
			if (option == 'y' || option == 'Y') {
				goto retry;
			}
			else if (option == 'n' || option == 'N') {
				return;
			}
			else {
				goto wrong;
			}
		}
	}

	void view_cars() {
		string car_model;
		string no_plate;
		string rate_per_hour;
		char status;
		int count = 0;
		int location = -1;
		string trash;

		ifstream counter;
		counter.open("Car Data\\list_of_cars.txt");
		while (getline(counter, trash)) {
			count++;
		}
		counter.close();
		
		string * list_of_cars = new string[count];
		
		ifstream read_data_for_cars;
		read_data_for_cars.open("Car Data\\list_of_cars.txt");
		for (int k = 0; k < count; k++) {
			getline(read_data_for_cars, list_of_cars[k]);
		}
		read_data_for_cars.close();
		cout << "\t\t\t\tLIST OF CARS WITH DETAILS\n";
		for (int i = 0; i < count; i++) {
			string file_name = list_of_cars[i] + ".txt";
			read_data_for_cars.open("Car Data\\" + file_name);
			if (read_data_for_cars.is_open())
			{
				cout << "******************************************************************\n";
				getline(read_data_for_cars, car_model);
				getline(read_data_for_cars, no_plate);
				getline(read_data_for_cars, rate_per_hour);
				read_data_for_cars >> status;
				cout << "MODEL : " << car_model << endl;
				cout << "NUMBER PLATE : " << no_plate << endl;
				cout << "RATE PER HOUR : " << rate_per_hour << " pkr" << endl;
				if (status == 'r' || status == 'R') {
					cout << "STATUS : " << "Rented" << endl;
				}
				else {
					cout << "STATUS : " << "Available" << endl;
				}
				read_data_for_cars.close();
				cout << "******************************************************************\n";
			}
		}
		delete[] list_of_cars;
		cout << "Press Enter to Continue!";
		char ch;
		ch = _getch();
	}

	void view_customers() {
		string username;
		string password;
		string address;
		string phone_number;
		int count = 0;
		int location = -1;
		string trash;
		ifstream counter;
		counter.open("Customer Data\\Customer List.txt");
		while (getline(counter, trash)) {
			count++;
		}
		
		counter.close();
		
		int j = 0;
		string* list_of_customers = new string[count];
		
		ifstream read_data_for_customers1;
		read_data_for_customers1.open("Customer Data\\Customer List.txt");
		for (int k = 0; k < count; k++) {
			getline(read_data_for_customers1, list_of_customers[k]);
		}
		read_data_for_customers1.close();
		cout << "\t\t\t\tLIST OF CUSTOMERS WITH DETAILS\n";
		for (int i = 0; i < count; i++) {
			string file_name = list_of_customers[i] + ".txt";
			ifstream read_data_for_customers;
			read_data_for_customers.open("Customer Data\\" + file_name);
			if (read_data_for_customers.is_open())
			{
				cout << "******************************************************************\n";
				getline(read_data_for_customers, username);
				getline(read_data_for_customers, password);
				getline(read_data_for_customers, address);
				getline(read_data_for_customers, phone_number);
				cout << "User Name : " << username << endl;
				cout << "Password : " << password << endl;
				cout << "Address : " << address << endl;
				cout << "Phone Number : " << phone_number << endl;
				read_data_for_customers.close();
				cout << "******************************************************************\n";
			}
			else
			{
				continue;
			}
		}
		delete[] list_of_customers;
		cout << "Press Enter to Continue!";
		char ch;
		ch = _getch();
	}

	void view_cars_customers() {
	retry:
		system("CLS");
		cout << "\t\t\t\tView current registered cars and customers\n";
		cout << "1) Registered Cars" << endl;
		cout << "2) Registered Customers" << endl;
		cout << "What do you want to see:";
		int option;
		cin >> option;
		if (option == 1) {
			view_cars();
		}
		else if (option == 2) {
			view_customers();
		}
		else {
			cout << "Invalid Input";
			goto retry;
		}
	}

	
	void add_customer() {
		system("CLS");
		cout << "\t\t\t\t\tADD CUSTOMER\n";
		string customer_name, password, address, phone_number;
		cout << "Enter Customer Name:";
		cin.ignore();
		getline(cin, customer_name);
		string file_name;
		file_name = customer_name + ".txt";
		ofstream add_customer("Customer Data\\" + file_name);
		cout << "Press Enter to Continue!";
		cin.ignore();
		cout << "Enter the the Password for the CUSTOMER:";
		getline(cin, password);
		cout << "Press Enter to Continue!";
		cin.ignore();
		cout << "Enter the proper ADDRESS of customer:";
		getline(cin, address);
		cout << "Press Enter to Continue!";
		cin.ignore();
		cout << "Enter PHONE NUMBER of Customer:";
		getline(cin, phone_number);
		add_customer << customer_name << endl;
		add_customer << password << endl;
		add_customer << address << endl;
		add_customer << phone_number;
		ofstream write_CL;
		write_CL.open("Customer Data\\Customer List.txt", ios::app);
		write_CL << customer_name << endl;
		write_CL.close();
		add_customer.close();
	}

	void Remove_Customer() {
		int CN;
		char arr[20];
		string filename = "Customer Data\\";
		
		num_of_customers = 0;
		string trash;
		ifstream counter("Customer Data\\Customer List.txt");
		while (getline(counter, trash))
		{
			ifstream check;
			string file_name = trash + ".txt";
			check.open("Customer Data\\" + file_name);
			if (check.is_open())
				num_of_customers++;
		}
		counter.close();
		string* Customer_List = new string[num_of_customers];

		ifstream read_CL("Customer Data\\Customer List.txt");
		for (int i = 0; i < num_of_customers; i++)
		{
			read_CL >> Customer_List[i];
		}
		read_CL.close();


		for (int i = 0, j = 1; i < num_of_customers; i++)
		{
			if (Customer_List[i] != " ")
			{
				cout << j++ << ") " << Customer_List[i] << endl;
			}
		}

		cout << "Enter the Customer Number you want to DELETE:";
		cin >> CN;

		if (CN < 1 || CN > num_of_customers) {
			cout << "Invalid Customer Number\n";
			return;
		}

		strcpy(arr, Customer_List[CN - 1].c_str());

		for (int i = 0; arr[i] != '\0'; i++) {
			if (isupper(arr[i])) {
				arr[i] = tolower(arr[i]);
			}
			filename += arr[i];
		}

		filename += ".txt";
		remove(filename.c_str());
		for (int i = CN - 1; i < num_of_customers-1; i++)
		{
			Customer_List[i] = Customer_List[i + 1];
		}
		num_of_customers--;
		
		ofstream write_CL("Customer Data\\Customer List.txt");
		for (int i = 0; i < num_of_customers; i++)
		{
			write_CL << Customer_List[i] << endl;
		}
		write_CL.close();

		cout << "\nCustomer Deleted Successfully!\n";
		delete[] Customer_List;
		Sleep(2000);
	}

	void add_remove_customer() {
		system("CLS");
	again:
		cout << "\t\t\t\t\tADD AND REMOVE CUSTOMER\n";
		int option;
		cout << "1) Add Customer\n";
		cout << "2) Remove Customer\n";
		cout << "Enter 1 to ADD CUSTOMER or 2 to REMOVE CUSTOMER:";
		cin >> option;
		if (option == 1)
		{
			add_customer();
			cout << "\nNew Customer Added Successfuly!\n";
			Sleep(2000);
		}
		else if (option == 2)
		{
			Remove_Customer();
		}
		else
		{
			system("CLS");
			goto again;
		}
	}

	void Update_Customer_data() {
		int CN;
		char arr[20];
		string filename = "Customer Data\\";
		
		num_of_customers = 0;
		string trash;
		ifstream counter("Customer Data\\Customer List.txt");
		while (getline(counter, trash))
		{
			ifstream check;
			string file_name = trash + ".txt";
			check.open("Customer Data\\" + file_name);
			if (check.is_open())
				num_of_customers++;
		}
		counter.close();
		string* Customer_List = new string[num_of_customers];

		ifstream read_CL("Customer Data\\Customer List.txt");
		for (int i = 0; i < num_of_customers; i++)
		{
			read_CL >> Customer_List[i];
		}
		read_CL.close();


		for (int i = 0, j = 1; i < num_of_customers; i++)
		{
			if (Customer_List[i] != " ")
			{
				cout << j++ << ") " << Customer_List[i] << endl;
			}
		}
		cout << "Enter the Customer Number you want to UPDATE:";
		cin >> CN;
		strcpy(arr, Customer_List[CN - 1].c_str());
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (isupper(arr[i]))
			{
				arr[i] = tolower(arr[i]);

			}
			filename += arr[i];
		}
		filename += ".txt";
		ifstream read_C_D(filename);
		string Data[4];
		int info = 0;
		for (int i = 0; i < 4; i++)
		{
			getline(read_C_D, Data[i]);
		}
		system("CLS");
	top:
		cout << "1) Customer Password\n2) Customer Address\n3) Customer Phone Number\nWhich detail you want to edit:";
		cin >> info;
		if (info == 1)
		{
			cin.ignore();
			cout << "Enter new Passowrd:";

			getline(cin, Data[1]);
		}
		else if (info == 2)
		{
			cin.ignore();
			cout << "Enter new Address:";

			getline(cin, Data[2]);
		}
		else if (info == 3)
		{
			cin.ignore();
			cout << "Enter new Phone Number:";

			getline(cin, Data[3]);
		}
		else
		{
			cout << "Invalid Input\n";
			goto top;
		}
		ofstream write_C_D(filename);
		for (int i = 0; i < 4; i++)
		{
			write_C_D << Data[i] << endl;
		}
		cout << "\nCustomer Data Updated Successfuly!\n";
		delete[] Customer_List;
		Sleep(2000);
	}

	void remove_car() {
		string car_model;
		string no_plate;
		string no_plate_input;
		string rate_per_hour;
		char status;
		int count = 0;
		int location = -1;


		string trash;

		ifstream counter;
		counter.open("Car Data\\list_of_cars.txt");
		while (getline(counter, trash)) {
			count++;
		}
		counter.close();

		string* list_of_cars = new string[count];

		ifstream read_data_for_cars;
		read_data_for_cars.open("Car Data\\list_of_cars.txt");
		for (int k = 0; k < count; k++) {
			getline(read_data_for_cars, list_of_cars[k]);
		}
		read_data_for_cars.close();

		cout << "\t\t\t\tLIST OF CARS WITH DETAILS\n";
		for (int i = 0; i < count; i++) {
			string file_name = list_of_cars[i] + ".txt";
			read_data_for_cars.open("Car Data\\" + file_name);
			if (read_data_for_cars.is_open())
			{
				cout << "******************************************************************\n";
				getline(read_data_for_cars, car_model);
				getline(read_data_for_cars, no_plate);
				getline(read_data_for_cars, rate_per_hour);
				read_data_for_cars >> status;
				cout << "MODEL : " << car_model << endl;
				cout << "NUMBER PLATE : " << no_plate << endl;
				cout << "RATE PER HOUR IN PKR : " << rate_per_hour << endl;
				if (status == 'r' || status == 'R') {
					cout << "STATUS : " << "Rented" << endl;
				}
				else {
					cout << "STATUS : " << "Available" << endl;
				}
				read_data_for_cars.close();
				cout << "******************************************************************\n";
			}
		}
	retry:
		cin.ignore();
		cout << "Enter the Number Plate of the car which you want to remove:";
		getline(cin, no_plate_input);
		for (int i = 0; i < count; i++) {
			if (list_of_cars[i] == no_plate_input) {
				location = i;
				break;
			}
		}
		if (location == -1) {
			cout << "NOT FOUND!!!" << endl;
			goto retry;
		}

		string file_name = "Car Data\\" + list_of_cars[location] + ".txt";
		if (remove(file_name.c_str()) == 0) {
			cout << list_of_cars[location] << " has been removed";
		}

		for (int i = location; i < count - 1; i++) {
			list_of_cars[i] = list_of_cars[i + 1];
		}
		ofstream write_data_for_cars;
		write_data_for_cars.open("Car Data\\list_of_cars.txt", ios::out);
		for (int i = 0; i < count - 1; i++) {
			write_data_for_cars << list_of_cars[i] << endl;
		}
		write_data_for_cars.close();

		delete[] list_of_cars;

	}

	void add_car() {
		string car_model;
		string no_plate;
		string rate_per_hour;
		char status;
		cin.ignore();
		cout << "Enter Model of the Car:";
		getline(cin, car_model);
		cout << "Press Enter to Continue:";
		cin.ignore();
		cout << "Enter the Number Plate of the Car:";
		getline(cin, no_plate);
		cout << "Press Enter to Continue:";
		cin.ignore();
		cout << "Enter the Rate Per Hour of the Car:";
		getline(cin, rate_per_hour);
		cout << "Press Enter to Continue:";
		cin.ignore();
		cout << "Enter Status of the Car ( \"R\" for Rental and \"A\" for Available ) : ";
		while (1) {
			cin >> status;
			if (status == 'R' || status == 'r' || status == 'A' || status == 'a') {
				break;
			}
			cout << "Enter Status of the Car ( \"R\" for Rental and \"A\" for Available ) : ";
		}
		string file_name;
		file_name = no_plate + ".txt";
		ofstream add_car("Car Data\\" + file_name);
		add_car << car_model << endl;
		add_car << no_plate << endl;
		add_car << rate_per_hour << endl;
		add_car << status << endl;
		add_car << 0 << endl;
		add_car << 0;
		add_car.close();

		ofstream write_data_for_cars_list;
		write_data_for_cars_list.open("Car Data\\list_of_cars.txt", ios::app);
		write_data_for_cars_list << no_plate << endl;
		write_data_for_cars_list.close();

		cout << car_model << " has been added.";
		Sleep(2000);
	}

	void add_remove_car() {
	retry:
		system("CLS");
		cout << "\t\t\t\tADD OR REMOVE CARS\n";
		cout << "1) Add Car\n";
		cout << "2) Remove Car\n";
		cout << "ENTER 1 to ADD Car and ENTER 2 to REMOVE Car: ";
		int option;
		cin >> option;
		if (option == 1) {
			add_car();
		}
		else if (option == 2) {
			remove_car();
		}
		else {
			cout << "Invalid Input";
			Sleep(2000);
			goto retry;
		}
	}

	void customer_reports() {
		system("CLS");
		string Customer_username;
		int Total_money_spent = 0;
		
		num_of_customers = 0;
		string trash;
		ifstream counter("Customer Data\\Customer List.txt");
		while (getline(counter, trash))
		{
			ifstream check;
			string file_name = trash + ".txt";
			check.open("Customer Data\\" + file_name);
			if (check.is_open())
				num_of_customers++;
		}
		counter.close();
		string* Customer_List = new string[num_of_customers];

		ifstream read_CL("Customer Data\\Customer List.txt");
		for (int i = 0; i < num_of_customers; i++)
		{
			read_CL >> Customer_List[i];
		}
		read_CL.close();

		for (int i = 0, j = 1; i < num_of_customers; i++)
		{
			if (Customer_List[i] != " ")
			{
				cout << j++ << ") " << Customer_List[i] << endl;
			}
		}

		cout << "Enter the username of CUSTOMER you want to get record of:";
		cin.ignore();
		getline(cin, Customer_username);
		ifstream Customer_Rec;
		Customer_Rec.open("Customer Record\\" + Customer_username + ".txt");
		if (!Customer_Rec.is_open())
		{
			cout << "No record Found!\n";
			char ch;
			cout << "Press any Key to Continue!\n";
			ch = _getch();
		}
		else
		{
			string no_plate, starting, ending, Total_cost, trash;
			ifstream runner;
			runner.open("Customer Record\\" + Customer_username + ".txt");
			while (getline(runner, trash))
			{
				for (int i = 0; i < 3; i++)
				{
					getline(runner, trash);
				}
				getline(Customer_Rec, no_plate);
				getline(Customer_Rec, starting);
				getline(Customer_Rec, ending);
				getline(Customer_Rec, Total_cost);
				Total_money_spent += stoi(Total_cost);
				cout << "***********************************************************\n";
				cout << "Number Plate is: " << no_plate << endl;
				cout << "Strting Date is: " << starting << endl;
				cout << "Ending Booking is: " << ending << endl;
				cout << "Total Bill is: " << Total_cost << endl;
				cout << "***********************************************************\n";
			}
			cout << "Total Money Spent By this Customer is: " << Total_money_spent << endl;
			runner.close();
			Customer_Rec.close();
			char ch;
			cout << "Press any Key to Continue!\n";
			ch = _getch();
		}
		delete[] Customer_List;
	}

	void car_report() {
		system("CLS");
		string no_plate_input;
		string car_model, no_plate, rate_per_hour;
		char status;
		int Damage_Count = 0, Rented_count = 0;
		int count = 0;
		int location = -1;

		ifstream read_data_for_cars;
		string trash;
		ifstream counter("Car Data\\list_of_cars.txt");
		ifstream read_CD("Car Data\\list_of_cars.txt");
		while (getline(counter, trash))
		{
			ifstream check;
			string file_name = trash + ".txt";
			check.open("Car Data\\" + file_name);
			if (check.is_open())
				count++;
		}
		counter.close();

		string * list_of_cars = new string[count];

		for (int i = 0; i < count; i++)
		{
			getline(read_CD, list_of_cars[i]);
		}

		read_CD.close();
		cout << "\t\t\tLIST OF CARS WITH DETAILS\n";
		for (int i = 0; i < count; i++) {
			cout << i + 1 << ") " << list_of_cars[i] << endl;
		}
	retry:
		int choice;
		cout << "Enter the number of car whose Report you want:";
		cin >> choice;
		if (choice > count)
		{
			goto retry;
		}
		string file_name = list_of_cars[choice - 1] + ".txt";
		read_data_for_cars.open("Car Data\\" + file_name);
		getline(read_data_for_cars, car_model);
		getline(read_data_for_cars, no_plate);
		getline(read_data_for_cars, rate_per_hour);
		read_data_for_cars >> status;
		read_data_for_cars >> Damage_Count;
		read_data_for_cars >> Rented_count;
		cout << "******************************************************************\n";
		cout << "MODEL : " << car_model << endl;
		cout << "NUMBER PLATE : " << no_plate << endl;
		cout << "RATE PER HOUR : " << rate_per_hour << endl;
		cout << "STATUS : " << "Available" << endl;
		cout << "Car was Damaged/Repaired " << Damage_Count << " times." << endl;
		cout << "Car was Rented " << Rented_count << " times." << endl;
		cout << "******************************************************************\n";
		read_data_for_cars.close();

		delete[] list_of_cars;

		char ch;
		cout << "Press any Key to Contiue!\n";
		ch = _getch();

	}

	void check_reports() {
	retry:
		system("CLS");
		cout << "\t\tReports of Customers and Cars\n";
		cout << "1) Customer Reports\n";
		cout << "2) Cars Reports\n";
		cout << "Enter 1 for Customer Reports and 2 for Car Reports : ";
		int option;
		cin >> option;
		if (option == 1) {
			customer_reports();
		}
		else if (option == 2) {
			car_report();
		}
		else {
			cout << "Invalid Input";
			Sleep(2000);
			goto retry;
		}
	}

	void dashboard() {
		while (1) {
		label:
			system("CLS");
			cout << "\t\t\t\t\tDASHBOARD\n";
			cout << "1) Change Password\n";
			cout << "2) View Current Registered Cars and Customers\n";
			cout << "3) Add and Remove Customers\n";
			cout << "4) Update Customer Data\n";
			cout << "5) Add and Remove Car\n";
			cout << "6) Check Reports Related to Customers and Cars\n";
			cout << "7) Quit\n";
			cout << "Enter the option you want to use:";
			int option;
			cin >> option;
			if (option == 1) {
				change_password();
			}
			else if (option == 2) {
				view_cars_customers();
			}
			else if (option == 3) {
				add_remove_customer();
			}
			else if (option == 4) {
				Update_Customer_data();
			}
			else if (option == 5) {
				add_remove_car();
			}
			else if (option == 6) {
				check_reports();
			}
			else if (option == 7) {
				break;
			}
			else {
				cout << "Invalid Input";
				Sleep(2000);
				goto label;
			}
		}
	}
};

int main() {
label:
	admin admin1;
	customer customer1;
	cout << "1) ADMIN\n";
	cout << "2) CUSTOMER\n";
	cout << "ENTER 1 to LOGIN as ADMIN and ENTER 2 to LOGIN as CUSTOMER:";
	int option;
	cin >> option;
	system("CLS");
	if (option == 1) {
	retry:
		cout << "\t\t\t\t\tADMIN\n";
		if (admin1.login()) {
			admin1.dashboard();
		}
		else {
			cout << "Incorrect Username Or Password";
			Sleep(2000);
			system("CLS");
			goto retry;
		}

	}
	else if (option == 2) {
	retry1:
		cout << "\t\t\t\t\tADMIN\n";
		if (customer1.login()) {
			cout << "YOu are in";
			customer1.dashboard();
		}
		else {
			cout << "Incorrect Username Or Password";
			Sleep(2000);
			system("CLS");
			goto retry1;
		}
	}
	else {
		cout << "Invalid Input";
		system("CLS");
		goto label;
	}
	return 0;
}