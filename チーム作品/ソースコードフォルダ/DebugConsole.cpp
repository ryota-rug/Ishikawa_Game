#include "DebugConsole.h"
#include "conioex.h"

#include <iostream>

FILE *fp;

DebugConsole::DebugConsole()
	:rectConsoleSize{0,0,1,1}
{
	m_pPile = NULL;

	AllocConsole();

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);

	SetConsoleScreenBufferSize(hStdout, coord);
	rectConsoleSize.Right = coord.X - 1;	
	rectConsoleSize.Bottom = coord.Y - 1;	
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	
	SetConsoleTitle("デバッグコンソール");
	freopen_s(&fp, "CON", "w", stdout);    
}

DebugConsole::~DebugConsole()
{
	fclose(fp);
	FreeConsole();
}

void DebugConsole::Update()
{
	gotoxy(1, 1);
	if (!m_pPile == NULL)
	{//なぜかクリアスクリーン使うと挙動がおかしいため、空白で代用
		printf("ライン%d        ", m_pPile->Get_Line());
		gotoxy(1, 2);
		printf("攻撃力%d        ", m_pPile->GetAttack());
	}
}

void DebugConsole::SetPile(PileBanker * pPile)
{
	m_pPile = pPile;
}
