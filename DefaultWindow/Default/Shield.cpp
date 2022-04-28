#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
	Initialize();
}


CShield::~CShield()
{
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fDiagonal = 20.f;
}

int CShield::Update(void)
{		
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));
	Update_Rect();
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);
}

void CShield::Release(void)
{
}
