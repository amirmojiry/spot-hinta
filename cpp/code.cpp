#include <curl/curl.h>
#include <iostream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

struct EnergyData {
    double PriceWithTax;
    std::string Rank;
    std::string DateTime;
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    std::string base_url = "https://api.spot-hinta.fi";
    int next_hours = 2;

    for(int i = 0; i <= next_hours; i++) {
        std::string endpoint = "/JustNow?lookForwardHours=" + std::to_string(i) + "&isHtmlRequest=true";
        std::string url = base_url + endpoint;

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            json j = json::parse(readBuffer);
            std::cout << j.dump() << std::endl;
        }
    }

    return 0;
}