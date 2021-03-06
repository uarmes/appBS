#pragma once
#include "Conversion.h"

// klasa dziedziczaca po Conversion, implementująca metodą convert()
class TXT_to_XML :
	public Conversion
{
private:
	string id, time, result;
public:
	TXT_to_XML(string _path);
	~TXT_to_XML() {};
	void convert();
};
