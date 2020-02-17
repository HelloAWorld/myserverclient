#include "mycirclebuffer.h"
#include "memory.h"

CMyCircleBuffer::CMyCircleBuffer()
{
	m_ialloclen = 0;
	m_idatalen = 0;
	m_icurpos = 0;
	m_icurbase = 0;
	m_pData = NULL;
}

int CMyCircleBuffer::InitBuffer(int iBufSize)
{
	if(NULL != m_pData)
	{
		delete [] m_pData;
		m_icurpos = 0;
		m_icurbase = 0;
		m_idatalen = 0;
		m_ialloclen = 0;
	}
	m_pData = new char[iBufSize];
	if(NULL == m_pData)
	{
		return -1;
	}		
	m_ialloclen = iBufSize;
}

int CMyCircleBuffer::AddData(const char * pData, int iDataLen)
{
	if((iDataLen + m_idatalen) > m_ialloclen)
	{
		return -1;
	}
	
	if(m_icurpos + iDataLen >= m_ialloclen)
	{
		int reslen = m_ialloclen - m_icurpos;
		memcpy(m_pData + m_icurpos, pData, reslen);
		memcpy(m_pData, pData + reslen, iDataLen - reslen);
		m_icurpos = iDataLen - reslen;
	}
	else
	{
		memcpy(m_pData + m_icurpos, pData, iDataLen);	
		m_icurpos += iDataLen;
	}
	m_idatalen += iDataLen;
	
	return 0;
}

int CMyCircleBuffer::GetDataLength() const
{
	return m_idatalen;
}

int CMyCircleBuffer::SetPosition(int iStep)
{
	if(istep > m_idatalen)
	{
		return -1;
	}
	m_icurpos = (m_icurpos + istep) % m_ialloclen;
	return m_icurpos;
}

int CMyCircleBuffer::GetData(char * pData, int iDataLen)
{
	if(NULL == pData || iDataLen <= 0)
	{
		return -1;
	}
	
	int realdatalen = iDataLen;
	if(iDataLen > m_idatalen)
	{
		realdatalen = m_idatalen;
	}
	if(m_ialloclen - m_icurbase >= realdatalen)
	{
		memcpy(pData, m_pData + m_icurbase, realdatalen);
		m_icurbase += realdatalen;
		m_idatalen -= realdatalen;
	}
	else
	{
		int reslen = m_ialloclen - m_icurbase;
		memcpy(pData, m_pData + m_icurbase, reslen);
		memcpy(pData, m_pData, realdatalen - reslen);
		m_icurbase = realdatalen - reslen;
	}
	return 0;
}

const char * CMyCircleBuffer::GetData() const
{
	return m_pData + m_icurbase;
}
