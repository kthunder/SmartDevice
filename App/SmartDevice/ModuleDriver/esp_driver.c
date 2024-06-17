#include "esp_driver.h"

#define AT_DEFAULT_TIMEOUT      10
static PTATInterfaceDevice g_ptATInterfaceDevice;

static int isReturnOk(char *res, int len)
{
    res[len]='\0';

    return strstr(res, "OK\r\n");
}

static int isReturnError(char *res, int len)
{
    res[len]='\0';

    return strstr(res, "ERROR\r\n");
}

int ATInterfaceInit(void)
{
    g_ptATInterfaceDevice = getATInterfaceDevice();
    g_ptATInterfaceDevice->Init(g_ptATInterfaceDevice);

    return 0;
}

int ATCommandSend(char *cmd, int iTimeoutMs)
{
    char buf[100];
    int i=0;
    int prev, now = 0;

    g_ptATInterfaceDevice->ClearRecvBuf(g_ptATInterfaceDevice);
    g_ptATInterfaceDevice->Write(g_ptATInterfaceDevice, cmd, strlen(cmd));
    g_ptATInterfaceDevice->Write(g_ptATInterfaceDevice, "\r\n", 2);

    /*等待数据返回结果*/
    prev = KAL_GetTime();
    while (iTimeoutMs)
    {
        if(g_ptATInterfaceDevice->ReadByte(g_ptATInterfaceDevice, &buf[i]) == 0)
        {
            if ((i!=0) && (buf[i-1]=='\r') && (buf[i]=='\n'))
            {
                if(isReturnOk(buf, i+1))
                    return RETURN_SUCCESS;
                else if(isReturnError(buf, i+1))
                    return RETURN_ERROR;
                else
                {
                    i=0;
                }
            }
            i++;
        }
        
        now = KAL_GetTime();
        if(now > prev)
        {
            iTimeoutMs--;
            prev = now;
        }
    }

    return TIMEOUT_ERROR;
}

int ATDataReceive(NetDevice * pNetDevice, unsigned char *data, int *pLen, int iTimeoutMs)
{
    /* +IPD,4,9:ASDFGHJ */
    char buf[100];
    int i,j=0;
    int prev, now, len = 0;

    AT_STATUS status = INIT_STATUS;

    prev = KAL_GetTime();
    while (iTimeoutMs)
    {
        if(g_ptATInterfaceDevice->ReadByte(g_ptATInterfaceDevice, &buf[i]) == 0)
        {
            switch (status)
            {
                case INIT_STATUS:
                {
                    buf[i+1]='\0';
                    if(strstr(buf,"+IPD,"))
                    {
                        status = LEN_STATUS;
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                    break;
                }
                case LEN_STATUS:
                {
                    if(buf[i] == ':')
                    {
                        for(j = 0; j < i; j++)
                        {
                            len = len * 10 + buf[j] - '0';
                        }
                        status = DATA_STATUS;
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                    break;
                }
                case DATA_STATUS:
                {
                    data[i]=buf[i];
                    i++;
                    if (i == len)
                    {
                        if (pLen != NULL)
                        {
                            *pLen = len;
                        }
                        return 0;
                    }
                    
                    break;
                }
                
            
            default:
                break;
            }
        }
        
        now = KAL_GetTime();
        if(now > prev)
        {
            iTimeoutMs--;
            prev = now;
        }
    }
}