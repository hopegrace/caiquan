#include "BaseConnect.h"
#include "cocos2d.h"
//#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID

enum {
	HEAD_LOGIN = 0x0002,
	HEAD_LOGIN_ACK = 0x0003,
	HEAD_LOGOUT = 0x0004,
	HEAD_LOGOUT_ACK = 0x0005,
	HEAD_GET = 0x0006,
	HEAD_GET_ACK = 0x0007
} e_HEAD;

BaseConnect::BaseConnect(CCString* ipaddres,int port,int iptype)
{
	//����SOCKET������
    CREATE_TCPSOCKETMGR();    

    //uint64 t_begin = GetCurrentTime();
    //���������SOCKET��������������IP���˿ڣ��Զ����SOCKET_ID��ʶ
	sSocketMgr.createSocket(ipaddres->getCString(), port, iptype);
    //uint64 t_end = GetCurrentTime();
    // ע��Э�飬��������ͷ���ص�����//
	sSocketMgr.register_process(HEAD_LOGIN_ACK, SCT_CALLBACK_2(BaseConnect::ack_login, this));
	sSocketMgr.register_process(HEAD_GET_ACK, SCT_CALLBACK_2(BaseConnect::ack_getHand, this));

    //sSocketMgr.register_process(HEAD_LOGIN_ACK, SCT_CALLBACK_2(BaseConnect::process_login, this));
    //sSocketMgr.register_process(0x2d, SCT_CALLBACK_2(BaseConnect::process_openbackpack, this));
    // ע����Ϣ�ػ��¼���ע����¼�����Խػ��յ���������Ϣ�����ص���������true�򱾴��¼�������ַ�ע�����Э�飬����false�򲻷ַ�//
    sSocketMgr.register_connect(SCT_CALLBACK_2(BaseConnect::OnConnect, this));
    sSocketMgr.register_disconnect(SCT_CALLBACK_3(BaseConnect::onDisconnect, this));
	
	currHand_ = -1;//��ǰ����//
	//CCLOG("add connect player wait [%u]", t_end - t_begin);
	
}


BaseConnect::~BaseConnect(void)
{
	
}
//���Ӧ�����յ���Ϣʱ��Ĵ�����ô�Ƿ�������//
//_tag����socket fd//
//���ܴӷ�����������Ӧ��//
void BaseConnect::process_login(int _tag, WorldPacket & packet)
{
    CCLOG("process_login len:%u", packet.size());
    // ����Э���
    //WorldPacket newP;
    //newP.clear();    
    //newP.SetOpcode(0x00B6);// ����Э��ͷ
    //newP    << uint16(0x00B6) 
    //        << uint16(0);// Э�鳤��
    //newP.SetLength(newP.size());// ����Э�鳤��    
    //sSocketMgr.SendPacket(1, &newP);// ��������
}

void BaseConnect::process_openbackpack(int _tag, WorldPacket & packet)
{
    CCLOG("process_openbackpack len:%u", packet.size());
}

bool BaseConnect::process_all(int _tag, int _cmd, WorldPacket & packet)
{
    CCLOG("process_all _tag:%u, _cmd:%u, len:%u", _tag, _cmd, packet.size());
    return false;
}

void BaseConnect::OnConnect(int _tag, bool isConnect)
{
    // ����Э���
    //WorldPacket packet;
    //packet.clear();    
    //packet.SetOpcode(0x0010);// ����Э��ͷ
    //packet    << uint16(0x0010) 
    //        << uint16(0)// Э�鳤��
    //        << uint8(1) 
    //        << uint8(0);
    //// �����ַ�������(uint8��ʾ�ַ���������ռ�ֽڣ��˴�Ϊ1�ֽ�)
    //packet.AppendPacketString<uint8>(std::string("aaa:88889083:d5956683c17d7e284d33ee295b277b52"));    
    //packet.SetLength(packet.size());// ����Э�鳤��    
    //sSocketMgr.SendPacket(1, &packet);// ��������
    CCLOG("OnConnect:%u, isConnect[%u]", _tag, isConnect);
	
}

void BaseConnect::onDisconnect(int _tag)
{
    CCLOG("desconnect:%u", _tag);
}

void BaseConnect::login()
{
	WorldPacket packet;
	packet.clear();
	packet.SetOpcode(HEAD_LOGIN);
	packet <<uint16(0) << uint16(HEAD_LOGIN);//����+cmd//
	packet.SetLength(packet.size());
	sSocketMgr.SendPacket(1, &packet);
}

void BaseConnect::getHand()
{
	WorldPacket packet;
	packet.clear();
	packet.SetOpcode(HEAD_GET);
	packet <<uint16(0) << uint16(HEAD_GET);
	packet.SetLength(packet.size());
	sSocketMgr.SendPacket(1, &packet);
}

void BaseConnect::ack_login(int tag, WorldPacket& packet)
{
	CCLOG("ack_login: %d", packet.size());
}

void BaseConnect::ack_getHand(int tag, WorldPacket& packet)
{	
	int16 len, cmd;
	packet >> currHand_;
	CCLOG("ack_getHand: hand: %d", currHand_);
}

//#endif
