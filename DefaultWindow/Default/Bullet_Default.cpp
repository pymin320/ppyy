#include "stdafx.h"
#include "Bullet_Default.h"


CBulletDefault::CBulletDefault()
{
}


CBulletDefault::~CBulletDefault()
{
	Release();
}

void CBulletDefault::Initialize(void)
{
	m_tInfo.fCX = 7.f;
	m_tInfo.fCY = 14.f;

	m_fSpeed = 3.f;
}

int CBulletDefault::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;



	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
		
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBulletDefault::Late_Update(void)
{
	if (0 >= m_tRect.left || WINCX - 0 <= m_tRect.right ||
		0 >= m_tRect.top || WINCY - 0 <= m_tRect.bottom)
		m_bDead = true; 
}

void CBulletDefault::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBulletDefault::Release(void)
{
	
}