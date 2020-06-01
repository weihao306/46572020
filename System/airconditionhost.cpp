#include "AirConditionHost.h"

AirConditionHost::AirConditionHost(QObject *parent):
	QObject(parent)
{
}

AirConditionHost::~AirConditionHost() {
	delete server;
}

void AirConditionHost::PowerOn() {
	server = new QTcpServer();
	CreatChartController();
	CreateMonitor();
	CreateSchduleController();
	CreateWaitList();
	CreateServiceList();
	qDebug()<<"请输入ManagerClient的端口：";
	QTextStream input(stdin);
	quint16 port;
	input >> port;
	connect(server, SIGNAL(newConnection()),
			this, SLOT(managerConnectHandle()));
	if(!server->listen(QHostAddress::Any, port))
	{
		qDebug()<<"服务器监听失败";
		return;
	}
	else
	{
		qDebug()<<"开始等待管理员";
	}
}

void AirConditionHost::managerConnectHandle() {
	qDebug()<<"管理员客户端已连接";
	QTcpSocket *managerSocket = server->nextPendingConnection();
	chartConstroller->setSocket(managerSocket);
	delete server;
	server = new QTcpServer();
	connect(server, SIGNAL(newConnection()), this, SLOT(guestConnectHndle()));
}

void AirConditionHost::guestConnectHndle(){
	qDebug()<<"有顾客客户端连接";
}

void AirConditionHost::CreatChartController() {
	chartConstroller = new ChartController();
}

void AirConditionHost::CreateMonitor(){
	monitor = new Monitor();
}

void AirConditionHost::CreateSchduleController(){
	scheduleController = new ScheduleController();
}

void AirConditionHost::CreateWaitList(){
	waitList = new WaitList();
	waitList->Initial();
}

void AirConditionHost::CreateServiceList(){
	serviceList = new ServiceList();
	serviceList->Initial();
}
