#pragma once

#include "Include.h"
#include "Player.h"

#include "Monster.h"
#include "AbstractFactory.h"

#include "CPattern.h"

#include "UI.h"
#include "CBoss.h"
#include "Item.h"

class CMainGame
{
public:				// 생성자, 소멸자
	CMainGame();
	~CMainGame();

public:

	void	Initialize(void);		// 초기화 함수
	void	Update(void);			// 매 프레임마다 갱신되는 데이터를 만드는 함수
	void	Late_Update(void);
	void	Render(void);			// 매 프레임마다 출력하는 함수
	void	Release(void);			// 동적할당한 포인터를 해제하는 함수

public :
	static void	CreateItem(float _x, float _y, float _angle);

private:

	HDC		m_hDC;

	//list<PATTERN*> m_PatternList;

	list<CObj*>	m_ObjList[OBJ_END];
	list<CObj*> m_ColList;
	TCHAR		m_szFPS[64];	// 멀티 바이트 기반에서는 CHAR로 유니 코드 기반에서는 유니코드로 처리해주는 매크로
	int			m_iFPS;
	DWORD		m_dwTime;
	int			A;

};