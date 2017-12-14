#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// this is our proto of foo
#include "proto/foo.pb.h"

int main(int argc, char **argv)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr);
    addr.sin_port = htons(5555);

    // initialise a foo and set some properties
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    prototest::Foo foo;
    foo.set_id(4);
    foo.set_bar("narf");

    // serialise to string, this one is obvious ; )
    std::string buf;
    foo.SerializeToString(&buf);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int check = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (check >= 0){
      printf("Connected \n");
    }
    else{
      printf("Failed to connect \n");
      return -1;
    }
    for(int i=0 ; i<5 ; i++){
      send(sock, buf.data(), strlen(buf.c_str()), 0);
      char buf_incoming[256];

      int size = recv(sock, buf_incoming, sizeof(buf_incoming), 0);
      printf("i = %d, Bytes Received: \"%d\" | Message: %s",i, size, buf_incoming);
    }
    close(sock);
    return 0;
}
