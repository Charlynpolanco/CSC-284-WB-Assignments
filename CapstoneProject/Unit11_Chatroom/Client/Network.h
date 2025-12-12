#pragma once
#include <string>

int connectToServer(const std::string& ip, int port);
int sendMessage(int sock, const std::string& msg);
int receiveMessage(int sock, char* buffer, int bufferSize);
void shutdownNetworking();