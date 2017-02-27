#include <iostream>
#include<regex>
#include<string>
#include<sstream>


using namespace std;



string EliminateSpacesAndAddNumbering(char *);

//Global Variable for how many attributes a line has?
int attr = 0;


int main() {


	//First Expression check does line number has attributes
	regex reg1("(<(.*=\".*\")>|(.*= \".*\")>)");//Expression for feteching tags that have attributes.
	regex reg2("\"\\S*?\"");//Expression for fetching attrbutes values.
	smatch match;

	int codeLinesN =0 ;
	int queries = 0;
	cin >> codeLinesN >> queries;//4 3

	char MaxCharacters[201] = { '\0' };
	
	//dynamic string array allocation in heap memory
	string * sentence = new string[codeLinesN];//for save lines as total 1 string
	string * queryResults = new string[queries];//Query Results
	string **TagValues = new string*[codeLinesN];//for fetching like tags are the keys and attributes are column




	cin.ignore();//flush stream

	for (int i = 0; i < codeLinesN; ++i) {



		cin.getline(MaxCharacters, 200);//Take total characters


										//Assigning built in all char array to string array index 0
		sentence[i] = MaxCharacters;

		//Array full string
		if (regex_search(sentence[i], match, reg1)) {


			//Method Calling
			//	LineNoTagName = FetchTagName(MaxCharacters);

			//Eliminate space's and make a whole one new sentence two arguments char, string pointer
			sentence[i] = EliminateSpacesAndAddNumbering(MaxCharacters);

			//calculate how many attributes and allocate columns for example 2
			TagValues[i] = new string[attr];


			//Save Values in the form of columns
			//sregex token iterator
			sregex_token_iterator pos(sentence[i].cbegin(), sentence[i].cend(), reg2);
			sregex_token_iterator end;//default constructor

			for (int j = 0; pos != end; pos++) {

				string s = *pos;

				//eliminate double quotes at first index and last index
				s.erase(0, 1);
				s.erase(s.size() - 1, 1);

				//put the values
				TagValues[i][j] = s;
				j++;
			}

		}//if end for regex_search() function


	}//for end


	 //------------------------------------

	 //Quiries
	int RowNo = 0;
	string attributeinQuery;
	for (int i = 0; i < queries; ++i) {
		cin.getline(MaxCharacters, 200);//Take total characters

		RowNo = 0;
		//--------------------------------------------------------
		//Characters iteration
		for (int i = 0; MaxCharacters[i] != '\0'; i++) {

			attributeinQuery = "";
			if (MaxCharacters[i] == '.') {
				RowNo++;//means cursor is in this line
			}
			else if (MaxCharacters[i] == '~') {

				while (MaxCharacters[i] != '\0') {

					//fetch attribute name
					i++;
					if (MaxCharacters[i] != '\0')
						attributeinQuery += MaxCharacters[i];

				}
				i--;//decrement one time because we don't want to to iterate
			}//else if

		}//for loop for check what's line no and what is attribute



		 //My New Expression
		string newExpression = attributeinQuery + "\\d";
		//regex and new smatch
		regex nMade(newExpression);
		smatch nMatch;

		if (regex_search(sentence[RowNo], nMatch, nMade)) {

			string rt = nMatch.str();
			//casting char into integer
			int columnIndex = rt[rt.size() - 1] - '0';
			queryResults[i] = TagValues[RowNo][columnIndex];
		}
		else {
			queryResults[i] = "Not Found!";
		}


	}//For Loop End



	 //Print Results
	for (int i = 0; i < queries; ++i)
		cout << queryResults[i] << endl;


	delete[]sentence;
	delete[]queryResults;
	delete[]TagValues;



}//Main End





string EliminateSpacesAndAddNumbering(char * ctr) {
	string tempstr;
	ostringstream oss;
	int totalattr = -1;
	int assignArray = 0;

	for (int i = 0; ctr[i] != '\0'; i++) {
		if (ctr[i] != ' ') {

			if (ctr[i] == '=') {
				totalattr++;
				assignArray++;
				//inserts format data
				oss << totalattr;
				tempstr += oss.str();
				oss.str("");// after 1 is converted to integer we want to remove old ostringstream character
			}
			tempstr += ctr[i];

		}

	}

	attr = assignArray;
	//Return edit array
	return tempstr;

}