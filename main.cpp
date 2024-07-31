#include "QtPortScanner.h"
#include <iomanip>

void printResults(std::map <int, std::string> results, int closedPorts)
{
    // Print Output
    std::cout << "\033[94m[*] \033[97m" // Blue
        << std::left << std::setw(15) << "Port"
        << std::setw(10) << "Status"
        << std::setw(10) << "Service"
        << std::endl
        << std::setfill('-') << std::setw(40) << ""
        << std::setfill(' ') << std::endl;

    for (auto& result : results)
    {
        std::cout << "\033[92m[+] \033[97m" // Green
            << std::left << std::setw(15) << result.first
            << std::setw(10) << "Open"
            << std::setw(10) << result.second
            << std::endl;
    }

    std::cout << std::endl
        << "\033[92m[+] \033[97m" // Green
        << "Total Open Ports: " << results.size()
        << std::endl;

    std::cout << "\033[91m[-] \033[97m" // Red
        << "Total Closed/Filtered Ports: " << closedPorts
        << std::endl;
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QtPortScanner scanner;
    std::map<int, std::string> results;
    std::string target_ip;
    int ports;

    std::cout << "[*] Enter target IP: ";
    std::cin >> target_ip;
    std::cout << "[*] Enter ports to scan: ";
    std::cin >> ports;

    scanner.setTarget(target_ip);
    std::cout << "\033[94m[*] \033[97m";
    std::cout << "Scanning Target ... " << std::endl;
    scanner.scanTarget(ports);
    
    results = scanner.getResults();
    printResults(results, scanner.getClosedPorts().size());

    return a.exec(); // Trigger even loop
}

