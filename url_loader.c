#include "url_loader.h"
#include "logger.h"

#include <curl/curl.h>

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    StringBuffer *sb = (StringBuffer*) userp;

    string_buffer_write(sb, contents, realsize);

    return realsize;
}

bool get_web_page(const char* url, StringBuffer* response ) {
    bool ret = false;
    CURLcode res;
    CURL *curl = curl_easy_init();
    char log_buffer[100];

    if (curl) {
        struct curl_slist *headers = NULL ;
        headers = curl_slist_append(headers, "Accept: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L); // Disable progress
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); /* send all data to this function  */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) response); // we pass our 'sb' struct to the callback function

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res == CURLE_OK) {
            sprintf(log_buffer, "get_web_page() read %lu bytes.", (long)response->size);
            add_to_log(log_buffer, DUMP);
            ret = true;
        } else {
            sprintf(log_buffer, "get_web_page() failed: %s",
                    curl_easy_strerror(res));
            add_to_log(log_buffer, ERROR);
        }
        curl_easy_cleanup(curl);
    }
    return ret;
}

static size_t ReadMemoryCallback(void *ptr, size_t size, size_t nmemb, void *userp)
{
    StringBuffer *sb = (StringBuffer*) userp;
    size_t realsize = size * nmemb;
    size_t bytes_read = string_buffer_read(sb, (char*)ptr, realsize);
    return bytes_read;
}

bool post_web_page(const char* url, StringBuffer* request, StringBuffer* response ) {
    bool ret = false;
    CURLcode res;
    CURL *curl = curl_easy_init();
    char log_buffer[100];

    if (curl) {
        struct curl_slist *headers = NULL ;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L); // Disable progress
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);        
        curl_easy_setopt(curl, CURLOPT_READDATA, (void *)request);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) response);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (curl_off_t)request->size);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        
        /* Check for errors */
        if (res == CURLE_OK) {
            sprintf(log_buffer, "post_web_page() read %lu bytes.", (long)response->size);
            add_to_log(log_buffer, DUMP);
            ret = true;
        } else {
            sprintf(log_buffer, "post_web_page() failed: %s",
                    curl_easy_strerror(res));
            add_to_log(log_buffer, ERROR);
        }
        curl_easy_cleanup(curl);
    }
    return ret;
}