#ifndef CLIENT_H_
#define CLIENT_H_

using namespace std;

class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	int sendExercise(int arg1, char op, int arg2);
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
