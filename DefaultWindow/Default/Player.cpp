#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "Shield.h"
#include "Item.h"

CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{
	Release();
}
void CPlayer::Initialize(void)
{
	m_iHeart = 5;
	m_iBoostCount = 0;
	m_iBombCount = 3;
	m_iGageScore = 1;

	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	PolygonPoint[0] = { (long)m_tInfo.fX, (long)m_tInfo.fY - 50 };
	PolygonPoint[1] = { (long)m_tInfo.fX + 50, (long)m_tInfo.fY };
	PolygonPoint[2] = { (long)m_tInfo.fX + 50, (long)m_tInfo.fY + 50 };
	PolygonPoint[3] = { (long)m_tInfo.fX, (long)m_tInfo.fY };
	PolygonPoint[4] = { (long)m_tInfo.fX - 50 , (long)m_tInfo.fY + 50 };
	PolygonPoint[5] = { (long)m_tInfo.fX - 50, (long)m_tInfo.fY };

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;
	m_fDiagonal = 50.f;

	m_fAngle_Shield = 90.f;
	m_bBoost = false;
	m_bShield = false;
	m_fDiagonal_Shield = 80.f;
	
	m_Side = "Team";

	m_Time = GetTickCount();		// 쉴드 타이머
	m_Time2 = GetTickCount();       // 총알 타이머
	m_Time3 = GetTickCount();		// 부스트 타이머
	m_Time4 = GetTickCount();		// 폭탄 타이머
}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		if (m_iHeart)
		{
			--m_iHeart;
			m_bDead = false;

			if (m_iHeart <= 0)
			{
				return OBJ_DEAD;
			}
		}
		else
			return OBJ_DEAD;
	}

	if (g_iScore >= m_iGageScore * 50)
	{
		++m_iBoostCount;
		++m_iGageScore;
	}

	// 키입력시 연산
	Key_Input();
	PolygonPoint[0] = { (long)m_tInfo.fX, (long)m_tInfo.fY - 30 };
	PolygonPoint[1] = { (long)m_tInfo.fX + 30, (long)m_tInfo.fY};
	PolygonPoint[2] = { (long)m_tInfo.fX + 30, (long)m_tInfo.fY + 30};
	PolygonPoint[3] = { (long)m_tInfo.fX, (long)m_tInfo.fY};
	PolygonPoint[4] = { (long)m_tInfo.fX - 30 , (long)m_tInfo.fY + 30 };
	PolygonPoint[5] = { (long)m_tInfo.fX - 30, (long)m_tInfo.fY};

	// 쉴드 좌표 움직이게
	m_fAngle_Shield += 3.f;

	// 쉴드 타이머
	if (m_bShield)
	{
		DWORD CurrentTime = GetTickCount();
		if (CurrentTime - m_Time > 5000)
		{
			for (auto& _iter = m_pShieldList->begin(); _iter != m_pShieldList->end();)
			{
				Safe_Delete<CObj*>(*_iter);
				_iter = m_pShieldList->erase(_iter);
			}
			m_bShield = false;
			m_Time = GetTickCount();
		}
	}

	// 부스트 타이머
	if (m_bBoost)
	{
		DWORD CurrentTime = GetTickCount();
		if (CurrentTime - m_Time3 > 5000)
		{
			m_bBoost = false;
			m_Time3 = GetTickCount();
		}
	}

	// 최종좌표 전달
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	m_tPosin.x = long(m_tInfo.fX + (m_fDiagonal * cosf((m_fAngle * PI) / 180.f)));
	m_tPosin.y = long(m_tInfo.fY - (m_fDiagonal * sinf((m_fAngle * PI) / 180.f)));

	if (m_bShield)
	{
		for (auto& _shield : *m_pShieldList)
		{
			m_tPosin_Shield.x = long(m_tInfo.fX + (m_fDiagonal_Shield * cosf((m_fAngle_Shield * PI) / 180.f)));
			m_tPosin_Shield.y = long(m_tInfo.fY - (m_fDiagonal_Shield * sinf((m_fAngle_Shield * PI) / 180.f)));

			_shield->Set_Pos(m_tPosin_Shield.x, m_tPosin_Shield.y);
			_shield->Late_Update();
			
			m_fAngle_Shield += 180.f;
		}
	}
}

void CPlayer::Render(HDC hDC)
{
	Polygon(hDC, PolygonPoint, 6);

	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	LineTo(hDC, m_tPosin.x, m_tPosin.y);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if(m_bShield)
	{
		for (auto& _shield : *m_pShieldList)
		{
			_shield->Render(hDC);
		}
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15, L"Shield!!!");
	}

	if (m_bBoost)
	{
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15, L"Boost!!!");
	}
}

void CPlayer::Release(void)
{
	//Safe_Delete<CPattern*>(m_pPattern);
	m_ColList = nullptr;
}

//충돌이 되면 실행되는 함수
void CPlayer::OnTriggerEnter(CObj* _Object)
{
	if (!(_Object->Get_Side() == "Enemy"))
	{
		m_CollisionTime = GetTickCount();

		m_helth--;
		//데미지입음

	}
	if (_Object->Get_Side() == "Team")
	{
		Set_ItemAbility(_Object);
	}
}


void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState('V'))
	{
		if (GetTickCount() - m_Time4 > 500)
		{
			if (m_iBombCount > 0)
			{
				m_pBulletList->push_back(CAbstractFactory<CBulletBomb>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
				((CBulletBomb*)m_pBulletList->back())->SetBulletList(m_pBulletList);
				m_pBulletList->back()->Set_Speed(3.f);
				--m_iBombCount;
				m_Time4 = GetTickCount();
			}
		}
	}

	if (GetAsyncKeyState(VK_CONTROL))
	{
		if (GetTickCount() - m_Time3 > 200)
		{
			if (m_iBoostCount > 0)
			{
				m_bBoost = true;
				--m_iBoostCount;
			}
			m_Time3 = GetTickCount();
		}
	}

	// 총알 발사
	if (GetAsyncKeyState(VK_SPACE))
	{		
		if (GetTickCount() - m_Time2 > 120)
		{
			if (m_bShield)	// 쉴드 모드
			{
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, "Team"));
				m_pBulletList->back()->Set_Speed(6.f);

				for (auto& _shield : *m_pShieldList)
				{
					POINT temp = { dynamic_cast<CShield*>(_shield)->Get_PosinPoint().x,
									dynamic_cast<CShield*>(_shield)->Get_PosinPoint().y };
					m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)temp.x, (float)temp.y, m_fAngle, "Team"));
					m_pBulletList->back()->Set_Speed(6.f);
				}
			}
			else if (m_bBoost)	// 부스트 모드
			{
				//m_pBulletList->push_back(CAbstractFactory<CBulletBomb>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle));
				//((CBulletBomb*)m_pBulletList->back())->SetBulletList(m_pBulletList);
				//m_pBulletList->back()->Side("Team");//수정필요
				//m_pBulletList->back()->Set_Speed(-3.f);
				//총알 3발
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x - 10, (float)m_tPosin.y, m_fAngle, "Team"));
				m_pBulletList->back()->Set_Speed(8.f);
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, "Team"));
				m_pBulletList->back()->Set_Speed(8.f);
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x + 10, (float)m_tPosin.y, m_fAngle, "Team"));
				m_pBulletList->back()->Set_Speed(8.f);
				
			}
			else if (!m_bBoost)	// 기본 모드
			{
				m_pBulletList->push_back(CAbstractFactory<CBullet>::Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, "Team"));
				m_pBulletList->back()->Set_Speed(6.f);
				//m_ColList->push_back(m_pBulletList->back());
			}
			m_Time2 = GetTickCount();
		}
	}

	// 포신 회전
	if (GetAsyncKeyState('A'))
		m_fAngle += 5.f;

	if (GetAsyncKeyState('D'))
		m_fAngle -= 5.f;

	// 플레이어 이동
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (m_tInfo.fX > 0)					// 화면 이탈 방지
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// 화면 이탈 방지
				{
					m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// 화면 이탈 방지
				{
					m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
					m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				}
			}
			else
			{
				m_tInfo.fX -= m_fSpeed;
			}
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (m_tInfo.fX < 800)				// 화면 이탈 방지
		{
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (m_tInfo.fY < 600)		// 화면 이탈 방지
				{
					m_tInfo.fX += m_fSpeed / sqrtf(2.f);
					m_tInfo.fY += m_fSpeed / sqrtf(2.f);
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if (m_tInfo.fY > 0)			// 화면 이탈 방지
				{
					m_tInfo.fX += m_fSpeed / sqrtf(2.f);
					m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
				}
			}
			else
				m_tInfo.fX += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (m_tInfo.fY > 0)		// 화면 이탈 방지
		{
			m_tInfo.fY -= m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (m_tInfo.fY < 600)	// 화면 이탈 방지
		{
			m_tInfo.fY += m_fSpeed;
		}
	}
}

void CPlayer::Set_ItemAbility(CObj* _item)
{
	int iItemType = dynamic_cast<CItem*>(_item)->Get_ItemType();
	switch (iItemType)
	{
		m_fAngle_Shield;
	case ITEM_SHIELD:
		for (int i = 0; i < 2; ++i)
		{
			m_pShieldList->push_back(CAbstractFactory<CShield>::Create((float)m_tPosin.x, (float)m_tPosin.y, 90.f));
		}
		m_bShield = true;
		m_Time = GetTickCount();
		break;
	case ITEM_SPEED:
		m_fSpeed *= 1.1f;
		break;
	case ITEM_COIN:
		g_iScore += 100;
		break;
	default:
		break;
	}
}