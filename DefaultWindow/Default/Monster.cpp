#include "stdafx.h"
#include "Monster.h"
#include "Player.h"
#include <random>
#include "AbstractFactory.h"
#include "Item.h"

CMonster::CMonster() {}
CMonster::CMonster(MOBTYPE eType)
{
	m_eType = eType;
	m_Side = "Enemy";
}
CMonster::~CMonster()
{
	//hong modify
	Release();
	//end
}
void CMonster::Initialize(void)
{
	//좌우이동몬스터
	if (m_eType == MOB_FW)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;

		m_fSpeed = 1.f;
	}
	//내려오는몬스터
	if (m_eType == MOB_DF)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;

		m_fSpeed = 1.5f;
	}
	if (m_eType == MOB_CH)
	{
		m_tInfo.fCX = 25.f;
		m_tInfo.fCY = 25.f;

		m_fSpeed = 2.f;
	}

	m_pPattern = new CPattern;
	m_fDiagonal = 30.f;

	m_TempAngle = m_fAngle - 30.f;
	m_Side = "Enemy";
}

int CMonster::Update(void)
{
	if (m_bDead)
	{
		if (Item_Percent() > 20) // 서진 추가
		{
			CreateItem();
			return OBJ_DEAD;
		}
	}
	if (m_eType == MOB_FW)
	{
		m_tInfo.fX += m_fSpeed;
		m_fAngle = -90.f;
	}

	if (m_eType == MOB_DF)
	{
		m_tInfo.fY += m_fSpeed;
	}
	//추격몬스터 역삼각함수로 각도 구하기
	if (m_eType == MOB_CH)
	{
		//x좌표 사이의 거리
		float fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;

		//y좌표 사이의 거리
		float fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		//대각선 거리
		float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		m_fAngle = acosf(fWidth / fDistance) * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;

		m_tInfo.fX += m_fSpeed * cosf((m_fAngle)*PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fAngle)*PI / 180.f);
	}
	m_Posin.x = m_tInfo.fX;
	m_Posin.y = m_tInfo.fY + 20.f;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (m_eType == MOB_FW)
	{
		if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
			m_fSpeed *= -1.f;
	}

	if (m_eType == MOB_CH)
	{
		//포신 끝 좌표
		m_Posin.x = m_tInfo.fX + m_fDiagonal * cosf((m_fAngle)*PI / 180.f);
		m_Posin.y = m_tInfo.fY - m_fDiagonal * sinf((m_fAngle)*PI / 180.f);
		/*	m_Posin.x = m_Posin2.x;
			m_Posin.y = m_Posin2.y;*/
	}
	m_iPatternNum = rand() % 3 + 1;
	m_pPattern->Set_Angle(m_fAngle);
	m_pPattern->Update(m_Posin, m_iPatternNum);//랜덤값으로 1~N의 번호를 넣어주면 됨
}

void CMonster::Render(HDC hDC)
{
	if (m_eType == MOB_CH)
	{
		MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
		LineTo(hDC, m_Posin.x, m_Posin.y);
	}
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
	//hong modify
	delete m_pPattern;
	m_pPattern = nullptr;
	m_ColList = nullptr;
	//end
}

void CMonster::OnTriggerEnter(CObj* _Object)
{
	if ((_Object->Get_Side() == "Team"))
	{
		//CreateItem();
		m_bDead = true;
	}
}

void CMonster::SetBulletList(list<CObj*>* _pBullet)
{
	m_pPattern->Set_BulletList(_pBullet);
}

// 서진 추가 (아이템 생성용)
void CMonster::SetItemList(list<CObj*>* _pItem)
{
	m_pItemList = _pItem;
}

int CMonster::Item_Percent()
{
	return rand() % 100 + 1;
}

void CMonster::CreateItem()
{
	m_pItemList->push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY, -90.f, "ITEM"));
	
	//m_ColList->push_back(m_pItemList->back());
}
