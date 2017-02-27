#include <iostream>
#include<regex>
#include<string>

using namespace std;




int main() {



	regex reg1("<[^/]");


	smatch match;

	int codeLinesN = 20;
	int queries = 20;
	bool startafterFirst = false;
	int counterflag = 0;
	string allinOne = "";
	string dynamicExpression = "";
	bool doublecheck = false;
	//	cin >> codeLinesN >> queries;//4 3

	char MaxCharacters[201] = { '\0' };

	//dynamic string array allocation in heap memory
	string * sentence = new string[codeLinesN];//for saving code lines as a string index
	string * saveResults = new string[queries];//for saving fetching results from quiries


											   //	cin.ignore();//flush stream

	for (int i = 0; i < codeLinesN; ++i) {

		cin.getline(MaxCharacters, 200);//Take total characters

										//Assigning built in all char array to string array index 0
		sentence[i] = MaxCharacters;


		//Algorithm for adding dots(.) in whole code

		if (startafterFirst) {

			//Regex
			if (regex_search(sentence[i], match, reg1)) {

				allinOne += ".";

				if (counterflag != 0) {
					allinOne.erase(allinOne.size() - 1, 1);//erase last character which is dot(.) at last index
					counterflag--;
				}


			}
			else {
				counterflag = 1;

			}

		}

		allinOne += sentence[i];

		startafterFirst = true;

	}//loop termination of code lines

	delete[]sentence;


	string Lastexpression = "";
	string attrGet = "";
	int index;
	int tildaCounter;
	//Quiries
	for (int j = 0; j < queries; ++j) {
		tildaCounter = 0;
		index = 0;
		dynamicExpression = "(<";
		attrGet = "";
		

		cin.getline(MaxCharacters, 200);


		for (int k = 0; MaxCharacters[k] != '\0'; k++) {

			//it means it's a Next tag
			if (MaxCharacters[k] == '.') {
				//save index at dot appears

				dynamicExpression += ".*?>\\.";
				//capture dot(.) index
				index = dynamicExpression.size() - 1;
				dynamicExpression += "<";
				continue;//jump this iteration


			}
			//it means it's a attribute
			else if (MaxCharacters[k] == '~') {
				tildaCounter++;
				//For Replacing close parenthesis for those elements who doesn't have any attribute

				if (index != 0) {
					dynamicExpression.replace(index, 1, ".)(");
				}

				else {
				//	dynamicExpression.erase(0, 1);
				}



				dynamicExpression += ".*?";

				while (MaxCharacters[k] != '\0') {

					k++;


					if (MaxCharacters[k] != '\0') {
						attrGet += MaxCharacters[k];
					}

				}//while loop terminate


				k--;//decrement one time because we don't want to to iterate
				dynamicExpression += attrGet + ")";
				if (index != 0) {
					int totallength = dynamicExpression.size() - 1;
					Lastexpression = dynamicExpression.substr(index + 2, totallength);
				}
				continue;//jump this iteration

			}//else if


			dynamicExpression += MaxCharacters[k];



		}//for loop characters iteration



		if (tildaCounter == 0) {

			dynamicExpression.erase(0, 1);

		}

		 //Capture group 1 checking , After dynamic expression is made

		 //------------------------------------------
		regex reg2(dynamicExpression);
		if (regex_search(allinOne, match, reg2)) {



			//Now check if it's a valid query or not also remember index if only single element is write
			string doubleCheckExpression = match[1].str() + Lastexpression;

			regex reg3(doubleCheckExpression);
			smatch tempmatch;

			if (regex_search(allinOne, tempmatch, reg3)) {


				//Fetching attribute values algorihm
				//------------------------------------------

				string newExpressionAgain = "(" + match.str();

				newExpressionAgain += " = \")(.*?)\"";

				regex reg4(newExpressionAgain);

				//a new expression contain group match which results as a sub matches
				if (regex_search(allinOne, match, reg4)) {


					saveResults[j] = match[2].str();


				}



			}


		}//Searching value finish
		else {
			saveResults[j] = "Not Found!";
		}



	}//for loop exit



	for (int i = 0; i < queries; ++i)
		cout << saveResults[i] << endl;

	delete[] saveResults;

	system("pause");
}//Main