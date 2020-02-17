#ifndef __MY_CIRCLE_BUFFER_H__
#define __MY_CIRCLE_BUFFER_H__

class CMyCircleBuffer
{
public:
	CMyCircleBuffer();

	int InitBuffer(int iBufSize = 1024 * 10);

	int AddData(const char *pData, int iDataLen);
	int GetDataLength() const;
	void SetPosition(int istep);
	int GetData(char * pData, int iDataLen);
	const char * GetData() const;
private:
	int m_ialloclen;
	int m_idatalen;
	int m_icurpos;
	int m_icurbase;
	char * m_pData;
};


#endif 
