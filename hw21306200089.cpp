/*

Ali Ihsan Basoglu
1306200089
Date : 22/05/2021
Development Environment: Visual Studio 2019

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

using namespace std;

class Node {
	public:
	string type;
	string name;

	vector <Node> links;
	
	Node(string typ, string nam) {
		type = typ;
		name = nam;

	}
};

int main() {

	vector <Node> nodes;		// all nodes will be stored in here 

	fstream newfile;
	newfile.open("input.txt", ios::in);												// dosyayi acma
	if (newfile.is_open()) {													//dosya acik mi ? 
		string line;
		while (getline(newfile, line)) {										// satir satir oku
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // bosluklari sil
			int i = 0;																	// char index resets every new line 
			if (line != "Paths:") {
				
				while (i < line.length()) {
					char c = line.at(i);
					//START of node init and push them into the nodes vector. 
					if (c == ',') {

						string ty;
						ty = line.at(i - 2);
						string nm;
						nm = line.at(i - 1);

						Node node(ty, ty + nm);
						nodes.push_back(node);


						try
						{
							if (line.at(i + 3)) {

							}
						}
						catch (exception) {
							ty = line.at(i + 1);
							nm = line.at(i + 2);
							Node node(ty, ty + nm);
							nodes.push_back(node);
						}
						//END of node init 
					}

					// START of links init
					if (c == '>') {
						string nodeName;
						string no;
						string deName;
						string link;
						string li;
						string nk;

						no = line.at(i - 3);
						deName = line.at(i - 2);
						nodeName = no + deName;
						li = line.at(i + 1);
						nk = line.at(i + 2);
						link = li + nk;

						for (int x = 0; x < nodes.size(); x++) {
							if (nodes[x].name == nodeName) {
								for (int y = 0; nodes.size(); y++) {
									if (nodes[y].name == link) {
										nodes[x].links.push_back(nodes[y]);
										break;
									}
								}
							}
						}
					}
					// END of links init

					i++;
				}
			}
			else {
				 
				//cout << "else basladi " << endl;
				ofstream OutFile;

				OutFile.open("output.txt", std::ofstream::out | std::ofstream::trunc);  // this is for clearing the output.txt if its written
				OutFile.close();
				vector <string> yol;
				
				bool pathExist;
				while (getline(newfile, line)) {										// satir satir oku
					line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // bosluklari sil
					int i = 0;																	// char index resets every new line 

					while (i < line.length()) {
						char x = line.at(i);
						string y;
						y = x;
						yol.push_back(y);
						i++;
					} // charlari mape atama 
					
					//CHECK FOR THE PATH EXIST OR NOT 
					  
					vector <pair<Node, int>> stack;
					
					for (Node link : nodes) {
						
						if (yol[0] == link.type) {
							stack.push_back(std::make_pair(link, 0));		
						

						}
					}
					
					pathExist = false;
					while (stack.size() > 0) {
						
						Node node = stack[stack.size()-1].first;
						int i = stack[stack.size() - 1].second;
						stack.pop_back();
						
						for (auto link : node.links) {
							
							
							if (link.type == yol[i+1]) {
								
								stack.push_back(std::make_pair(link, i+1));
							}
						}

						if (yol.size() <= i + 1) {
							pathExist = true;
						}
											
						//ENDCHECK
						
					}

					string info; 
					if (pathExist) {
						info = "[YES]";
					}
					else {
						info = "[NO]";
					}
					yol.clear();
					ofstream OutFile;

					OutFile.open("output.txt", ios::app);
					OutFile << line << " " << info <<endl;
					//SATIR SONU
				}
				
			}

		}
	}
}