#include <curl/curl.h>
#include <iostream>
#include <string>
#include <map>
#include "json.hpp"
#include <ctime>
#include <sstream>

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

EnergyData fetch_hour_data(int lookForwardHours) {
    std::string base_url = "https://api.spot-hinta.fi";
    std::string endpoint = "/JustNow?lookForwardHours=" + std::to_string(lookForwardHours) + "&isHtmlRequest=true";
    std::string url = base_url + endpoint;

    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    EnergyData data;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        json j = json::parse(readBuffer);
        data.PriceWithTax = j["PriceWithTax"];
        if (j["Rank"].is_number()) {
            data.Rank = std::to_string(j["Rank"].get<int>());
        } else if (j["Rank"].is_string()) {
            data.Rank = j["Rank"];
        }
        data.DateTime = j["DateTime"];
    }
    return data;
}

int main() {
    int next_hours = 2;
    std::map<std::string, std::map<std::string, std::string>> energy_prices;

    for(int i = 0; i <= next_hours; i++) {
        EnergyData data = fetch_hour_data(i);
        double price = data.PriceWithTax * 100;

        // Parse DateTime
        std::tm tm = {};
        std::istringstream ss(data.DateTime);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
        char buffer[6];
        std::strftime(buffer, sizeof(buffer), "%H:%M", &tm);
        std::string time_str(buffer);

        energy_prices["Hour " + std::to_string(i)] = { {"Price", std::to_string(price)}, {"Time", time_str} };
    }

    for(auto& pair : energy_prices) {
        auto& details = pair.second;
        std::cout << "Price at " << details["Time"] << ": " << details["Price"] << " snt/kWh\n";
    }

    return 0;
}