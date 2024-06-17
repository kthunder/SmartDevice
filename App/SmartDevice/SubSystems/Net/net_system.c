#include "net_system.h"

#define ESP_DEFAULT_TIMEOUT     10

NetDevice* g_NetDeviceList = NULL;

static int Esp8266Init(NetDevice * pNetDevice)
{
    ATInterfaceInit();

    ATCommandSend("AT+CWMODE=3", ESP_DEFAULT_TIMEOUT);
    ATCommandSend("AT+CIPMUX=0", ESP_DEFAULT_TIMEOUT);

    return 0;
}

static int Esp8266Connect(NetDevice * pNetDevice, int SSID, char *password)
{
    char cmd[100];

    sprintf(cmd, "AT+CWJAP=\"%s\", \"%s\"",SSID, password);

    return ATCommandSend(cmd, ESP_DEFAULT_TIMEOUT);
}

static void Esp8266DisConnect(NetDevice * pNetDevice)
{
    return ATCommandClose("AT+CIPCLOSE", ESP_DEFAULT_TIMEOUT);
}

static int Esp8266Send(NetDevice * pNetDevice, char *type, char *pDestIp, int iDestPort, unsigned char *data, int len)
{
    return 0;
}

static int Esp8266Recevice(NetDevice * pNetDevice, char *type, int iLocalPort, char *pSrcIp, unsigned char *data, int *pLen, int timeout)
{
    return ATDataReceive(pNetDevice, data, pLen, timeout);
}


static NetDevice g_Esp8266NetDevice=
{
    .name = "Esp8266",
    .ip = {0,0,0,0},
    .mac = {0,0,0,0,0,0},
    .Init = Esp8266Init,
    .Connect = Esp8266Connect,
    .Send = Esp8266Send,
    .Receive = Esp8266Recevice
};

static void NetDeviceRegister(NetDevice* netDevice)
{
    if (g_NetDeviceList == NULL)
    {
        g_NetDeviceList = netDevice;
    }else
    {
        NetDevice* tmp = g_NetDeviceList;
        while (tmp->next!=NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = netDevice;
    }
}

void Add8266oNetDevice()
{
    NetDeviceRegister(&g_Esp8266NetDevice);
}

void InitNetDevices()
{
    NetDevice* tmp = g_NetDeviceList;

    while (tmp !=NULL)
    {
        tmp->Init(tmp);
        tmp = tmp ->next;
    }
}

