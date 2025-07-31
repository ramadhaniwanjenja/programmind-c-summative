# Multi-threaded Web Scraper 🕷️

A parallel web content fetcher using POSIX threads to download multiple URLs simultaneously.

## Features
- **Parallel Processing**: Concurrent URL fetching using pthreads
- **Multi-threading**: Each URL processed in separate thread
- **File Output**: Individual output files per thread (`page_1.txt`, `page_2.txt`, etc.)
- **Error Handling**: Graceful handling of unreachable URLs
- **cURL Integration**: Uses system cURL for HTTP requests

## Prerequisites
```bash
# Install required dependencies
sudo apt-get install curl
sudo apt-get install build-essential
```

## Compilation & Usage
```bash
gcc -o web_scraper web_scraper.c -lpthread
./web_scraper
```

## Default URLs
The program fetches from these URLs by default:
- `https://google.com`
- `https://httpbin.org/html`
- `https://openai.com`
- `https://thisurldoesnotexist.example` (demonstrates error handling)

## Customization
Modify the `urls[]` array in `main()` to scrape different websites:
```c
char* urls[] = {
    "https://your-website.com",
    "https://another-site.org",
    // Add more URLs here
};
```

## Output Files
- **Format**: `page_N.txt` where N is the thread ID
- **Content**: Raw HTML content from each URL
- **Location**: Current working directory

## Thread Structure
```c
typedef struct {
    int id;           // Thread identifier
    char url[2048];   // Target URL
} ThreadArg;
```

## Sample Output
```
🌐 Thread 1 fetching: https://google.com
🌐 Thread 2 fetching: https://httpbin.org/html
✅ Thread 1: Content saved to page_1.txt
❌ Thread 4: Failed to fetch URL: https://thisurldoesnotexist.example
🎉 All fetch operations complete.
```

## Technical Highlights
- **POSIX Threads**: `pthread_create()` and `pthread_join()`
- **Concurrent Execution**: No thread synchronization required
- **System Calls**: Integration with external cURL command
- **Error Recovery**: Individual thread failures don't affect others