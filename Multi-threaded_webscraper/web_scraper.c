#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_URLS 10
#define MAX_LENGTH 2048

// Structure to pass URL info to thread
typedef struct {
    int id;
    char url[MAX_LENGTH];
} ThreadArg;

// Function executed by each thread
void* fetch_url(void* arg) {
    ThreadArg* data = (ThreadArg*) arg;
    char filename[64];
    char command[MAX_LENGTH + 100];

    // Output file per thread
    snprintf(filename, sizeof(filename), "page_%d.txt", data->id);

    // Command using curl
    snprintf(command, sizeof(command), "curl -s -L \"%s\" -o %s", data->url, filename);

    printf("🌐 Thread %d fetching: %s\n", data->id, data->url);

    int status = system(command);

    if (status != 0) {
        printf("❌ Thread %d: Failed to fetch URL: %s\n", data->id, data->url);
    } else {
        printf("✅ Thread %d: Content saved to %s\n", data->id, filename);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_URLS];
    ThreadArg args[MAX_URLS];

    // 🔽 Change/add URLs here
    char* urls[] = {
        "https://google.com",
        "https://httpbin.org/html",
        "https://openai.com",
        "https://thisurldoesnotexist.example"  // will trigger error
    };

    int num_urls = sizeof(urls) / sizeof(urls[0]);

    // Start threads
    for (int i = 0; i < num_urls; i++) {
        args[i].id = i + 1;
        strncpy(args[i].url, urls[i], MAX_LENGTH - 1);
        if (pthread_create(&threads[i], NULL, fetch_url, &args[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // Wait for all threads
    for (int i = 0; i < num_urls; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n🎉 All fetch operations complete.\n");

    return 0;
}
