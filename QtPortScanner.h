#ifndef QTPORTSCANNER
#define QTPORTSCANNER

#include <QtCore/QCoreApplication>
#include <QFutureSynchronizer>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QTcpSocket>

/*
class QCoreApplication;
class QTcpSocket;
class QByteArray;
class QtConcurrent;
class QFuture;
class QFutureSynchronizer;
class QtPortScannerImpl;
*/

#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <memory>

class QtPortScanner
{
private:
	std::string Target_IP;
	std::mutex openPortsMutex;
	std::mutex closedPortsMutex;
	std::atomic <bool> isScanning;
	std::vector <int> closedPorts;
	std::map <int, std::string> openPorts;
	
	void updateOpenPorts(int port, std::string service);
	void updateClosedPorts(int port);
	std::string getService(std::string& banner);
	void sendRequest(QTcpSocket& socket, int port);
	void scanPort(int port);
	void scanRange(int start, int end);
	
public:
	void setTarget(std::string& IP);
	void scanTarget(int numPorts);
	std::vector <int> getClosedPorts();
	std::map<int, std::string> getResults();

};
#endif

