#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	
	m_fSpeed = 3.f;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);

	if (!(m_Side == "Team"))
	{	
		m_tInfo.fCX = 7.f;
		m_tInfo.fCY = 14.f;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	/*if (0 >= m_tRect.left || WINCX - 0 <= m_tRect.right ||
		0 >= m_tRect.top || WINCY - 0 <= m_tRect.bottom)
		m_bDead = true;*/
}

void CBullet::Render(HDC hDC)
{
	HBRUSH myBrush;
	HBRUSH oldBrush;

	if (!(m_Side == "Team"))
	{ 
  		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 81, 81));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else if (!(m_Side == "Enemy"))
	{
		myBrush = (HBRUSH)CreateSolidBrush(RGB(101, 171, 235));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
}

void CBullet::Release(void)
{
	m_ColList = nullptr;

}
void CBullet::OnTriggerEnter(CObj* _Object)
{
	if ((m_Side == "Team") && (_Object->Get_Side() == "Enemy"))
	{
		int a;
		//m_bDead = true;
	}
}
void CBullet::SetDirection(const POINT& _direction)
{
	m_Direction = _direction;
}