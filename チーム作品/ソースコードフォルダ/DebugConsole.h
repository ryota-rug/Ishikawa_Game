#ifndef __DEBUGCONSOLE_H__
#define __DEBUGCONSOLE_H__

#include "DirectXTex/Texture.h"
#include "PileBankerBase.h"
class DebugConsole
{
public:
	DebugConsole();
	~DebugConsole();
	void Update();
	void SetPile(PileBanker*);

private:
	const COORD coord = {40,20};
	HANDLE hStdout;
	SMALL_RECT rectConsoleSize;
	PileBanker* m_pPile;
};



#endif // !__DEBUGCONSOLE_H__
