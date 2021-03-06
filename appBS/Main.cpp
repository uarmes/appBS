#include <string>
#include "Conversion.h"
#include <iostream>
#include "TXT_to_XML.h"
#include "XML_to_TXT.h"
#include "Main.h"

using namespace std;

// metoda ktora realizuje konwersje w zaleznosci od wyslanego do niej obiektu
void Main::choose(Conversion *c)
{
	c->convert();
}

// funkcja obslugujaca cmd
void Main::start_process(char *argv[])
{
	if (argv[1] != NULL && argv[2] == NULL)
	{
		Conversion *wsk;
		string path = argv[1];
		string extension = Conversion::slice_path(path, 1);

		if (extension == "txt")
		{
			TXT_to_XML t2x(path);
			wsk = &t2x;
			choose(wsk);
		}
		else if (extension == "xml")
		{
			XML_to_TXT x2t(path);
			wsk = &x2t;
			choose(wsk);
		}
		else
			cout << "podano zly format pliku" << endl;
	}
	else
		cout << "niepoprawna skladnia!" << endl
		<< "prawidlowa postac: appBS nazwa_pliku.format" << endl;

}
//zakomentowac w przypadku potrzeby zrobienia testow googleTestBS
int main(int argc, char *argv[])
{
	Main m;
	m.start_process(argv);
	return 0;
}