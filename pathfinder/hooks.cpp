#include "pch.h"

#include "hooks.h"
#include "pathfinder.h"

bool* IsDead(gd::PlayLayer* playLayer)
{
	return ReCa<bool*>(ReCa<uint32_t>(playLayer) + 0x39C);
}

bool Hooks::Initialise()
{
	if (MH_Initialize() != MH_OK) return false;

	HMODULE libcocos2d = GetModuleHandleA("libcocos2d.dll");
	if (!libcocos2d)
		throw 1, "Failed to find libcocos2d.dll";

	CREATE_HOOK(GetProcAddress(libcocos2d, "?update@CCScheduler@cocos2d@@UAEXM@Z"), PlayLayer::scheduleUpdate);

	CREATE_GD_HOOK(0x2029C0, PlayLayer::update);
	CREATE_GD_HOOK(0x1FB780, PlayLayer::init);
	CREATE_GD_HOOK(0x20A1A0, PlayLayer::destroyPlayer);
	CREATE_GD_HOOK(0x1FD3D0, PlayLayer::levelComplete);
	CREATE_GD_HOOK(0x20BF00, PlayLayer::resetLevel);
	CREATE_GD_HOOK(0x111500, PlayLayer::pushButton);
	CREATE_GD_HOOK(0x111660, PlayLayer::releaseButton);

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) return false;

	return true;
}

void __fastcall Hooks::PlayLayer::scheduleUpdate_h(CCScheduler* self, void*, float dt)
{
	scheduleUpdate(self, Pathfinder::GetInstance()->GetDeltaTime());
}

void __fastcall Hooks::PlayLayer::update_h(gd::PlayLayer* self, void*, float dt)
{
	if (!Pathfinder::GetInstance()->IsDone())
	{
		if (!*IsDead(self) && self->m_player1->position.x != 0.0f)
			Pathfinder::GetInstance()->Update(self);
		update(self, dt);
	}
}

void __fastcall Hooks::PlayLayer::init_h(gd::PlayLayer* self, void*, gd::GJGameLevel* GJLevel)
{
	init(self, GJLevel);
	Pathfinder::GetInstance()->OnInit(self);
}

void __fastcall Hooks::PlayLayer::destroyPlayer_h(gd::PlayLayer* self, void*, gd::PlayerObject* player, int param)
{
	destroyPlayer(self, player, param);
	if (*IsDead(self))
		Pathfinder::GetInstance()->Fail(self);
}

void* __fastcall Hooks::PlayLayer::levelComplete_h(gd::PlayLayer* self)
{
	Pathfinder::GetInstance()->Success();
	if (Pathfinder::GetInstance()->IsDone())
		return levelComplete(self);
	resetLevel_h(self);
	return nullptr;
}

void __fastcall Hooks::PlayLayer::resetLevel_h(gd::PlayLayer* self)
{
	Pathfinder::GetInstance()->OnReset(self);
	resetLevel(self);
}

uint32_t __fastcall Hooks::PlayLayer::pushButton_h(gd::PlayLayer* self, void*, int param, bool button)
{
	return 0;
}

uint32_t __fastcall Hooks::PlayLayer::releaseButton_h(gd::PlayLayer* self, void*, int param, bool button)
{
	return 0;
}
