#include "stdafx.h"
#include "CBoss.h"
#include "CBossFront.h"

CBoss::CBoss()
	:m_BossTime(GetTickCount())
{
	m_pBossFront = new CBossFront;
}

CBoss::~CBoss()
{
}

void CBoss::Initialize(void)
{
	m_tInfo.fCX = 900;
	m_tInfo.fCY = 200;

	m_ySpeed = 1.f;
	m_fSpeed = 0.2f;
	m_Hp = 200;

	m_pBossFront->Initialize();
}

int CBoss::Update(void)
{
	if (m_bDead && dynamic_cast<CBossFront*>(m_pBossFront)->Dead())
	{
		--m_Hp;
		if (m_Hp <= 0)
		{
			return OBJ_DEAD;
			//Safe_Delete(m_pBossFront);
		}
	}


	m_tInfo.fX += m_fSpeed;
	if (m_BossTime + 7000 <= GetTickCount())
	{
		m_tInfo.fY += m_ySpeed;
	}

	Update_Rect();

	m_pRect.right = m_tInfo.fX + 280;
	m_pRect.left = m_tInfo.fX + 250;
	m_pRect.top = m_tInfo.fY + 100;
	m_pRect.bottom = m_tInfo.fY + 180;

	m_pRect2.right = m_tInfo.fX - 280;
	m_pRect2.left = m_tInfo.fX - 250;
	m_pRect2.top = m_tInfo.fY + 100;
	m_pRect2.bottom = m_tInfo.fY + 180;

	
	return OBJ_NOEVENT;
}

void CBoss::Late_Update(void)
{
	if (-80 >= m_tRect.left || 880 <= m_tRect.right)
		m_fSpeed *= -1.f;
	if (80 < m_tRect.bottom)
		m_ySpeed = 0;
}

void CBoss::Render(HDC hDC)
{

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Rectangle(hDC, m_pRect.left, m_pRect.top, m_pRect.right, m_pRect.bottom);
	Rectangle(hDC, m_pRect2.left, m_pRect2.top, m_pRect2.right, m_pRect2.bottom);
}

void CBoss::Release(void)
{
}
