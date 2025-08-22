#include <iostream>
#include <string>
#include <map>
#include <WiFi.h>

// IoT Device Tracker Class
class IoTDeviceTracker {
public:
    IoTDeviceTracker(const char* ssid, const char* password);
    void addDevice(const std::string& deviceId, const std::string& deviceName);
    void updateDeviceLocation(const std::string& deviceId, const std::string& location);
    void printDeviceLocations();

private:
    WiFiClient client;
    std::map<std::string, std::string> devices;
};

IoTDeviceTracker::IoTDeviceTracker(const char* ssid, const char* password) {
    // Initialize WiFi connection
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void IoTDeviceTracker::addDevice(const std::string& deviceId, const std::string& deviceName) {
    devices[deviceId] = deviceName;
    Serial.println("Added device: " + deviceId + " - " + deviceName);
}

void IoTDeviceTracker::updateDeviceLocation(const std::string& deviceId, const std::string& location) {
    if (devices.find(deviceId) != devices.end()) {
        devices[deviceId] = location;
        Serial.println("Updated location for device: " + deviceId + " - " + location);
    } else {
        Serial.println("Device not found: " + deviceId);
    }
}

void IoTDeviceTracker::printDeviceLocations() {
    Serial.println("Device Locations:");
    for (auto& device : devices) {
        Serial.println(device.first + " - " + device.second);
    }
}

int main() {
    IoTDeviceTracker tracker("your_wifi_ssid", "your_wifi_password");

    tracker.addDevice("DEV001", "Smart Bulb");
    tracker.addDevice("DEV002", "Smart Thermostat");
    tracker.updateDeviceLocation("DEV001", "Living Room");
    tracker.updateDeviceLocation("DEV002", "Bedroom");
    tracker.printDeviceLocations();

    return 0;
}