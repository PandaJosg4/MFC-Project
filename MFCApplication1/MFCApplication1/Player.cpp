
// Player.cpp : implementation file
//

#include "stdafx.h"
#include "Player.h"
#include "Projectile.h"


// Updates coordinates of player
void Player::Move(int xChange, int yChange)
{
    coor.x += xChange;
    coor.y += yChange;
}

void Player::Shoot()
{
	
}

// Returns coordinates of player
Point Player::Coordinates()
{
    return coor;
}

// Sets coordinates of player
void Player::SetCoordinates(int x1, int y1)
{
    coor.x = x1;
    coor.y = y1;
}




/*
Notes on Text Control and SetItemDlgText function
---------------------------------------------
Need to pass a LPCTSTR (const TCHAR *) to set caption of Text Control

2 Options:

--> 1. Start with CString (const char *)
        - CString auto-converts to LPCTSTR (const TCHAR *)
        - need to use .format(_T("%d"),) for ints

    Ex:
    CString a;
    a.Format(_T("%d"), *int*);
    SetDlgItemText(IDC_USERPOS, a);

    ---------------------------------------------

    2. Start with wstring (std::wstring)
        - use .c_str() to convert to LPCWSTR (const wchar_t *)
        - LPCWSTR auto-converts into LPCTSTR (const TCHAR *)
        - can use std:to_wstring for ints/strings/anything
        - using .c_str() only allows for read-only data

    Ex:
    std::wstring b = std::to_wstring(*int*);
    SetDlgItemText(IDC_USERPOS, b.c_str());
*/