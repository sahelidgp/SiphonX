#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }

    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        return 1;
    }

    string msg = "Hello from client";

    int sent = send(sock, msg.c_str(), msg.size(), 0);
    cout << "Bytes sent = " << sent << endl;

    char buffer[1024] = {0};

    int bytes = read(sock, buffer, sizeof(buffer));

    cout << "Bytes received = " << bytes << endl;

    if (bytes >= 0)
        cout << "Server says: " << buffer << endl;
    else
        perror("read");

    close(sock);

    return 0;
}