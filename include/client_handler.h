#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <vector>
#include <mutex>

void handle_client(int client_socket, std::vector<int>& clients, std::mutex& clients_mutex);

#endif // CLIENT_HANDLER_H
