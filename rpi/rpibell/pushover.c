//
// Created by Roman Kirillov on 30/08/15.
//

#include <curl/curl.h>

#include "pushover.h"
#include "pushover_api_constants.h"

const char PUSHOVER_JSONRPC_URL[] = "https://api.pushover.net/1/messages.json";
static char PUSHOVER_MESSAGE[1024];

int send_pushover_message() {
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, PUSHOVER_JSONRPC_URL);

    sprintf(PUSHOVER_MESSAGE,
            "token=%s&user=%s&message=Hello",
            PUSHOVER_API_TOKEN,
            PUSHOVER_USER_KEY);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PUSHOVER_MESSAGE);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr,
                "Failed to post message to PushOver: %s\n",
                curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
}
