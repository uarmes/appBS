#pragma once
#include <fstream>
#include <string>
using namespace std;

class Conversion
{
public:
	Conversion() = default;
	virtual ~Conversion() {};
	static string slice_path(string path, int type);
	virtual void convert() = 0;
protected:
	fstream file_in;
	fstream file_out;
	string path;
};
