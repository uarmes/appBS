#pragma once
#include "Conversion.h"

// klasa dziedziczaca po Conversion, implementująca metodą convert()
class XML_to_TXT :
	public Conversion
{
public:
	XML_to_TXT(string _path);
	~XML_to_TXT() {};
	void convert();
};
