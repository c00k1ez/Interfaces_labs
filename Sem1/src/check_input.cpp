#include <iostream>
#include <exception>
#include <fstream>
#include <map>
#include "utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc != 3)
	{
		cout << "Invalid args count.\nUse Command ./check_input -f [FILE_NAME]." << endl;
		return -1;
	}

	ArgumentParser parser = ArgumentParser(argc, argv);

	if(!parser.haveArgument("-f"))
	{
		cout << "Invalid arguments.\nUse Command ./check_input -f [FILE_NAME]." << endl;
		return -2;
	}

	DataBunch data;

	char byte;
	ifstream input(parser.getArgument("-f"));
	int byte_counter = 0, package_counter = 0;
	string byte_pack = "";
	vector<char> package_cnt = {0, 0, 0, 0};
	while (input.get(byte) && byte != '\n')
	{
		byte_counter++;
		byte_pack += byte;
	    if(byte_counter % 2 == 0)
	    {
	    	//cout << byte_pack << " " << package_counter << endl;

	    	string bits = hex2bin(byte_pack[0]) + hex2bin(byte_pack[1]);

	    	if(!check_package(bits, package_cnt, package_counter))
	    	{
	    		cout << "Invalid " << package_counter << " package!" << endl;
	    		return -1;
	    	} else
	    	{
	    		for(int i = 0; i < bits.length(); i ++)
	    		{
	    			data.package[package_counter][i] = bits[i] == '1';
	    		}
	    	}

	    	package_counter ++;
	    	byte_pack = "";
	    }
	}
	input.close();

	print_bits_table(data);
	cout << "Correct!" << endl;

	return 0;
}