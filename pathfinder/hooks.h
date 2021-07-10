#ifndef HOOKS_H
#define HOOKS_H

using namespace cocos2d;

namespace Hooks
{
	bool Initialise();

	namespace PlayLayer
	{
		THISCALL_HOOK(void, scheduleUpdate, CCScheduler* self, float dt);
		THISCALL_HOOK(void, update, gd::PlayLayer* self, float dt);
		THISCALL_HOOK(void, init, gd::PlayLayer* self, gd::GJGameLevel* GJLevel);
		THISCALL_HOOK(void, destroyPlayer, gd::PlayLayer* self, gd::PlayerObject* player, int param);
		THISCALL_HOOK_NO_ARGS(void*, levelComplete, gd::PlayLayer* self);
		THISCALL_HOOK_NO_ARGS(void, resetLevel, gd::PlayLayer* self);

		THISCALL_HOOK(uint32_t, pushButton, gd::PlayLayer* self, int param, bool button);
		THISCALL_HOOK(uint32_t, releaseButton, gd::PlayLayer* self, int param, bool button);
	}
}

#endif // HOOKS_H
