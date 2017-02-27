#include <iostream>
#include<string>
#include<vector>
#include <sstream>//for i/o operations memory (string),use of str("") function and for extract/insert content from string device object
#include<algorithm>//for Remove function
//Ordered associative containers - keys are maintained in sorted order
#include<map>//Replicates Associative Array, One-to-one mapping, no duplicates allowed,rapid key based lookup



using namespace std;

int main() {

	int cdLines;
	int que;
	int i;
	cin >> cdLines >> que;
	cin.ignore();//flush the stream

	vector<string> codeLines;
	vector<string> queries;
	map<string, string>	mp;//For Making Query & Value Pair
	string temporary;//for pushing content inside a vector or using this with analyze code loop
	vector<string>	tag;//for storing tagNames

						//Taking CodeLines
	for (i = 0; i < cdLines; ++i) {
		getline(cin, temporary);
		//Push codeline in vector
		codeLines.push_back(temporary);
	}

	//Taking Queries
	for (i = 0; i < que; ++i) {
		getline(cin, temporary);
		//Push query in vector
		queries.push_back(temporary);
	}


	//Analyze Code
	for (i = 0; i < cdLines; i++) {

		temporary = codeLines[i];
		//Using Erase/Remove idiom to remove " (double quotes) from container
		temporary.erase(remove(temporary.begin(), temporary.end(), '\"'), temporary.end());
		//Using Erase/Remove idiom to remove > (closing angle bracket) from container
		temporary.erase(remove(temporary.begin(), temporary.end(), '>'), temporary.end());

		//Now check if string first two characters are equal to "</" or not
		if (temporary.substr(0, 2) == "</") {
			tag.pop_back();
		}
		//We use stringstream object to insert/extract content in as tagName, Attribute , Value
		else {

			stringstream ss;
			//set the stringstream object as an empty
			ss.str("");
			//insert string in stringstream object
			ss << temporary;
			string tagName, attr, val;
			char ch;
			//extract data from stringstram object into three different string objects
			ss >> ch >> tagName >> attr >> ch >> val;
			//Creating another empty string object for
			string temporary2;

			//if code line has more attributes than it's mean vector size is greater than 0
			if (tag.size() > 0) {
				//it means it's a nested query
				temporary2 = *tag.rbegin();
				temporary2 = temporary2 + "." + tagName;
			}
			//else we save tagName in our vector 'tag'
			else {
				//save tagname in newly created string object
				temporary2 = tagName;

			}
				//and push tagName in our vector 'tag'
				tag.push_back(temporary2);
				
				//Storing query as a key
				mp[*tag.rbegin() + "~" + attr] = val;
				
				while (ss)
				{
					ss >> attr >> ch >> val;
					mp[*tag.rbegin() + "~" + attr] = val;
				}//while exit

			}//else exit


		}//for exit



	for (i = 0; i<que; i++) {
		
		if (mp.find(queries[i]) == mp.end()) {
			
			cout << "Not Found!\n";

		}
		else {
			cout << mp[queries[i]] << endl;

		}
	}


	}