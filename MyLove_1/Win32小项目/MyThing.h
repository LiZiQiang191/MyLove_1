#pragma once
class CMyThing
{
private:
	MyPoint * m_pos;					//���������Ͻǵ�����
	int  m_side;						//����߳�
	size_t m_time;						//�����Ļ������ֵ�ʱ��
	HBITMAP heartBit;
	HDC heartDC;
public:
	CMyThing();
	~CMyThing();
public:
	void InitThing(HDC &hdc);					//��ʼ����Ʒ
	void RenderThing(HDC &hdc, HINSTANCE& hInst, int flag);			//������Ʒ
	void SetAttribute(int side, MyPoint pos, size_t time);
public:
	void clear();
};