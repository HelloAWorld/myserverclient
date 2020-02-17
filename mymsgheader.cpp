#include "mymsgheader.h"
#include "memory.h"

CMyMsgHeader::CMyMsgHeader()
{
	m_imsglen = 0;
	m_imsgtype = 0;
	m_imsgdatalen = 0;
	m_pData = NULL;
}

int CMyMsgHeader::GetMsgLen() const
{
	return m_imsglen;
}

int CMyMsgHeader::GetMsgType() const
{
	return m_imsgtype;
}

int CMyMsgHeader::GetMsgDataLen() const
{
	return m_imsgdatalen;
}

const char * CMyMsgHeader::GetMsgData() const
{
	return m_pData;
}

void CMyMsgHeader::SetMsgLen(int iMsgLen)
{
	m_imsglen = iMsgLen;
}

void CMyMsgHeader::SetMsgType(int imsgtype)
{
	m_imsgtype = imsgtype;
}

void CMyMsgHeader::SetMsgData(const char * pData, int iDataLen)
{
	if(NULL == pData || iDataLen <= 0 )
	{
		return;
	}
	SetMsgLen(iDataLen + 3 * sizeof(int));
	m_imsgdatalen = iDataLen;
	m_pData = new char[iDataLen + 1];
	memset(m_pData, 0, iDataLen + 1);
	memcpy(m_pData, pData, iDataLen);
}

char * CMyMsgHeader::format()
{
	char * buf = new char[m_imsglen];
	memset(buf, 0, m_imsglen);

	int pos = 0;
	memcpy(buf, &m_imsglen, sizeof(int));
	pos += sizeof(int);

	memcpy(buf, &m_imsgtype, sizeof(int));
	pos += sizeof(int);

	memcpy(buf, &m_imsgdatalen, sizeof(int));
	pos += sizeof(int);
	
	memcpy(buf, m_pData, m_imsgdatalen);
	
	return buf;
}

int CMyMsgHeader::parse(const char * pData, int iDataLen)
{
	int pos = 0;
	memcpy(&m_imsglen, pData, sizeof(int));
	if(m_imsglen > iDataLen)
	{
		return 0;
	}
	pos += sizeof(int);

	memcpy(&m_imsgtype, pData + pos, sizeof(int));
	pos += sizeof(int);

	memcpy(&m_imsgdatalen, pData + pos, sizeof(int));
	pos += sizeof(int);
	if(m_imsgdatalen > (iDataLen - pos))
	{
		return -1;
	}
	
	m_pData = new char [m_imsgdatalen + 1];
	memset(m_pData, 0, m_imsgdatalen + 1);
	memcpy(m_pData, pData + pos , m_imsgdatalen);
	pos += m_imsgdatalen;
			
	return pos;
}
