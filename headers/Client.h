#ifndef CLIENT_H_
#define CLIENT_H_
/*
 * A client used to send and recieve information to and from a server object.
 */
class Client {
public:
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	int* GetMove();
	void SendMove(int x, int y, int color);
private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
