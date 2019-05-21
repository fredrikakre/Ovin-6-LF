#include "CourseCatalog.h"

void CourseCatalog::addCourse(const string& code, const string& name)
{
	// courses.insert({code, name}); // no overwrite
	courses[code] = name; // enables updating of names
}

void CourseCatalog::removeCourse(const string& code)
{
	// PPP chapter B.4.7. Every container has these operations
	courses.erase(code);
}

string CourseCatalog::getCourse(const string& code) const
{
	return courses.at(code);
}

ostream& operator<<(ostream& os, const CourseCatalog& cc)
{
	for (const auto& c : cc.courses)
		os << c.first << ", " << c.second << '\n';

	return os;
}

void CourseCatalog::saveToFile(const string& filename) const
{
	ofstream out{filename};

	if (!out)
		error("Kunne ikke lagre til " + filename);

	for (const auto& c : courses)
		out << c.first << ", " << c.second << '\n';
	// for-løkken over er akkurat den samme som i operator<<().
	// For å unngå å duplisere denne koden følgende metode brukes:
	// Det vil bli forelest litt senere i kurset og er relevant til eksamen.
	// Utskriftsoperatoren kan gjenbrukes, istedetfor å duplisere for-løkken.
	// Vi skriver ut "objektet selv":
	// this: en peker til objektet som saveToFile() kalles på.
	// *this: dereferering av this-pekeren. Det vil si: vi følger pekeren og velger "dette" objektet.
	// Du kan tenke på det som at *this er objektet du befinner deg i. Det gir kodelinjen:
	// out << *this; // betyr derfor at du kaller utskriftsoperatoren til _dette_ objektet.
}

void CourseCatalog::loadFromFile(const string& filename)
{
	ifstream in{filename};

	if (!in)
		error("Kunne ikke laste fra " + filename);

	// Empty courses before populating it with data read from file
	courses.clear();

	string line;
	while (getline(in, line)) {
		stringstream ss{line};

		string emneKode;
		string emneNavn;

		// Fetch the two parts of the line separated by comma ','
		getline(ss, emneKode, ',');
		getline(ss, emneNavn, ',');

		// Erase whitespace (1 character at beginning of string)
		emneNavn = emneNavn.substr(1);

		courses[emneKode] = emneNavn;
	}
}
