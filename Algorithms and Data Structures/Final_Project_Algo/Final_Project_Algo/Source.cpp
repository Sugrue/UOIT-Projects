/*
     _    _                  _ _   _                      ___
    / \  | | __ _  ___  _ __(_) |_| |__  _ __ ___  ___   ( _ )
   / _ \ | |/ _` |/ _ \| '__| | __| '_ \| '_ ` _ \/ __|  / _ \/\
  / ___ \| | (_| | (_) | |  | | |_| | | | | | | | \__ \ | (_>  <
 /_/   \_\_|\__, |\___/|_|  |_|\__|_| |_|_| |_| |_|___/  \___/\/
|___/
____        _          ____  _                   _
|  _ \  __ _| |_ __ _  / ___|| |_ _ __ _   _  ___| |_ _   _ _ __ ___  ___
| | | |/ _` | __/ _` | \___ \| __| '__| | | |/ __| __| | | | '__/ _ \/ __|
| |_| | (_| | || (_| |  ___) | |_| |  | |_| | (__| |_| |_| | | |  __/\__ \
|____/ \__,_|\__\__,_| |____/ \__|_|   \__,_|\___|\__|\__,_|_|  \___||___/
 ___ _   _ _____ ____    ____  ___ ____   ___  _   _
|_ _| \ | |  ___|  _ \  |___ \( _ )___ \ / _ \| | | |  Networking & IT Sec.
 | ||  \| | |_  | |_) |   __) / _ \ __) | | | | | | |  Final Project
 | || |\  |  _| |  _ <   / __/ (_) / __/| |_| | |_| |
|___|_| \_|_|   |_| \_\ |_____\___/_____|\___/ \___/

By: Kyle Sugrue       100483306
Scott Spiering    100484450
Graham MacGregor  100485734

NOTES:
Algorithms are not working at 100%

Both algorithms will find the correct paths on the condition that the edges are in the "correct direction". IE expanding out from the source.

One solution applied for Kruskal's algorithm is to enter douplicate edges in the oppsite direction. IE Ottawa -> Montreal and Montreal -> Ottawa.

However this dos not work well with Bellman Ford, as loops are created. A possible solution would be to verify if the path before adding a predecessors
however we were unable to do this.
*/

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
bool BOOLdupEntry = false; //switch to true for duplicate entries (See notes)

class edge {
	//Class edge, used to store all edge information
private:
	string STRsource;
	string STRdestination;

	int INTcost = NULL;
	int INTsource = NULL;
	int INTdestination = NULL;

public:
	string getSTRsource() { return STRsource; };
	string getSTRdestination() { return STRdestination; };
	int getINTcost() { return INTcost; };
	int getINTdestination() { return INTdestination; };
	int getINTsource() { return INTsource; };

	void setSource(string STR, int INT) {
		STRsource = STR;
		INTsource = INT;
	};
	void setDestination(string STR, int INT) {
		STRdestination = STR;
		INTdestination = INT;
	};
	void setCost(int INT) { INTcost = INT; };

	edge(string STRscr, int INTscr, string STRdest, int INTdest, int INTcst) {
		setSource(STRscr, INTscr);
		setDestination(STRdest, INTdest);
		setCost(INTcst);
	};

};
void cls() {
	//clears the screen
	for (int i = 0; i < 26; i++)
		cout << endl;
}
void line(){
	//adds a line
	cout << "################################################################################";
}
bool readFile(string STRpath, vector<edge*> &VECedge, vector<string> &VECnodeName) {
	/*reads from the file one line at a time. Checks to see if a unique number has been previously assigned to a 
	node by verifiying the vector VECnodeName, if so it assignes the number associated with the node. This process
	ensures that no duplicated node IDs can be created.

	VECnodeName[X], where X is the node ID and the value stored in the vector at that particular position is the 
	node name.	

	The VECedge vector is populated with the edges, so long as a douplicate dos not exist.
*/

	string STRdestination;
	string STRsource;
	int INTcost;
	int INTdestination;
	int INTsource;
	int i;


	ifstream file;
	file.open(STRpath);

	if (!file.is_open()) {
		cout << "ERROR NO FILE FOUND" << endl;
		return false;
	}


	while (file >> STRsource >> STRdestination >> INTcost) {
		INTdestination = -1;
		INTsource = -1;

		for (i = 0; i < VECnodeName.size(); i++) {
			if (STRsource == VECnodeName[i])
				INTsource = i;

			if (STRdestination == VECnodeName[i])
				INTdestination = i;
		}

		if (INTsource == -1) {
			VECnodeName.resize(VECnodeName.size() + 1);
			VECnodeName[VECnodeName.size() - 1] = STRsource;
			INTsource = VECnodeName.size() - 1;
		}

		if (INTdestination == -1) {
			if (STRdestination == STRsource)
				INTdestination = INTsource;
			else {
				VECnodeName.resize(VECnodeName.size() + 1);
				VECnodeName[VECnodeName.size() - 1] = STRdestination;
				INTdestination = VECnodeName.size() - 1;
			}
		}

		if (!BOOLdupEntry) {
			VECedge.resize(VECedge.size() + 1);
			VECedge[VECedge.size() - 1] = new edge(STRsource, INTsource, STRdestination, INTdestination, INTcost);
		} 
		else {
			VECedge.resize(VECedge.size() + 2);
			VECedge[VECedge.size() - 1] = new edge(STRsource, INTsource, STRdestination, INTdestination, INTcost);
			VECedge[VECedge.size() - 2] = new edge(STRdestination, INTdestination, STRsource, INTsource, INTcost);
		}
	}
}
bool printEdge(vector<edge*> &VECedge) {
	//Prints all the edges by shuffling through a provided vector.
	cout
		<< "  _____    _                 " << endl
		<< " | ____|__| | __ _  ___  ___ " << endl
		<< " |  _| / _` |/ _` |/ _ \\/ __|" << endl
		<< " | |__| (_| | (_| |  __/\\__ \\" << endl
		<< " |_____\\__,_|\\__, |\\___||___/" << endl
		<< "             |___/           " << endl << endl;

	cout << "Num\tSource\t\tDestination\tCost" << endl;

	if (VECedge.size() == 0) {
		cout << "ERROR: THERE ARE NO EDGES." << endl;
		return false;
	}

	for (int i = 0; i < VECedge.size(); i++)
		cout << i << "\t" << VECedge[i]->getSTRsource() << "[" << VECedge[i]->getINTsource() << "]\t"
		<< VECedge[i]->getSTRdestination() << "[" << VECedge[i]->getINTdestination() << "]\t"
		<< VECedge[i]->getINTcost() << endl;

	return true;
}
bool printNodeName(vector<string> &VECnodeName, vector<edge*> VECedge) {
	//prints all the nodes by shuffling through a provided vector
	vector<bool> VECcheck;
	VECcheck.resize(VECnodeName.size());

	for (int i = 0; i < VECcheck.size(); i++)
		VECcheck[i] = false;

	cout
		<< "  _   _           _           " << endl
		<< " | \\ | | ___   __| | ___  ___ " << endl
		<< " |  \\| |/ _ \\ / _` |/ _ \\/ __|" << endl
		<< " | |\\  | (_) | (_| |  __/\\__ \\" << endl
		<< " |_| \\_|\\___/ \\__,_|\\___||___/" << endl;

	cout << "Number\tName" << endl;

	if (VECnodeName.size() == 0) {
		cout << "ERROR: THERE ARE NO NODES." << endl;
		return false;
	}

	for (int i = 0; i < VECnodeName.size(); i++) 
		for (int j = 0; j < VECedge.size(); j++) 
			if (VECnodeName[i] == VECedge[j]->getSTRsource() || VECnodeName[i] == VECedge[j]->getSTRdestination())
				VECcheck[i] = true;
		
	

	for (int i = 0; i < VECnodeName.size(); i++) {
		cout << i << "\t" << VECnodeName[i];
		if (VECcheck[i] == false)
			cout << "\t NODE IS NOT CONNECTED TO ANY OTHER NODES";
		cout << endl;
	}

	return true;
}
bool bellmanFord(vector<edge*> &VECedge, vector<string> &VECnodeName, int INTstartNode) {
	/*
	The algorithm starts by assigning all nodes a distance of infinity except the starting point. The alogrithm then checks if the distance found in the VECdistance vector plus the 
	cost of the edge connecting two nodes is smaller then its stored distance. As only the a path starting from the source node will be less these are the only paths that can be found.

	Once an edge that meets this condition is found it "predecessor" (or the edge's source) is stored at the node (or the edge's destination) entry within the vector. IE. VECpredecessors[X] 
	where x is the node

	It then prints the results in a recusive fashion. Starting from a node and backing up through the predecessors until the source node is found. The process is repeated for all nodes.
	
	*/
	vector <int> VECdistance;
	vector <int> VECpredecessors;
	vector <int> VECpath;

	const int INFINI = 999999999;

	if (VECnodeName.size() == 0) {
		cout << "ERROR NO NODES."<<endl;
		return false;
	}

	VECdistance.resize(VECnodeName.size());
	VECpredecessors.resize(VECnodeName.size());

	for (int i = 0; i < VECnodeName.size(); i++) {
		VECdistance[i] = INFINI;
	}
	for (int i = 0; i < VECpredecessors.size(); i++)
		VECpredecessors[i] = i;
	
	VECdistance[INTstartNode] = 0;

	for (int i = 0; i < VECnodeName.size()-1; i++)
		for (int j = 0; j < VECedge.size(); j++) {
			if (VECdistance[VECedge[j]->getINTsource()] + VECedge[j]->getINTcost() < VECdistance[VECedge[j]->getINTdestination()])  {
					VECdistance[VECedge[j]->getINTdestination()] = VECedge[j]->getINTsource() + VECedge[j]->getINTcost();
					VECpredecessors[VECedge[j]->getINTdestination()] = VECedge[j]->getINTsource();
				
				}
		}
	
	cout << "********************************************************************************" << endl
		<< "SOURCE NODE" << endl
		<< "\t\tFIRST HOP" << endl
		<< "\t\tSECOND HOP" << endl
		<< "\t\tTHIRD HOP" << endl
		<< "\t\t\t\tDESTINATION NODE" << endl
		<< "********************************************************************************"<< endl;
	system("pause");
	cls();

	//Since paths are added from destination to source using the push back functions, the path can be printed by printing the last node/hop, poping it off, and repeat until the path vector is empty 
	for (int i = 0; i < VECnodeName.size(); i++) {
		if (i != VECpredecessors[VECpredecessors[i]] || VECpredecessors[i] == i) {
			if (VECdistance[i] != INFINI) {
				VECpath.push_back(i);

				while (VECpath[VECpath.size() - 1] != INTstartNode)
					VECpath.push_back(VECpredecessors[VECpath[VECpath.size() - 1]]);

				cout << VECnodeName[VECpath[VECpath.size() - 1]] << endl;
				VECpath.pop_back();

				while (VECpath.size() >= 2) {
					cout << "\t\t" << VECnodeName[VECpath[VECpath.size() - 1]] << endl;
					VECpath.pop_back();
				}

				if (VECpath.size() == 1)
					cout << "\t\t\t\t" << VECnodeName[VECpath[VECpath.size() - 1]] << " Cost: " << VECdistance[VECpath[VECpath.size() - 1]] << endl;
				VECpath.resize(0);

				cout << "********************************************************************************";
			}
			else {
				cout << "ERROR: " << VECnodeName[i] << "IS UNREACHABLE FROM " << VECnodeName[INTstartNode] << endl;
				cout << "********************************************************************************";
			}
		}
		else {
			cout << "THE PATH BETWEEN " << VECnodeName[i] << "[" << i << "] and " << VECnodeName[VECpredecessors[i]] << "[" << VECpredecessors[i] << "] IS LOOPED" << endl;
			cout << "********************************************************************************";
		}
	}
	return true;
}
bool kruskals(vector<edge*> &VECedge, vector<string> &VECnodeName) {
	/*
	Kruskals algorithm is impliment here by first using bubble sort to sort the edges in order. Afterwhich, the smallest cost edge is added to the Minimum 
	Spanning Tree (VECmPT), then the nodes connected to the edge in question are added to the node list VECnode.

	Afterward, each eadge is check (in order, smallest to largest cost), if one is found who's source or destination node is not found in the node list (VECnode)
	it is safe to assume that the edge dos not form a loop. At which point the edge is added to the MPT and the node(s) that are not present in the node list are
	added	
	*/
	bool BOOLswapped;
	edge* EDGEtemp;
	vector<edge*> VECtempEdge = VECedge;
	vector<int> VECnode;
	vector <edge*> VECmST;
	bool BOOLedgeCheck = false;

	if (VECnodeName.size() == 0) {
		cout << "ERROR NO NODES." << endl;
		return false;
	}


	for (int i = 0; i < VECtempEdge.size(); i++)
	for (int j = 0; j < VECtempEdge.size() - 1; j++) {
		if (VECtempEdge[j]->getINTcost() > VECtempEdge[j + 1]->getINTcost()) {
			EDGEtemp = VECtempEdge[j];
			VECtempEdge[j] = VECtempEdge[j + 1];
			VECtempEdge[j + 1] = EDGEtemp;
		}
	}

	if (VECtempEdge[0]->getINTdestination() == VECtempEdge[0]->getINTsource())
		VECnode.push_back(VECtempEdge[0]->getINTsource());
	else {
		VECnode.push_back(VECtempEdge[0]->getINTsource());
		VECnode.push_back(VECtempEdge[0]->getINTdestination());
	}

	VECmST.push_back(VECtempEdge[0]);

	for (int i = 1; i < VECtempEdge.size(); i++) {
		for (int j = 0; j < VECnode.size(); j++) {
			BOOLedgeCheck = false;

			if (VECtempEdge[i]->getINTsource() == VECnode[j]) {
				BOOLedgeCheck = true;
				break;
			}
		}

		if (BOOLedgeCheck == false) {
			VECmST.push_back(VECtempEdge[i]);
			VECnode.push_back(VECtempEdge[i]->getINTsource());
		}
		else {
			BOOLedgeCheck = false;

			for (int j = 0; j < VECmST.size(); j++) {
				if (VECtempEdge[i]->getINTdestination() == VECnode[j]) {
					BOOLedgeCheck = true;
					break;
				}
			}

			if (BOOLedgeCheck == false) {
				VECmST.push_back(VECtempEdge[i]);
				VECnode.push_back(VECtempEdge[i]->getINTdestination());
			}
		}
	}



	cout << "  __  __ _       _                                             " << endl
		<< " |  \\/  (_)_ __ (_)_ __ ___  _   _ _ __ ___                        " << endl
		<< " | |\\/| | | '_ \\| | '_ ` _ \\| | | | '_ ` _ \\                       " << endl
		<< " | |  | | | | | | | | | | | | |_| | | | | | |                      " << endl
		<< " |_|  |_|_|_| |_|_|_| |_| |_|\\__,_|_| |_| |_|                      " << endl
		<< "  ____                          _               _____              " << endl
		<< " / ___| _ __   __ _ _ __  _ __ (_)_ __   __ _  |_   _| __ ___  ___ " << endl
		<< " \\___ \\| '_ \\ / _` | '_ \\| '_ \\| | '_ \\ / _` |   | || '__/ _ \\/ _ \\" << endl
		<< "  ___) | |_) | (_| | | | | | | | | | | | (_| |   | || | |  __/  __/" << endl
		<< " |____/| .__/ \\__,_|_| |_|_| |_|_|_| |_|\\__, |   |_||_|  \\___|\\___|" << endl
		<< "       |_|                              |___/                     " << endl;

	//MPT paths are printed in edge form to avoid complications (See notes section)
	printEdge(VECmST);

	return true;

}
bool removeEdge(vector<edge*> &VECedge, int INTdelEdge) {
	//Deletes a particular node, moves all nodes located after it forwards, then pops the last node (Which is empty)
	delete VECedge[INTdelEdge];

	for (int i = INTdelEdge; i < VECedge.size()-1; i++)
		VECedge[i] = VECedge[i + 1];

	VECedge.pop_back();

	return true;
}
bool changeCost(vector<edge*> &VECedge, int INTEdge, int INTcost) {
	//changes the edge's cost value

	VECedge[INTEdge]->setCost(INTcost);
	return true;
}
bool removeNode(vector<edge*> &VECedge, vector<string> &VECnodeName, int INTnode) {
	/*
	The particular nodes connecting edges (source or destination) are found and removed by way of the remove edge function. Afterwards the node can safely be deleted
	*/
	for (int i = 0; i < VECedge.size(); i++)
		if (VECedge[i]->getINTdestination() == INTnode || VECedge[i]->getINTsource() == INTnode) {
			delete VECedge[i];
			VECedge[i] = NULL;
		}

		for (int i = 0; i < VECedge.size(); i++)
		if (VECedge[i] == NULL) {
			removeEdge(VECedge, i);
			i--;
		}
			
	for (int i = INTnode; i < VECnodeName.size() - 1; i++)
		VECnodeName[i] = VECnodeName[i + 1];
	VECnodeName.pop_back();

	return true;
}
bool addEdge(vector<edge*> &VECedge, vector<string> &VECnodeName) {
	int INTinput[3];

	cls();

	printNodeName(VECnodeName, VECedge);
	line();
	cout << "Edit" << endl;
	cout << "\tPlease select a source node:";
	cin >> INTinput[0];

	cout << "\tPlease provide an edge Cost:";
	cin >> INTinput[1];
	cout << "\tPlease select a destination node:";
	cin >> INTinput[2];

	for (int i = 0; i < VECedge.size(); i++) {
		if (VECedge[i]->getINTsource() == INTinput[0] && VECedge[i]->getINTcost() == INTinput[1] && VECedge[i]->getINTdestination() == INTinput[2]) {
			cout << "EDGE ALREADY EXISTS" << endl;
			system("pause");
			return false;
		}
	}

	if (INTinput[0] < VECnodeName.size() && INTinput[2] < VECnodeName.size()) {
		VECedge.push_back(new edge(VECnodeName[INTinput[0]], INTinput[0], VECnodeName[INTinput[2]], INTinput[2], INTinput[1]));
		return true;
	}
	else {
		cout << "ONE OF THE NODES ENTERED DOS NOT EXIST" << endl;
		system("pause");
		return false;
	}
}
bool addNode(vector<edge*> &VECedge, vector<string> &VECnodeName) {
	vector<int> VECinput;
	string STRnode;

	cls();
	cout << "Edit" << endl;
	cout << "\t[Please ensure that you add edges through the 'add edges' option featured on the main menu]" << endl;
	cout << "\tNode Name:";
	cin >> STRnode;
	
	for (int i = 0; i < VECnodeName.size(); i++) {
		if (VECnodeName[i] == STRnode) {
			cout << "ERROR. NODE ALREADY EXISTS" <<endl<< endl;
			system("Pause");
			return false;
		}
	}

	VECnodeName.push_back(STRnode);
	
	//addEdge(VECedge, VECnodeName);
}
int main() {
	//Simple menu based system, printing, collecting input and calling the desired functions

	vector<edge*> VECedge;
	vector<string> VECnodeName;
	int INTtemp[2];
	int INTinput;
	string STRinput;

	const string FILE = "network.txt";

	cout << "     _    _                  _ _   _                      ___           " << endl
		<< "    / \\  | | __ _  ___  _ __(_) |_| |__  _ __ ___  ___   ( _ )              " << endl
		<< "   / _ \\ | |/ _` |/ _ \\| '__| | __| '_ \\| '_ ` _ \\/ __|  / _ \\/\\            " << endl
		<< "  / ___ \\| | (_| | (_) | |  | | |_| | | | | | | | \\__ \\ | (_>  <            " << endl
		<< " /_/   \\_\\_|\\__, |\\___/|_|  |_|\\__|_| |_|_| |_| |_|___/  \\___/\\/            " << endl
		<< "            |___/                                                           " << endl
		<< "  ____        _          ____  _                   _                        " << endl
		<< " |  _ \\  __ _| |_ __ _  / ___|| |_ _ __ _   _  ___| |_ _   _ _ __ ___  ___  " << endl
		<< " | | | |/ _` | __/ _` | \\___ \\| __| '__| | | |/ __| __| | | | '__/ _ \\/ __| " << endl
		<< " | |_| | (_| | || (_| |  ___) | |_| |  | |_| | (__| |_| |_| | | |  __/\\__ \\ " << endl
		<< " |____/ \\__,_|\\__\\__,_| |____/ \\__|_|   \\__,_|\\___|\\__|\\__,_|_|  \\___||___/ " << endl
		<< "  ___ _   _ _____ ____    ____  ___ ____   ___  _   _                       " << endl
		<< " |_ _| \\ | |  ___|  _ \\  |___ \\( _ )___ \\ / _ \\| | | |  Networking & IT Sec." << endl
		<< "  | ||  \\| | |_  | |_) |   __) / _ \\ __) | | | | | | |  Final Project       " << endl
		<< "  | || |\\  |  _| |  _ <   / __/ (_) / __/| |_| | |_| |                      " << endl
		<< " |___|_| \\_|_|   |_| \\_\\ |_____\\___/_____|\\___/ \\___/                       " << endl
		<< endl
		<< "                                     By: Kyle Sugrue       100483306" << endl
		<< "                                         Scott Spiering    100484450" << endl
		<< "                                         Graham MacGregor  100485734" << endl<<endl<<endl;

	
	
	cout << "Please enter specify the location of Network.txt [.\\network.txt]"<<endl
		<< "\\ must be followed by another. IE C:\\\\windows\\\\"<<endl
		 <<"For the default please enter 0   ";
	cin >> STRinput;

	if (STRinput == "0")
		readFile(FILE, VECedge, VECnodeName);
	else
		readFile(STRinput, VECedge, VECnodeName);
	do{
		cls();

		cout << "  __  __       _         __  __              " << endl
			<< " |  \\/  | __ _(_)_ __   |  \\/  | ___ _ __  _   _ " << endl
			<< " | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |" << endl
			<< " | |  | | (_| | | | | | | |  | |  __/ | | | |_| |" << endl
			<< " |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|" << endl << endl;

		cout << "View" << endl
			<< "\t\t1. View Edges" << endl
			<< "\t\t2. View Nodes" << endl
			<< "\t\t3. View Nodes & Edges" << endl
			<< "Edit" << endl
			<< "\t\t4. Edit the Cost of an edge (Weight)" << endl
			<< "\t\t5. Remove an edge" << endl
			<< "\t\t6. Remove a node" << endl
			<< "\t\t7. Add an edge"<<endl
			<< "\t\t8. Add a node"<<endl
			<< "Algorithms" << endl
			<< "\t\t9. Bellman-Ford" << endl
			<< "\t\t10. Kruskal" << endl
			<< "Program" << endl
			<< "\t\t11.Quit" << endl;

		cin >> INTinput;

		switch (INTinput) {
		case 1:
			cls();
			printEdge(VECedge);
			system("pause");
			break;
		case 2:
			cls();
			printNodeName(VECnodeName, VECedge);
			system("pause");
			break;
		case 3:
			cls();
			printNodeName(VECnodeName, VECedge);
			printEdge(VECedge);
			system("pause");
			break;
		case 4:
			cls();
			printEdge(VECedge);
			
			line();
			cout << "Edit"<<endl
				<< "\t4. Edit the Cost of an edge (Weight)" << endl
				<< "\t   Please chose an Edge:";
			cin >> INTtemp[0];
			cout << "\t   Please specify the new cost (Weight):";
			cin >> INTtemp[1];
			line();

			changeCost(VECedge, INTtemp[0], INTtemp[1]);
			printEdge(VECedge);
			system("pause");
			break;
		case 5:
			cls();
			printEdge(VECedge);
			
			line();
			cout << "Edit"<<endl
				<< "\t5. Remove an edge" << endl
			    << "\t   Please chose en Edge:";
			cin >> INTtemp[0];
			line();

			removeEdge(VECedge, INTtemp[0]);
			printEdge(VECedge);
			system("pause");
			break;
		case 6:
			cls();
			printNodeName(VECnodeName, VECedge);

			line();
			cout << "Edit"<<endl
				<< "\t6. Remove a node" << endl
				<< "\t   Please chose a Node:";
			cin >> INTtemp[0];
			line();

			removeNode(VECedge, VECnodeName, INTtemp[0]);
			printNodeName(VECnodeName, VECedge);
			system("pause");
			break;
		case 7:
			cls();
			addEdge(VECedge, VECnodeName);
			break;
		case 8:
			cls();
			addNode(VECedge, VECnodeName);
			break;
		case 9:
			cls();
			printNodeName(VECnodeName, VECedge);

			line();
			cout << "Algorithms" << endl
				<< "\t7. Bellman-Ford" << endl
				<< "\t   Please chose a Node:";
			cin >> INTtemp[0];
			line();
			cls();

			bellmanFord(VECedge, VECnodeName, INTtemp[0]);
			system("pause");
			break;
		case 10:
			cls();

			kruskals(VECedge, VECnodeName);
			system("pause");
			break;

			break;
		case 11:
			break;
		default:
			cls();
			cout << "ERROR: INVAILD INPUT. PLEASE TRY AGAIN." << endl;
			system("pause");
		}
	} while (INTinput != 11);
	return 0;
}


