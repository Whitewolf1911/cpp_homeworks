/*

Ali Ihsan Basoglu
1306200089
Date : 03/06/2021
Development Environment: Visual Studio 2019

Notes : This is the best algorithm i could do . 
In Schedule.txt  "ScheduleTime" variable doesnt show you starting time of that operation . Instead it will show the ending time of that operation. 
For example, if you see 17; 3; 2; 100; 10  >> "17" means that operation ended in T=17 . I think this is better solution for seeing the ending time of all operations.
Except that everything is same format as its instructed in homework pdf.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

vector<string> split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

struct MACHINE {
	
	vector <pair<int,int> > process;
	vector <tuple<int, int, int>> setupDuration;

};

class Schedule {
public:
	int time;
	int opCode;
	int order_num;
	int amountWork;
	int setup_overhead;

	Schedule(int t, int op, int ord, int amo, int set) {
		time = t;
		opCode = op;
		order_num = ord;
		amountWork = amo;
		setup_overhead = set;
	}
};

class Orders {

public:
	int orderNo;
	int orderAmount;
	int opCode;
	int expireDate;
    
	Orders(int orNo, int orAm, int opCo, int exDate) {

		orderNo = orNo;
		orderAmount = orAm;
		opCode = opCo;
		expireDate = exDate;
	}

	int get_orderNo() {
		return orderNo;
	}
	int get_orderAmount() {
		return orderAmount;
	}
	int get_opCode() {
		return opCode;
	}
    int get_expire() {
		return expireDate;
	}

};

MACHINE machine; // our machine
vector <Orders> orders; 
vector <Schedule> CompleteSchedule;
ofstream OutFile;

int main() {
	
	// init operations.txt
	fstream newfile;
	newfile.open("Operations.txt", ios::in);												// dosyayi acma
	if (newfile.is_open()) {													//dosya acik mi ? 
		string line;
		while (getline(newfile, line)) {										// satir satir oku
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // bosluklari sil														
			int op_speed=0;
			int op_code=0;
			vector <string> v = split(line, ';');
			op_code = stoi(v[0]);
			op_speed = stoi(v[1]);

			machine.process.push_back(make_pair(op_code, op_speed));
			
		}
		newfile.close();
	}
	// end of init operations.txt

	// init setupdurations.txt 
	newfile.open("SetupDuration.txt", ios::in);											
	if (newfile.is_open()) {													
		string line;
		while (getline(newfile, line)) {										
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); 																	
			int cur_op = 0;
			int next_op = 0;
			int switch_time = 0;

			vector <string> v = split(line, ';');
			cur_op = stoi(v[0]);
			next_op = stoi(v[1]);
			switch_time = stoi(v[2]);
	
			machine.setupDuration.push_back(make_tuple(cur_op, next_op, switch_time));
			machine.setupDuration.push_back(make_tuple(next_op, cur_op, switch_time));

		}
		newfile.close();
	}
	// end of init setupduration.txt


	//init orders.txt
	newfile.open("Orders.txt", ios::in);												
	if (newfile.is_open()) {													
		string line;
		while (getline(newfile, line)) {									
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			int orderNo = 0;
			int orderAmount = 0;
			int process_code = 0;
			int expire_date = 0;

			vector <string> v = split(line, ';');
			
			orderNo = stoi(v[0]);
			orderAmount = stoi(v[1]);
			process_code = stoi(v[2]);
			expire_date = stoi(v[3]);
			
			Orders order(orderNo, orderAmount , process_code , expire_date);
			orders.push_back(order);

			}
		}
	// end of init orders.txt
	
	
	// Sort our orders by expire priority
	sort(orders.begin(), orders.end(), []( Orders lhs,  Orders rhs) {
		return lhs.get_expire() < rhs.get_expire();
		});
	
	//sorting orders by op code

	int first_index = 0;
	int last_index = 0;
	bool flag = false;
	for (int x = 1; x < orders.size(); x++) {
		
		if (orders[x].get_expire() != orders[x - 1].get_expire()) {
			
			
			last_index = x;
			flag = true;
		}
		else {
			flag = false;
			
		}

		if (x + 1 == orders.size()) {

			last_index = x;
			flag = true;
		}

		if (flag) {

			sort(orders.begin() + first_index, orders.begin() + last_index, [](Orders lhs, Orders rhs) {
				return lhs.get_opCode() < rhs.get_opCode();
				});
			first_index = last_index;
		}
	}
	// end of sorting orders by op code 

	//Schedule calculation
	int scheduleTime = 0;

	for (int x = 0; x < orders.size(); x++) {
		
		int processSpeed=0;
		int processCode = 0;
		int setupOverhead = 0;
		int amountOfWork = 0;
		int orderCode = orders[x].get_orderNo();
		int nextOpCode = 0;
		int timeNeeded = 0;


		amountOfWork = orders[x].get_orderAmount();

		for (int y = 0; y < machine.process.size(); y++) {

			if (orders[x].get_opCode() == machine.process[y].first) {
				processSpeed = machine.process[y].second; // got the processSpeed
				processCode = machine.process[y].first;  // got the processCode
			}
		}
		
		timeNeeded = round((float)orders[x].get_orderAmount() / (float)processSpeed); // got the time for processing 
		
		if (x  < orders.size()) {
			if (x != 0) {
				int beforeOp = 0;
				int currentOp = 0;
				currentOp = orders[x].get_opCode();
				beforeOp = orders[x - 1].get_opCode();
				for (int z = 0; z < machine.setupDuration.size(); z++) {
				
					int firstOp = get<0>(machine.setupDuration[z]);
					int secondOp = get<1>(machine.setupDuration[z]);

					if (firstOp == beforeOp && secondOp == currentOp) {
						setupOverhead = get<2>(machine.setupDuration[z]);
						break;
					}
				
				}

			}
			
		}
		scheduleTime = scheduleTime + timeNeeded + setupOverhead;

		// push it to completeSchedule vector
		Schedule mySchedule = Schedule(scheduleTime, processCode, orderCode, amountOfWork, setupOverhead);
		CompleteSchedule.push_back(mySchedule);
	}
	// end of schedule calculation


	//Write to Schedule.txt
	OutFile.open("Schedule.txt", std::ofstream::out | std::ofstream::trunc);  // this is for clearing the output.txt if its written
	for (int x = 0; x < CompleteSchedule.size(); x++) {
		OutFile << CompleteSchedule[x].time << ";" << CompleteSchedule[x].opCode << ";" << CompleteSchedule[x].order_num << ";" << CompleteSchedule[x].amountWork << ";" << CompleteSchedule[x].setup_overhead<<endl;
	}
	OutFile.close();
	//end of writing to Schedule.txt
}