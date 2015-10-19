#include <czmq.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Usage: %s address ups_name\n", argv[0]);
        exit(1);
    }
    zsock_t * sc = zsock_new(ZMQ_PUB);
    zsock_connect(sc, "tcp://%s:5560", argv[1]);
    bool state = 0;
    int timeout = 0;
    while(!zsys_interrupted) {
        if(timeout == 0) {
            state = !state;
            timeout = 5 + random()%20;
        }
        timeout--;
        if(state) {
            zstr_sendx(sc, argv[2], "ON", NULL);
            printf("%s ON\n", argv[2]);
        } else {
            zstr_sendx(sc, argv[2], "OFF", NULL);
            printf("%s OFF\n", argv[2]);
        }
        sleep(1);
    }
    zsock_destroy(&sc);
}
