#include "server.h"

int main() {
    Server server(12345); // Port number for the server
    server.start();
    return 0;
}
