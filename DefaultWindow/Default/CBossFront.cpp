#include "stdafx.h"
#include "CBossFront.h"

CBossFront::CBossFront()
	:m_BossTime(GetTickCount())
{
}

CBossFront::~CBossFront()
{
}

void CBossFront::Initialize(void)
{
	m_tInfo.fX = 400;
	m_tInfo.fY = -200;
	m_fAngle = 0;

	m_Hp = 500;

	m_ySpeed = 1.0f;
	m_fSpeed = 0.2f;
	m_Side = "Enemy";
	m_fDiagonal = 0;
}

int CBossFront::Update(void)
{
	if (m_bDead)
	{
		--m_Hp;
	}

	m_tInfo.fX += m_fSpeed;

	if (m_BossTime + 7000 <= GetTickCount())
	{
		m_tInfo.fY += m_ySpeed;
	}

	Update_Rect();



	m_tRect.right = m_tInfo.fX + 100;
	m_tRect.left = m_tInfo.fX - 100;
	m_tRect.top = m_tInfo.fY + 100;
	m_tRect.bottom = m_tInfo.fY + 130;

	return OBJ_NOEVENT;
}

void CBossFront::Late_Update(void)
{
	if (275 >= m_tRect.left || 535 <= m_tRect.right)
		m_fSpeed *= -1.f;
	if (110 < m_tRect.bottom)
		m_ySpeed = 0;

	// 보스프론트 포신

	float		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float		fDiagona = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float		fRadian = acosf(fWidth / fDiagona);

	m_fDiagonal = m_tRect.bottom + 70;


	m_tPosin.x = long(m_tInfo.fX + m_fDiagonal * cosf(fRadian));
	m_tPosin.y = long(m_tInfo.fY + m_fDiagonal * sinf(fRadian));
}

void CBossFront::Render(HDC hDC)
{
	if (m_Hp > 0)
	{
		//RoundRect(hDC, m_PosinRect.left, m_PosinRect.top, m_PosinRect.right, m_PosinRect.bottom,180,5);
		MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 95, nullptr);
		LineTo(hDC, (int)m_tPosin.x, (int)m_tPosin.y);
		MoveToEx(hDC, (int)m_tInfo.fX + 1, (int)m_tInfo.fY + 95, nullptr);
		LineTo(hDC, (int)m_tPosin.x + 1, (int)m_tPosin.y);
		MoveToEx(hDC, (int)m_tInfo.fX - 1, (int)m_tInfo.fY + 95, nullptr);
		LineTo(hDC, (int)m_tPosin.x - 1, (int)m_tPosin.y);
		MoveToEx(hDC, (int)m_tInfo.fX + 2, (int)m_tInfo.fY + 95, nullptr);
		LineTo(hDC, (int)m_tPosin.x + 2, (int)m_tPosin.y);
		MoveToEx(hDC, (int)m_tInfo.fX - 2, (int)m_tInfo.fY + 95, nullptr);
		LineTo(hDC, (int)m_tPosin.x - 2, (int)m_tPosin.y);
		Pie(hDC, m_tRect.left, m_tRect.top - 60, m_tRect.right, m_tRect.bottom + 20, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom - 30);
		MoveToEx(hDC, m_tRect.left + 28, m_tRect.bottom, nullptr);
		LineTo(hDC, m_tRect.right - 28, m_tRect.bottom);

		if (m_bDead)
		{
			Ellipse(hDC, m_ColliRect.left - 5, m_ColliRect.top - 5, m_ColliRect.right + 5, m_ColliRect.bottom + 5);
		}
	}
}

void CBossFront::Release(void)
{
}

bool CBossFront::Dead()
{
	if (m_Hp <= 0)
	{
		return true;
	}
	else
		return false;
}