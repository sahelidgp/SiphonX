#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {

    // 1. Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    // Optional: Allows immediate reuse of the port after restarting
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    // 2. Configure server address
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 3. Bind socket to IP and port
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    cout << "==================================" << endl;
    cout << "Server listening on port 8080..." << endl;
    cout << "Waiting for client..." << endl;
    cout << "==================================" << endl;

    // 5. Accept client connection
    socklen_t addrlen = sizeof(address);

    int client_socket = accept(server_fd,
                               (sockaddr*)&address,
                               &addrlen);

    if (client_socket < 0) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    cout << "Client connected!" << endl;

    // 6. Receive message
    char buffer[1024] = {0};

    int bytes_received = recv(client_socket,
                              buffer,
                              sizeof(buffer) - 1,
                              0);

    if (bytes_received < 0) {
        perror("recv");
        close(client_socket);
        close(server_fd);
        return 1;
    }

    buffer[bytes_received] = '\0';

    cout << "Bytes received : " << bytes_received << endl;
    cout << "Client says    : " << buffer << endl;

    // 7. Send response
    string response = "Hello from server";

    int bytes_sent = send(client_socket,
                          response.c_str(),
                          response.size(),
                          0);

    if (bytes_sent < 0) {
        perror("send");
    } else {
        cout << "Bytes sent     : " << bytes_sent << endl;
    }

    // 8. Close sockets
    close(client_socket);
    close(server_fd);

    cout << "Connection closed." << endl;

    return 0;
}