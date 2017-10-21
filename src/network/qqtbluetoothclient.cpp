#include "qqtbluetoothclient.h"

#if defined(__WIN__) || defined(__WIN64__)
#include "qqtwin.h"
#elif defined(__LINUX__) || defined(__LINUX64__)
#include "qqtlinux.h"
#elif defined (__DARWIN__)
#include "qqtdarwin.h"
#endif
#include "qqtcore.h"

QQtBluetoothClient::QQtBluetoothClient(QBluetoothServiceInfo::Protocol socketType, QObject *parent) :
    QBluetoothSocket(socketType, parent)
{
    initSocket();
}

QQtBluetoothClient::QQtBluetoothClient(QObject *parent) : QBluetoothSocket(parent)
{
    initSocket();
}

void QQtBluetoothClient::initSocket()
{
    connect(this, SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
            this, SLOT(socketStateChanged(QBluetoothSocket::SocketState)) );
    // connected
    connect(this, SIGNAL(connected()),
            this, SLOT(socketConnected()) );
    // disconnected
    connect(this, SIGNAL(disconnected()),
            this, SLOT(socketDisconnect()) );
    // error
    connect(this, SIGNAL(error(QBluetoothSocket::SocketError)),
            this, SLOT(socketErrorOccured(QBluetoothSocket::SocketError)) );

    connect(this, SIGNAL(readyRead()),
            this, SLOT(readyReadData()));

    connect(this, SIGNAL(bytesWritten(qint64)),
            this, SLOT(updateProgress(qint64)));

    connect(this, SIGNAL(bytesWritten(qint64)),
            this, SIGNAL(signalUpdateProgress(qint64)));

    m_PORT = 0;
    m_protocol = nullptr;
}

void QQtBluetoothClient::installProtocol(QQTProtocol *stack)
{
    if(m_protocol)
        return;

    m_protocol = stack;
    connect(m_protocol, SIGNAL(write(const QByteArray&)),
            this, SLOT(write(const QByteArray&)));
}

void QQtBluetoothClient::uninstallProtocol(QQTProtocol *stack)
{
    if(!m_protocol)
        return;

    disconnect(m_protocol, SIGNAL(write(const QByteArray&)),
               this, SLOT(write(const QByteArray&)));
    m_protocol = NULL;
}

QQTProtocol *QQtBluetoothClient::installedProtocol()
{
    return m_protocol;
}

void QQtBluetoothClient::sendConnectMessage()
{
    pline() << isOpen() << state();

    if(!isOpen())
    {
        connectToSingelHost();
        return;
    }

    if(state() == ServiceLookupState ||
            state() == ConnectingState)
    {
        emit signalConnecting();
        return;
    }

    if(state() == ConnectedState)
        emit signalConnectSucc();

    return;
}


int QQtBluetoothClient::sendDisConnectFromHost()
{
    pline() << isOpen() << state();

    if(isOpen() )
    {
#if defined(__WIN__) || defined (__WIN64__)
        ;
#else
        shutdown(this->socketDescriptor(), SHUT_RDWR);
#endif
        disconnectFromService();
        close();
        emit signalDisConnectSucc();
    }

    return true;
}

/**
 * @brief QQtBluetoothClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtBluetoothClient::socketStateChanged(QBluetoothSocket::SocketState eSocketState)
{
    pline() << eSocketState;
    switch(eSocketState)
    {
    case ServiceLookupState:
    case ConnectingState:
        break;
    case ConnectedState:
        break;
    case ClosingState:
        break;
    case UnconnectedState:
        break;
    default:
        break;
    }
}

/**
 * @brief QQtBluetoothClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtBluetoothClient::socketErrorOccured(QBluetoothSocket::SocketError e)
{
    /*
     * 在错误状态下重新连接其他热点，直到确定连接类型，写入配置文件
     */
    pline() << e << errorString();
    switch(e)
    {
    case HostNotFoundError:
    default:
        emit signalConnectFail();
        break;
    }
}

/**
 * @brief QQtBluetoothClient::socketConnected
 * 功能接口
 */
void QQtBluetoothClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
}

/**
 * @brief QQtBluetoothClient::socketDisconnect
 * 功能接口
 */
void QQtBluetoothClient::socketDisconnect()
{
    pline();
}

void QQtBluetoothClient::updateProgress(qint64 bytes)
{
    //pline() << bytes;
}

void QQtBluetoothClient::connectToSingelHost()
{
    if (!m_uuid.isNull())
    {
        connectToService(m_serverIP, m_uuid);
        pline() << peerName() << m_uuid;
    }
    else if(m_serviceInfo.isValid())
    {
        connectToService(m_serviceInfo);
        pline() << m_serviceInfo;
    }
    else if (m_PORT!= 0)
    {
        connectToService(m_serverIP, m_PORT);
        pline() << peerName() << m_PORT;
    }
}



void QQtBluetoothClient::readyReadData()
{
    // queued conn and queued package;
    // direct conn and direct package;

    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do{
        quint16 nBlockLen = m_protocol->splitter(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen)
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            /*
             * stick package
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pline() << "stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            m_protocol->dispatcher(netData);
            continue;
        }
        /*
         * 正常分发
         */
        m_protocol->dispatcher(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}