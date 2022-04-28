#include "stdafx.h"
#include "UI.h"
#include "Player.h"


CUI::CUI()
{
	//ZeroMemory(m_szMessage, sizeof(TCHAR) * 64);
	//ZeroMemory(m_szHeart, sizeof(TCHAR) * 64);

	Initialize();
}


CUI::~CUI()
{
}

void CUI::Initialize(void)
{
}

int CUI::Update(void)
{

	return 0;
}

void CUI::Late_Update(void)
{
}

void CUI::Render_UI(HDC hDC, CObj* _pPlayer)
{
	Render_UI_Heart(hDC, _pPlayer);
}

void CUI::Release(void)
{

}

void CUI::Render_UI_Heart(HDC hDC, CObj* _pPlayer)
{
	static TCHAR	m_szHeart[64];
	//lstrcpy(m_szHeart, L"LIFE : ");
	//m_iHeart = dynamic_cast<CPlayer*>(m_pPlayer)->Get_Heart();
	switch (dynamic_cast<CPlayer*>(_pPlayer)->Get_Heart())
	{
	case 0:
		lstrcpy(m_szHeart, L" LIFE : 사망 ");
		break;
	case 1:
		lstrcpy(m_szHeart, L" LIFE : ♥ ");
		break;
	case 2:
		lstrcpy(m_szHeart, L" LIFE : ♥ ♥ ");
		break;
	case 3:
		lstrcpy(m_szHeart, L" LIFE : ♥ ♥ ♥ ");
		break;
	case 4:
		lstrcpy(m_szHeart, L" LIFE : ♥ ♥ ♥ ♥ ");
		break;
	case 5:
		lstrcpy(m_szHeart, L" LIFE : ♥ ♥ ♥ ♥ ♥");
		break;
	}
	TextOut(hDC, 20, 20, m_szHeart, lstrlen(m_szHeart));


	static TCHAR	m_szBoost[64];
	//lstrcpy(m_szHeart, L"BOOST : ");
	switch (dynamic_cast<CPlayer*>(_pPlayer)->Get_BoostCount())
	{
	case 0:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : 부스트가 없습니다. Score를 채우세요");
		break;
	case 1:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : ◆ ");
		break;
	case 2:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : ◆ ◆ ");
		break;
	case 3:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : ◆ ◆ ◆ ");
		break;
	case 4:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : ◆ ◆ ◆ ◆ ");
		break;
	case 5:
		lstrcpy(m_szBoost, L" BOOST(ctrl) : ◆ ◆ ◆ ◆ ◆");
		break;
	}
	TextOut(hDC, 20, 40, m_szBoost, lstrlen(m_szBoost));


	static TCHAR	m_szBomb[64];
	//lstrcpy(m_szHeart, L"BOOST : ");
	switch (dynamic_cast<CPlayer*>(_pPlayer)->Get_BombCount())
	{
	case 0:
		lstrcpy(m_szBomb, L" Bomb( V ) : 폭탄이 없습니다. 아이템을 획득하세요");
		break;
	case 1:
		lstrcpy(m_szBomb, L" Bomb( V ) : ◆ ");
		break;
	case 2:
		lstrcpy(m_szBomb, L" Bomb( V ) : ◆ ◆ ");
		break;
	case 3:
		lstrcpy(m_szBomb, L" Bomb( V ) : ◆ ◆ ◆ ");
		break;
	case 4:
		lstrcpy(m_szBomb, L" Bomb( V ) : ◆ ◆ ◆ ◆ ");
		break;
	case 5:
		lstrcpy(m_szBomb, L" Bomb( V ) : ◆ ◆ ◆ ◆ ◆");
		break;
	}
	TextOut(hDC, 20, 60, m_szBomb, lstrlen(m_szBomb));
}



void CUI::Render_UI_Score(HDC hDC)
{
	TCHAR	m_szTemp[64];
	RECT rc{ 600, 20, 770, 70 };
	swprintf_s(m_szTemp, L"Score : %d", g_iScore);
	DrawText(hDC, m_szTemp, lstrlen(m_szTemp), &rc, DT_RIGHT);
}


void CUI::Render_UI_PosText(HDC hDC, float _x, float _y, TCHAR _text[64])
{
	TCHAR	m_szTemp[64];
	lstrcpy(m_szTemp, _text);
	TextOut(hDC, _x, _y, m_szTemp, lstrlen(m_szTemp));
}


// 폰트 출력 (지울예정)
//
//lstrcpy(m_szFPS, L"Hello");
//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
// 1. dc 2, 3. 출력할 윈도우 left, top 좌표, 4. 출력할 문자열 5. 문자열 버퍼 크기
//
//RECT rc{ 0, 0, 50, 50 };
//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
// 1. dc 2. 출력할 문자열 3. 문자열 버퍼 크기 4. 출력할 렉트 주소, 5. 출력 옵션
//
//TCHAR	szBuff[32] = L"";
// 소수점 자리 출력이 불가능하다. winapi 라이브러리에서 제공하는 함수
//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
//
// visual c++ 라이브러리에서 제공(모든 서식 문자를 지원)
//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));