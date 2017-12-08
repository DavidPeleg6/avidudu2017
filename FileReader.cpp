#include "headers/FileReader.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;
#define IP_PARTS 4
#define IP_PART_SIZE 3
#define BIGGEST_PORT_SIZE 5
#define ANS 48 /* Ascii Number Spot */
/*
 * Constructor, makes a new file reader.
 * @param target_file - the file to be read by the reader.
 */
FileReader::FileReader(string target_file) {
	file_name = target_file;
}
/*
 * Destructor, does nothing.
 */
FileReader::~FileReader() { }
/*
 * This function reads the file and returns a pointer referencing:
 * ip ip ip ip port
 * 0  1  2  3  4
 * It expects the file to have the format:
 * ip.ip.ip.ip:port
 * @return a pointer to the data listed above.
 */
int* FileReader::read() {
	ifstream reader;
	unsigned char* ip = (unsigned char*)calloc(IP_PARTS, sizeof(unsigned char));
	char* port = (char*)calloc(BIGGEST_PORT_SIZE, sizeof(char));
	int* final = (int*)calloc(IP_PARTS + 1, sizeof(int));
	int p = -1, j = 0, i = 1;
	int cin[IP_PART_SIZE + 1] = {0, 0, 0, 0};
	char c;
	reader.open(file_name.c_str());
	if (!reader) {
		/* file failed to open */
		return 0;
	}
	while (reader >> c) {
		switch (c) {
		case '.':
			cin[0] = ParseInt(i, cin);
			i = 1;
			if (IP_PARTS < j || cin[0] == -1) {
				/* error */
				return 0;
			}
			ip[j++] = cin[0];
			break;
		case ':':
			p = 0;
			cin[0] = ParseInt(i, cin);
			i = 1;
			if (IP_PARTS < j || cin[0] == -1) {
				/* error */
				return 0;
			}
			ip[j++] = cin[0];
			break;
		default:
			if (p == -1) {
				if (IP_PART_SIZE < i) {
					return 0;
				}
				cin[i++] = c;
			} else {
				port[p++] = c;
			}
			break;
		}
	}
	for (int o = 0; o < IP_PARTS; o++) {
		final[o] = ip[o];
	}
	final[IP_PARTS] = IntConverter(port);
	free(ip);
	free(port);
	reader.close();
	return final;
}
/*
 * Parses the ip address to an integer.
 * @param i - the length of the input.
 * @param cin[] - an array containing the input.
 * @return an integer version of the input.
 */
int FileReader::ParseInt(int i, int cin[]) {
	switch(i) {
	case 2:
		return (cin[1] - ANS);
		break;
	case 3:
		return ((cin[1] - ANS) * 10) + (cin[2] - ANS);
	break;
		case 4:
		return ((cin[1] - ANS) * 100) + ((cin[2] - ANS) * 10) + (cin[3] - ANS);
		break;
	default:
		/* error */
		return -1;
	}
}
/*
 * Converts the input string into an integer.
 * DOES NOT HANDLE EXCEPTIONS, INVALID INPUTS WILL CASUSE ISSUES.
 * @param c - input string.
 * @return the input but as an integer.
 */
int FileReader::IntConverter(char* c) {
	stringstream str;
	int integer;
	str << c;
	str >> integer;
	return integer;
}
/*
 * Takes the output from the read function
 * as input and returns the ip adress as a string.
 * @param data - the output from the read() function.
 * @return a string representation of the ip adress.
 */
char* FileReader::ExtractIP(int* data) {
	int i = 0;
	char* s = (char*)calloc(20, sizeof(char));
	for (int j = 0; j < IP_PARTS; j++) {
		if (data[j] / 100 != 0) {
			s[i++] = (data[j] / 100) + ANS;
		}
		if ((data[j] % 100) / 10 != 0) {
			s[i++] = ((data[j] % 100) / 10) + ANS;
		}
		s[i++] = (data[j] % 10) + ANS;
		if (j < IP_PARTS - 1) {
			s[i++] = '.';
		}
	}
	char* rs = (char*)calloc(i, sizeof(char));
	for (int j = 0; j < i; j++) {
		rs[j] = s[j];
	}
	free(s);
	return rs;
}
/*
 * Extracts the port number from the data.
 * @param data - the data to have the port number extracted from.
 * @return the port number as an integer.
 */
int FileReader::ExtractPort(int* data) {
	return data[IP_PARTS];
}
