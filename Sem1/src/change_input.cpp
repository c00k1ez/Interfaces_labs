#include <iostream>
#include <exception>
#include "utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc != 3)
	{
		cout << "Invalid args count.\nUse Command ./change_input -f [FILE_NAME]." << endl;
		return -1;
	}

	ArgumentParser parser = ArgumentParser(argc, argv);

	if(!parser.haveArgument("-f"))
	{
		cout << "Invalid arguments.\nUse Command ./change_input -f [FILE_NAME]." << endl;
		return -2;
	}

	DataBunch data;

	read_data(data, parser.getArgument("-f"));

	print_bits_table(data);

	cout << "-------------------" << endl;

	while(1)
	{
		cout << "Do you wanna change smth? (y/n)" << endl;
		string ans;
		while(ans != "y" && ans != "n")
		{
			cin >> ans;
			if(ans != "y" && ans != "n") cout << "invalid answer." << endl;
		}
		if(ans == "n") break;
		cout << "Package number[0-3]:" << endl;
		int pack_number;
		while(1)
		{
			cin >> ans;
			try
			{
				pack_number = stoi(ans);
			} catch(invalid_argument)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			if(pack_number > 3 || pack_number < 0)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			break;
		}
		
		cout << "Bit to change [0-7]:" << endl;
		int bit_number;
		while(1)
		{
			cin >> ans;
			try
			{
				bit_number = stoi(ans);
			} catch(invalid_argument)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			if(bit_number > 7 || bit_number < 0)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			break;
		}

		cout << "New bit[0-1]:" << endl;
		int new_bit;
		while(1)
		{
			cin >> ans;
			try
			{
				new_bit = stoi(ans);
			} catch(invalid_argument)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			if(new_bit > 1 || new_bit < 0)
			{
				cout << "Invalid number." << endl;
				continue;
			}
			break;
		}

		data.package[pack_number][bit_number] = new_bit == 1;

	}
	cout << "-------------------" << endl;
	print_bits_table(data);
	write_to_file(data, parser.getArgument("-f"));
	return 0;

}
