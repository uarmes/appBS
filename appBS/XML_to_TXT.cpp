#include "XML_to_TXT.h"
#include <rapidxml/rapidxml.hpp>
#include <sstream>
#include <iostream>

using namespace rapidxml;

XML_to_TXT::XML_to_TXT(string _path)
{
	path = _path;
}

// metoda konwertuj¹ca xml do txt
void XML_to_TXT::convert()
{
	file_in.open(path, ios::in);
	if (file_in.good() == true)
	{
		// stworzenie pliku wyjsciowego
		file_out.open(slice_path(path, 0) + ".txt", ios::out);

		// sparowanie pliku xml z bibliotek¹ rapidXML
		try {
			xml_document<> doc;
			stringstream buffer;
			buffer << file_in.rdbuf();
			string content(buffer.str());
			doc.parse<0>(&content[0]);

			// okreslenie "korzenia" - glownego znacznika pliku xml -> <testy>
			xml_node<> * root_node;
			root_node = doc.first_node();

			// petla po "dzieciach" glownego znacznika czyli po <test>
			for (xml_node<> *pNode = root_node->first_node(); pNode; pNode = pNode->next_sibling())
			{
				int counter = 0; // licznik, potrzebny do wyeliminowania spacji po wpisaniu wartosci w ostatniej kolumnie

								 // petla po "dzieciach" znacznika <test> czyli <id>, <time>, <result>
				for (xml_node<> *gNode = pNode->first_node(); gNode; gNode = gNode->next_sibling())
				{
					counter++;
					// odczytanie 3 znacznika (result) dopisanie spacji - separatora
					if (counter != 3)
						file_out << gNode->value() << ' ';
					// gdy petla dochodzi do trzeciego "dziecka", w linijce nie jest zapisywana spacja
					else
						file_out << gNode->value();
				}
				file_out << endl;
			}
			cout << "konwersja do pliku tekstowego powiodla sie" << endl;
		}

		catch (parse_error& e)
		{
			cerr << "blad w pliku XML: " << e.what() << endl;
		}
	}
	else
		cout << "Wystapil blad, sprawdz sciezke lub czy plik w ogole istnieje!" << endl;

	file_in.close();
	file_out.close();

}