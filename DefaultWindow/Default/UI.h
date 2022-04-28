#pragma once
#include "Obj.h"

class CUI
{
public:
	CUI();
	~CUI();

			void	Initialize(void);
			int		Update(void);
			void	Late_Update(void);
	static	void	Render_UI(HDC hDC, CObj* _pPlayer);
			void	Release(void);

public:
	static	void	Render_UI_Heart(HDC hDC, CObj* _pPlayer);
	static	void	Render_UI_Score(HDC hDC);
	static	void	Render_UI_PosText(HDC hDC, float _x, float _y, TCHAR _text[64]);
};

