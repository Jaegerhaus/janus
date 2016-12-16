#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <fcntl.h>

char frames[1000000];

const char* SEND_HOST = "localhost";
const int SEND_PORT = 9999;
const int SEND_TIMEOUT = 3;

char* sendFrames(const char* host, int portno, const char* data)
{
  int sock, n;
  struct sockaddr_in serv_addr;
  struct hostent* server;
  struct timeval tv;
  fd_set fdset;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    return "Error opening socket";

  fcntl(sock, F_SETFL, O_NONBLOCK);

  server = gethostbyname(host);
  if (NULL == server)
    return "Error host not found";

  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  bcopy((char*) server->h_addr,
        (char*) &serv_addr.sin_addr.s_addr,
        server->h_length);

  connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

  FD_ZERO(&fdset);
  FD_SET(sock, &fdset);
  tv.tv_sec = SEND_TIMEOUT;
  tv.tv_usec = 0;

  if (1 == select(sock + 1, NULL, &fdset, NULL, &tv))
  {
    int so_error;
    socklen_t len = sizeof so_error;

    getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

    if (so_error)
      return strerror(so_error);

    fcntl(sock, F_SETFL, 0);
    write(sock, data, strlen(data));
  }

  close(sock);

  return "OK";
}

void* sendFrames_thread(void* arg)
{
  const char* data = (char*) arg;
  sendFrames(SEND_HOST, SEND_PORT, data);
}

void RVExtension(char* output, int outputSize, const char* function)
{
  char* result = "";

  if (0 == strcmp(function, "chunk_end"))
  {
    pthread_t thread;
    pthread_create(&thread, NULL, sendFrames_thread, frames);
    result = "OK";
  }
  else if (0 == strcmp(function, "chunk_begin"))
  {
    strcpy(frames, "");
    result = "OK";
  }
  else if (frames)
  {
    strcat(frames, function);
    result = "OK";
  }

  strncpy(output, result, outputSize);

  return;
}

void test()
{
  char output[4096];
  RVExtension(output, 4096, "chunk_begin");
  RVExtension(output, 4096, "chunk_data 1 ");
  RVExtension(output, 4096, "chunk_data 2 ");
  RVExtension(output, 4096, "chunk_end");

  pthread_exit(NULL);
}

int main()
{
  test();
  return 0;
}
