#include <iostream>
#include <cstring>
#include <sstream>

#include "utils.hpp"

using namespace std;


int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		cout << "Do not enough arguments.\nUse Command ./make_input --bits [YOUR_12_BITS] --output_file [FILE_NAME]." << endl;
		return -1;
	}

	ArgumentParser parser = ArgumentParser(argc, argv);

	if(parser.haveArgument("--bits") == false || parser.haveArgument("--output_file") == false )
	{
		cout << "Invalid arguments.\nUse Command ./make_input --bits [YOUR_12_BITS] --output_file [FILE_NAME]." << endl;
		return -2;
	}

	vector<bool> bits;
	string s_bits = parser.getArgument("--bits");
	if(s_bits.length() != 12)
	{
		cout << "You have to set only 12 bits." << endl;
		return -3;
	}

	for(int i = 0; i < s_bits.length(); i ++)
	{
		bits.push_back(s_bits[i] == '1');
	}
	

	DataBunch data;

	generate_package(data, bits);
	
	print_bits_table(data);

	write_to_file(data, parser.getArgument("--output_file"));

	return 0;
}