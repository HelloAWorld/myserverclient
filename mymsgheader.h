#ifndef __MY_MSG_H__
#define __MY_MSG_H__

class CMyMsgHeader
{
public:
	CMyMsgHeader();
	
	int GetMsgLen() const;
	int GetMsgType() const;
	int GetMsgDataLen() const;
	const char * GetMsgData() const;
	
	void SetMsgLen(int iMsgLen);
	void SetMsgType(int iMsgType);
	void SetMsgData(const char * pData, int iDataLen);

	char * format();
	int parse(const char * pData, int iDataLen);
private:
	int m_imsglen;
	int m_imsgtype;
	int m_imsgdatalen;
	char * m_pData;

};


#endif
