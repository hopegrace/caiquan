#ifndef __BASECONNECT__
#define __BASECONNECT__



#include "cocos2d.h"

//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
#include "TCPSocket.h"

USING_NS_CC;
class BaseConnect
{
public:
	BaseConnect(CCString* ipaddres,int port,int iptype);
	~BaseConnect(void);

	//ȫ�����õ�recv��Ϣ��Ӧ�Ļص�������//
	//send �Լ�д��ֱ��SendPacket//


	// ע�ᵥ��Э��ص�����������)��������SOCKET_ID��ʶ�����ݰ�//
    void process_login(int _tag, WorldPacket & packet);
	
    // ��Ϣ������//
    void process_openbackpack(int _tag, WorldPacket & packet);
    // ע�ᵥ��Э��ص�����������)��������SOCKET_ID��ʶ��Э��ͷ�����ݰ�//
    bool process_all(int _tag, int _cmd, WorldPacket & packet);
    // �����¼�//
    void OnConnect(int _tag, bool isConnect);
    // �����¼�//
    void onDisconnect(int _tag);

	//send cmd
	void login();
	void getHand();
	//recv ack
	void ack_login(int tag, WorldPacket& packet);
	void ack_getHand(int tag, WorldPacket& packet);

	int getCurrHand() {
		int ret = currHand_;
		currHand_ = -1;
		return ret;
	}
private:
	int16 currHand_;
};
//#endif

#endif __BASECONNECT__