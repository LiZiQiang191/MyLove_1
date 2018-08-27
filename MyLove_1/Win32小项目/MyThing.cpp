#include "stdafx.h"
#include "MyThing.h"


CMyThing::CMyThing()
{
	m_pos = NULL;
	m_side = 0;

}

CMyThing::~CMyThing()
{
	clear();
}

void CMyThing::InitThing( HDC &hdc)
{
	//��ʱ�丳ֵ
	m_time = 80;
	//�����긳ֵ
	m_pos = new MyPoint;
	m_pos->row = rand() % 600;
	m_pos->col = rand() % 1200;
	//���߳���ֵ
	int temp;
	while (true)
	{
		temp = rand() % 300;
		if (temp > 150)
			break;
	}
	m_side = temp;										//�߳�
	
	heartDC = CreateCompatibleDC(hdc);
}

void CMyThing::RenderThing(HDC &hdc ,HINSTANCE& hInst, int flag)
{
	TCHAR Str[30] = { 0 };
	for (int i = 1; i <= 12; ++i)
	{
		Sleep(m_time);
		_stprintf_s(Str, 20, _T("%d.%d.bmp"), flag, i);
		heartBit = (HBITMAP)LoadImage(hInst, Str, IMAGE_BITMAP, m_side, m_side, LR_LOADFROMFILE);
		SelectObject(heartDC, heartBit);
		if (flag == 1)
			TransparentBlt(hdc, m_pos->col, m_pos->row, m_side, m_side, heartDC, 0, 0, m_side, m_side, RGB(7, 7, 7));
		else if(flag == 2)
			TransparentBlt(hdc, m_pos->col, m_pos->row, m_side, m_side, heartDC, 0, 0, m_side, m_side, RGB(0, 7, 7));
		else if (flag == 3)
			TransparentBlt(hdc, m_pos->col, m_pos->row, m_side, m_side, heartDC, 0, 0, m_side, m_side, RGB(0, 0, 10));
		else
			TransparentBlt(hdc, m_pos->col, m_pos->row, m_side, m_side, heartDC, 0, 0, m_side, m_side, RGB(0, 8, 0));
		DeleteObject(heartBit);
 	}
}

void CMyThing::SetAttribute(int side, MyPoint pos, size_t time)
{
	m_side = side;
	*m_pos = pos;
	m_time = time;
}

void CMyThing::clear()
{
	if (m_pos)
	{
		delete m_pos;
		m_pos = NULL;
	}

	DeleteDC(heartDC);
}
