#include "headers/FileReader.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace std;
#define IP_PARTS 4
#define IP_PART_SIZE 3
#define BIGGEST_PORT_SIZE 5
#define ANS 48 /* Aacii Number Spot */
FileReader::FileReader(string target_file) {
	file_name = target_file;
}

FileReader::~FileReader() {
	// TODO Auto-generated destructor stub
}
/*
 * This function reads the file and returns a pointer referencing:
 * ip ip ip ip port
 * 0  1  2  3  4
 * It expects the file to have the format:
 * ip.ip.ip.ip:port
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
int FileReader::IntConverter(char* c) {
	stringstream str;
	int integer;
	str << c;
	str >> integer;
	return integer;
}
