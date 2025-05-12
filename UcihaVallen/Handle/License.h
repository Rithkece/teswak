#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <experimental/filesystem>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctime>    
#include <iomanip>  
struct LicenseInfo {
    std::string key = "";
    time_t expirationDate = 0;
};
LicenseInfo getEmbeddedLicenseInfo() {
    LicenseInfo license;
    license.key = "G498E4SE4G11VB5SE4G";
    license.expirationDate = time(nullptr) + 30 * 24 * 3600;//30d
    return license;
}
class License_Validated {
public:
    static bool Time(const LicenseInfo& license) {
        time_t now = time(nullptr);
        return now < license.expirationDate;
    }
    static bool Key(const std::string& licenseKey, const LicenseInfo& license) {
        if (licenseKey == license.key) {
            std::string title = "Novaverse Application - Expires on: " + std::to_string((license.expirationDate - time(nullptr)) / (24 * 3600)) + " days";
            SetConsoleTitleA(title.c_str());
            return true;
        }
        return false;
    }
};
std::string readLicenseFromFile() {
    std::ifstream file("database/text/vago mondo.txt");
    if (file.is_open()) {
        std::string licenseKey;
        std::getline(file, licenseKey);
        file.close();
        return licenseKey;
    }
    else {
        std::cerr << "Unable to open license file." << std::endl;
        return "";
    }
}