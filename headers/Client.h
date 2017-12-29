#ifndef CLIENT_H_
#define CLIENT_H_
/*
 * A client used to send and recieve information to and from a server object.
 */
class Client {
public:
	Client(const char *serverIP, int serverPort);
	virtual ~Client();
	void connectToServer();
	int* GetMove();
	void SendMove(int x, int y);
	char** listGames(const char* command);
	int passSimpleCommand(const char* command);
private:
	void writeCommand(const char* command, int length);
	int commandLength(const char* command);
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* CLIENT_H_ */
