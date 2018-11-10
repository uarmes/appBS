#include "Conversion.h"

// wyodrebnienie nazwy pliku lub formatu, moze nie zadzialac gdy w sciezce znajda sie nazwy folderow z kropka
// (mozna by uzyc np. biblioteki boost, ale nie wiedzialem czy jest dopuszczalna)
string Conversion::slice_path(string path, int type)
{
	// wyodrebnienie nazwy pliku
	if (type == 0)
		return path.substr(0, path.find_last_of("."));
	// wydorebnienie formatu
	else if (type == 1)
		return path.substr(path.find_last_of(".") + 1);
	else // miejsce na inne opcje "slicowania"
		return NULL;
}

