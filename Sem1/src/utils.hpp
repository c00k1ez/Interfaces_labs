#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>


struct DataBunch
{
	std::vector< std::vector<bool> > package;
	DataBunch();
};

void hemming_code(std::vector<bool> &bits);

const std::string byte2hex(std::string c);

std::string bin2hex(const std::vector<bool> &bits);

void print_bits_table(const DataBunch &data);

void generate_package(DataBunch &data, const std::vector<bool> &bits);

void write_to_file(const DataBunch &data, const std::string &filename);

void read_data(DataBunch &data, const std::string &filename);

bool check_package(const std::string &bits, std::vector<char> &package_cnt, int real_id);

std::string hex2bin(char c);

class ArgumentParser
{
public:
	ArgumentParser(int argc, char *argv[]);
	bool haveArgument(std::string arg_name);
	std::string getArgument(std::string arg_name);
private:
	std::vector< std::pair<std::string, std::string> > args;

};

#endif