#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>
#include <mutex>

class Server {
public:
    Server(int port);
    ~Server();
    void start();

private:
    int server_socket;
    int port;
    std::vector<int> clients;
    std::mutex clients_mutex;

    void accept_clients();
    void broadcast(const char* message, int sender_socket);
};

#endif // SERVER_H
