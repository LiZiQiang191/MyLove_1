#pragma once
class CManage
{
private:
	CMyThing * m_thing;
public:
	CManage();
	~CManage();
public:	
	void InitProc(HDC hdc);					//��ʼ������
	void RenderProc(HDC &hdc, HINSTANCE& hInst, int flag);			//��Ⱦ����
	void upProc(HDC hdc);				//���³���
	void Change(int side, MyPoint pos, size_t time);
};

