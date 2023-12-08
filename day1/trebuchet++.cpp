#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include<unordered_map>

int main()
{
	std::unordered_map<std::string, int> lookUpTable;
	lookUpTable.insert({
		{"0",0},
		{"1",1},
		{"2",2},
		{"3",3},
		{"4",4},
		{"5",5},
		{"6",6},
		{"7",7},
		{"8",8},
		{"9",9},
		{"zero",0},
		{"one",1},
		{"two",2},
		{"three",3},
		{"four",4},
		{"five",5},
		{"six",6},
		{"seven",7},
		{"eight",8},
		{"nine",9},
		{"orez",0},
		{"eno",1},
		{"owt",2},
		{"eerht",3},
		{"ruof",4},
		{"evif",5},
		{"xis",6},
		{"neves",7},
		{"thgie",8},
		{"enin",9}
		});
	std::fstream file("long.txt");
	std::string currentString;
	std::regex reg("(zero|one|two|three|four|five|six|seven|eight|nine|0|1|2|3|4|5|6|7|8|9)");
	std::regex r_reg("(orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|0|1|2|3|4|5|6|7|8|9)");
	std::match_results<std::string::const_reverse_iterator> rmatch;
	std::sregex_iterator end;
	int currentSum = 0;

	while (getline(file, currentString))
	{
		//getline(std::cin, currentString);
		std::sregex_iterator iter(currentString.begin(), currentString.end(), reg);
		std::smatch match;
		for (iter; iter != end && match.empty(); iter++)
		{
			match = *iter;
			//std::cout << match[0] << "\n";
			currentSum += lookUpTable[match[0]] * 10;
		}
		(void)std::regex_search(currentString.crbegin(), currentString.crend(), rmatch, r_reg);
		//std::cout << rmatch[0] << "\n";
		currentSum += lookUpTable[rmatch[0]];
		//std::cout << currentSum << "\n";
	}
	std::cout << currentSum;
	return 0;
}
