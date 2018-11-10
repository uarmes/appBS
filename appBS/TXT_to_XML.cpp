#include "TXT_to_XML.h"
#include <iostream>

TXT_to_XML::TXT_to_XML(string _path)
{
	path = _path;
}

// metoda konwertujaca txt do xml
void TXT_to_XML::convert()
{
	file_in.open(path, ios::in);

	// sprawdzenie poprawnosci otwarcia pliku wejsciowego (obsluga wyjatku) - jednoczesnie sprawdza czy plik istnieje
	if (file_in.good() == true)
	{
		// stworzenie pliku wyjsciowego
		file_out.open(slice_path(path, 0) + ".xml", ios::out);

		// poczatek tworzenia szablonu xml
		file_out << "<testy>" << endl;

		// petla wczytujaca dane z pliku az do osiagniecia konca danych
		while (file_in >> id >> time >> result)
		{
			// szablon xml
			file_out << "<test>" << endl
				<< "<id>" << id << "</id>" << endl
				<< "<time>" << time << "</time>" << endl
				<< "<result>" << result << "</result>" << endl
				<< "</test>" << endl;
		}
		file_out << "</testy>";

		cout << "konwersja do pliku xml powiodla sie" << endl;

		file_in.close();
		file_out.close();
	}
	// informacja w przypadku niepoprawnego otwarcia pliku lub braku pliku
	else
		cout << "Wystapil blad, sprawdz sciezke lub czy plik w ogole istnieje!" << endl;
}
