#pragma once
#include "Conversion.h"

// klasa dziedziczaca po Conversion, implementuj�ca metod� convert()
class XML_to_TXT :
	public Conversion
{
public:
	XML_to_TXT(string _path);
	~XML_to_TXT() {};
	void convert();
};
