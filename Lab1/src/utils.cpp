#include "utils.hpp"
#include <iostream>
#include <utility>
#include <fstream>
#include <map>

using namespace std;


DataBunch::DataBunch()
{

	package = std::vector< std::vector<bool> >(4, std::vector<bool>(8, 0));

}


void hemming_code(vector<bool> &bits)
{
	/*
		|1|2|3|4|5|6
		------------
	1) 	 1 0 1			get current code
	2)	 0 0 1 0 0 1	add special bits to 1, 2, 4 positions
	3)	 1 0 1 1 0 1
	bits[0] = bits[2] ^ bits[4]
	bits[1] = bits[2] ^ bits[5]
	bits[3] = bits[4] ^ bits[5]
	*/
	if(bits.size() != 6)
	{
		cout << "bits.size have to be equal to 6" << endl;
		throw -1;
	}

	
	bits[5] = bits[2];
	bits[4] = bits[1];
	bits[2] = bits[0];
	bits[0] = 0;
	bits[1] = 0;

	bits[0] = bits[2] ^ bits[4];
	bits[1] = bits[2] ^ bits[5];
	bits[3] = bits[4] ^ bits[5];
	
}

const string byte2hex(string c)
{

        if(c == "0000") return "0";
        if(c == "0001") return "1";
        if(c == "0010") return "2";
        if(c == "0011") return "3";
        if(c == "0100") return "4";
        if(c == "0101") return "5";
        if(c == "0110") return "6";
        if(c == "0111") return "7";
        if(c == "1000") return "8";
        if(c == "1001") return "9";
        if(c == "1010") return "A";
        if(c == "1011") return "B";
        if(c == "1100") return "C";
        if(c == "1101") return "D";
        if(c == "1110") return "E";
        if(c == "1111") return "F";

}

string bin2hex(const vector<bool> &bits)
{

	string s_bits;
	for(int i = 0; i < bits.size(); i ++)
		s_bits += bits[i] == 1 ? "1" : "0";
	string result;
	result += byte2hex(s_bits.substr(0, 4));
	result += byte2hex(s_bits.substr(4, 4));
	return result;

}

void print_bits_table(const DataBunch &data)
{

	for(int i = 0; i < 4; i ++)
	{
		for(int j = 0; j < 8; j ++)
		{
			cout << data.package[i][j] << " ";
		}
		cout << " " << bin2hex(data.package[i]) << endl;
	}

}

void generate_package(DataBunch &data, const vector<bool> &bits)
{

	data.package[0][0] = 0; data.package[0][1] = 0;
	data.package[1][0] = 0; data.package[1][1] = 1;
	data.package[2][0] = 1; data.package[2][1] = 0;
	data.package[3][0] = 1; data.package[3][1] = 1;

	for(int i = 0; i < 4; i ++)
	{
		vector<bool> temp_vec(6, 0);
		
		for(int j = 0; j < 3; j ++)
		{
			temp_vec[j] = bits[j + i*3];
		}
		hemming_code(temp_vec);
		for(int j = 2; j < 8; j ++)
		{
			data.package[i][j] = temp_vec[j-2];
		}
	}

}

void write_to_file(const DataBunch &data, const string &filename)
{

	ofstream out_file;
  	out_file.open(filename);
  	for(int i = 0; i < 4; i ++)
  	{
  		out_file << bin2hex(data.package[i]);
  	}
  	out_file << endl;
  	out_file.close();

}

string hex2bin(char c)
{
        if(c == '0') return "0000";
        if(c == '1') return "0001";
        if(c == '2') return "0010";
        if(c == '3') return "0011";
        if(c == '4') return "0100";
        if(c == '5') return "0101";
        if(c == '6') return "0110";
        if(c == '7') return "0111";
        if(c == '8') return "1000";
        if(c == '9') return "1001";
        if(c == 'A') return "1010";
        if(c == 'B') return "1011";
        if(c == 'C') return "1100";
        if(c == 'D') return "1101";
        if(c == 'E') return "1110";
        if(c == 'F') return "1111";
}

void read_data(DataBunch &data, const std::string &filename)
{

	ifstream in_file;
  	in_file.open(filename);
  	string hex_code;
  	in_file >> hex_code;
  	in_file.close();
  	int data_cnt = 0;
  	for(int i = 1; i < hex_code.length(); i += 2)
  	{
  		string bytes;
  		bytes += hex2bin(hex_code[i-1]);
  		bytes += hex2bin(hex_code[i]);
  		for(int j = 0; j < 8; j++)
  		{
  			data.package[data_cnt][j] = bytes[j] == '1';
  		}
  		data_cnt ++;
  	}
  	

}

bool check_package(const string &bits, vector<char> &package_cnt, int real_id)
{

	bool result = true;

	map<string, int> num_map = {
		{"00", 0},
		{"01", 1},
		{"10", 2},
		{"11", 3}
	};

	int package_number = num_map[bits.substr(0, 2)];
	if(package_number < real_id) result = false;
	package_cnt[package_number] ++;
	if(package_cnt[package_number] > 1) result = false;

	vector<bool> v_bits = {bits[4]=='1', bits[6]=='1', bits[7]=='1', 0, 0, 0};
	hemming_code(v_bits);

	if((v_bits[0] != (bits[2]=='1')) || (v_bits[1] != (bits[3]=='1')) || (v_bits[3] != (bits[5]=='1')) )
	{
		result = false;
	}

	return result;

}

ArgumentParser::ArgumentParser(int argc, char *argv[])
{
	for(int i = 2; i < argc; i += 2)
	{
		string flag(argv[i-1]);
		string arg(argv[i]);
		args.push_back(make_pair(flag, arg));
	}
}

bool ArgumentParser::haveArgument(std::string arg_name)
{
	bool flag = false;
	for(int i = 0; i < args.size(); i ++)
	{
		if(args[i].first == arg_name) flag = true;
	}
	return flag;
}

string ArgumentParser::getArgument(std::string arg_name)
{
	for(int i = 0; i < args.size(); i ++)
	{
		if(args[i].first == arg_name) return args[i].second;
	}
	return "";
}