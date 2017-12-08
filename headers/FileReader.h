#ifndef FILEREADER_H_
#define FILEREADER_H_
#include <string>
using namespace std;

/*
 * A class that reads IP and port information from a file and returns it.
 */
class FileReader {
public:
	FileReader(string target_file);
	virtual ~FileReader();
	int* read();
	char* ExtractIP(int* data);
	int ExtractPort(int* data);
private:
	int ParseInt(int i, int cin[]);
	int IntConverter(char* c);
	string file_name;
};

#endif /* FILEREADER_H_ */
