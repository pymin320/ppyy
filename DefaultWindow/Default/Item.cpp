#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
	m_ItemType = rand() % 4;
	Initialize();
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 2.f;
	m_ySpeed = 2.f;
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	m_tInfo.fY += m_fSpeed;

	Update_Rect();
}

void CItem::Render(HDC hDC)
{

	switch (m_ItemType)
	{
		HBRUSH myBrush;
		HBRUSH oldBrush;

	case ITEM_SHIELD:
		myBrush = (HBRUSH)CreateSolidBrush(RGB(129, 213, 119));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 20, L"SHIELD");
		return;
	case ITEM_SPEED:
		myBrush = (HBRUSH)CreateSolidBrush(RGB(63, 72, 204));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 20, L"SPEED");
		return;
	case ITEM_COIN:
		myBrush = (HBRUSH)CreateSolidBrush(RGB(250, 225, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 20, L"COIN");
		return;
	case ITEM_BOMB:
		myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
		CUI::Render_UI_PosText(hDC, m_tInfo.fX - 20, m_tInfo.fY + 20, L"BOMB");
		return;
	default:
		return;
	}

}

void CItem::Release(void)
{
}



