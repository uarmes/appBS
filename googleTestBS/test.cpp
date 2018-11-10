#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING // flaga ograniczajaca ilosc warningow przy kompilacji
#include "../appBS/Main.h"
#include "../appBS/TXT_to_XML.h"
#include "../appBS/XML_to_TXT.h"
#include "../appBS/Conversion.h"
#include <gtest/gtest.h>
#include <stdio.h>

string data_before, data_after;
string original, converted;
Main m;
fstream file, file_template;
bool status;

// metoda sprawdzajaca zgodnosc miedzy plikiem wygenerowanym przez program
// a plikiem bedacym pozadanym wzorcowym szablonem
bool check_content(string path_conv, string path_template) {
	file.open(path_conv, ios::in);
	file_template.open(path_template, ios::in);
	// sprawdzenie istnienia plikow
	if (file.good() && file_template.good()) {
		// petla do konca pliku wzorcowego
		while (!file_template.eof())
		{
			getline(file, converted);
			getline(file_template, original);
			// jesli roznia sie linie obu plikow to false - brak zgodnosci
			if (converted != original) {
				status = false;
				break;
			}
			else
				status = true;
		}
	}
	else
	{
		status = false;
		cout << "brak pliku wzorcowego" << endl;
	}

	file.close();
	file_template.close();
	return status;
}

// grupa testujaca metode slice_path()
TEST(CheckThePathSlicing, InputMatched) {
	data_before = "dane.txt";
	data_after = "dane";
	EXPECT_EQ(data_after, Conversion::slice_path(data_before, 0));
}

// dla pokazania jednego failed testu
TEST(CheckThePathSlicing, InputNotMatched) {
	data_before = "daned.txt";
	data_after = "dane";
	EXPECT_EQ(data_after, Conversion::slice_path(data_before, 0));
}

TEST(CheckThePathSlicing, LongInputWithManyDots) {
	data_before = "abcdefgh.i.j.k.l.txt";
	data_after = "abcdefgh.i.j.k.l";
	EXPECT_EQ(data_after, Conversion::slice_path(data_before, 0));
}

// "wyciaga" format ze sciezki
TEST(CheckThePathSlicing, GetExtension) {
	data_before = "Dabcdefgh.i.j.k.l.txt";
	data_after = "txt";
	EXPECT_EQ(data_after, Conversion::slice_path(data_before, 1));
}

// grupa sprawdzajaca czy pliki tworza sie prawidlowo
TEST(CheckTheFileCreation, TXTinput) {
	// usuniecie pliku xml, by potem sprawdzic, czy aplikacja tworzy go przy podaniu txt
	if (remove("dane.xml") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	char *argv[3] = { "appBS","dane.txt",NULL };
	m.start_process(argv);
	file.open("dane.xml", ios::in);
	// sprawdzenie czy plik xml istnieje
	status = file.good();
	file.close();
	EXPECT_EQ(true, status);
}

TEST(CheckTheFileCreation, XMLinput) {
	// usuniecie pliku txt, by potem sprawdzic, czy aplikacja tworzy go przy podaniu xml
	if (remove("dane.txt") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	char *argv[3] = { "appBS","dane.xml",NULL };
	m.start_process(argv);
	file.open("dane.txt", ios::in);
	// sprawdzenie czy plik txt istnieje
	status = file.good();
	file.close();
	EXPECT_EQ(true, status);
}

// grupa sprawdzajaca czy zawartosc plikow zgadza sie z pozadana 
TEST(CheckTheFileContent, TXTinput) {
	TXT_to_XML t2x("dane.txt");
	t2x.convert();
	status = check_content("dane.xml", "szablon.xml");
	EXPECT_EQ(true, status);
}

TEST(CheckTheFileContent, XMLinput) {
	XML_to_TXT x2t("dane.xml");
	x2t.convert();
	status = check_content("dane.txt", "szablon.txt");
	EXPECT_EQ(true, status);
}
/* zakomentowane w celu prawid³owej kompilacji appBS
int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
*/
