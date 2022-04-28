#include "stdafx.h"
#include "BulletBomb.h"
#include "AbstractFactory.h"
CBulletBomb::CBulletBomb()
{
}

CBulletBomb::~CBulletBomb()
{
    Release();
}

void CBulletBomb::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 15.f;

	m_fSpeed = 3.f;
}

int CBulletBomb::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	m_tInfo.fX += m_fSpeed * cosf((m_fAngle * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fAngle * PI) / 180.f);
	Update_Rect();

	DWORD currentTickCount = GetTickCount();
	if (currentTickCount - m_Time >= m_BombTimer)
	{
		m_Time = GetTickCount();
		for (int i = 1; i < 37; i++)
		{
			m_BulletList->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY));
			m_BulletList->back()->Side("Team");//수정필요
			m_BulletList->back()->Set_Angle(m_fAngle += (10.f * i));
		}
		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;
}

void CBulletBomb::Late_Update(void)
{	
	
}

void CBulletBomb::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBulletBomb::Release(void)
{
	m_BulletList = nullptr;
}
