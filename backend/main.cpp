#include <iostream>
#include <string>
#include <memory>
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    // 1. SERVE THE FRONTEND: Tell the C++ server where your HTML files are
    // This assumes you run the executable from inside the 'backend' folder
    svr.set_mount_point("/", "../frontend");

    // 2. CREATE THE API ENDPOINT: This is what your JavaScript connects to
    svr.Get(R"(/api/patient/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        
        // Extract the patient ID from the URL (e.g., /api/patient/224057231)
        std::string studentId = req.matches[1];
        
        // --- YOUR C++ LOGIC GOES HERE ---
        // (Instead of a hardcoded JSON, you would query your SQLite database here)
        
        json dashboardData;
        dashboardData["patientId"] = studentId;
        dashboardData["firstName"] = "Khethelo";
        dashboardData["appointment"]["status"] = "Confirmed";
        dashboardData["appointment"]["date"] = "Tue, 22 Sep";
        dashboardData["appointment"]["time"] = "10:30 - 11:00";
        dashboardData["appointment"]["type"] = "General medicine";
        dashboardData["appointment"]["doctor"] = "Dr. Mashazi";
        dashboardData["appointment"]["room"] = "Room 3";
        
        // Send the JSON response back to the JavaScript frontend
        res.set_content(dashboardData.dump(), "application/json");
    });

    // 3. START THE SERVER
    std::cout << "Starting Clinic Server..." << std::endl;
    std::cout << "Open your browser and go to: http://localhost:8080/patient_dashboard.html" << std::endl;
    
    svr.listen("localhost", 8080);

    return 0;
}