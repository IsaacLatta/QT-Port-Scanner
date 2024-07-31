#include "QtPortScanner.h"


void QtPortScanner::updateOpenPorts(int port, std::string service)
{
    std::lock_guard <std::mutex> lock(openPortsMutex);
    openPorts[port] = service;
}

void QtPortScanner::updateClosedPorts(int port)
{
    std::lock_guard <std::mutex> lock(closedPortsMutex);
    closedPorts.push_back(port);
}

std::string QtPortScanner::getService(std::string& banner)
{
    std::vector <std::string> services =
    {
    "SSH", "FTP", "HTTP", "HTTPS", "SMTP", "TELNET", "IMAP", "POP3",
    "DNS", "MYSQL", "POSTGRESQL", "RDP", "VNC", "SIP", "LDAP", "NTP",
    "SNMP", "SMB", "RPC", "NETBIOS", "NFS", "CIFS", "TFTP", "TELNET"
    };

    for (int i = 0; i < services.size(); i++)
    {
        if (banner.find(services[i]) != std::string::npos)
            return services[i];
    }
    return "Unknown";
}

void QtPortScanner::sendRequest(QTcpSocket& socket, int port)
{
	std::string banner;
	std::string request = "GET / HTTP/1.1\r\nHost: " + Target_IP + "\r\n\r\n";

	socket.write(request.c_str());
	if (socket.waitForReadyRead(20000))
	{
		QByteArray response = socket.readAll();
		banner = response.toStdString();
		banner = getService(banner);
	}
	else
		banner = "Unknown";

	updateOpenPorts(port, banner);
}

void QtPortScanner::scanPort(int port)
{
    QTcpSocket socket;

    socket.connectToHost(Target_IP.c_str(), port);
    if (socket.waitForConnected(10000))
        sendRequest(socket, port);
    else
        updateClosedPorts(port);
    socket.close();
}

void QtPortScanner::scanRange(int start, int end)
{
    for (; start <= end; start++)
    {
        scanPort(start);
    }
}

void QtPortScanner::setTarget(std::string& IP)
{
    Target_IP = IP;
}

void QtPortScanner::scanTarget(int numPorts)
{
    int start, end;
    int THREAD_COUNT = 10;
    int remainder = numPorts % THREAD_COUNT;
    QFutureSynchronizer <void> synchronizer;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        start = i * (numPorts / THREAD_COUNT) + 1;
        end = (i + 1) * (numPorts / THREAD_COUNT);

        synchronizer.addFuture(QtConcurrent::run(&QtPortScanner::scanRange, start, end));
    }

    synchronizer.waitForFinished();
    isScanning = false;
}

std::vector <int> QtPortScanner::getClosedPorts()
{
    std::lock_guard <std::mutex> lock(closedPortsMutex);
    return closedPorts;
}

std::map<int, std::string> QtPortScanner::getResults()
{
    std::lock_guard <std::mutex> lock(openPortsMutex);
    return openPorts;
}



