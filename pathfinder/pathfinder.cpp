#include "pch.h"

#include "pathfinder.h"
#include "hooks.h"

Pathfinder::Pathfinder()
	: replayHandler(1)
{}

Pathfinder* Pathfinder::GetInstance()
{
	if (!instance) instance = new Pathfinder;
	return instance;
}

void Pathfinder::OnInit(gd::PlayLayer* playLayer)
{
	printf("Please input the level length (in seconds): ");
	int time;
	std::cin >> time;

	replayHandler = ReplayHandler(fps * time);

	//CCDirector::sharedDirector()->setAnimationInterval(1.0 / fps);
	CCDirector::sharedDirector()->setAnimationInterval(1.0 / 50000.0f);
}

void Pathfinder::OnReset(gd::PlayLayer* playLayer)
{
	frame = 0;
	bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
	Hooks::PlayLayer::releaseButton(playLayer, NULL, true ^ flip);
	printf("Progress: %f%%\r", replayHandler.GetProgress());
}

void Pathfinder::Update(gd::PlayLayer* playLayer)
{
	if (IsDone()) return;

	bool press = replayHandler.GetClick(frame);
	auto func = press ? Hooks::PlayLayer::pushButton : Hooks::PlayLayer::releaseButton;
	bool flip = gd::GameManager::sharedState()->getGameVariable("0010");
	func(playLayer, NULL, true ^ flip);

	++frame;
}

void Pathfinder::Success()
{
	//printf("SUCCESS!\n");
	replayHandler.Success();
	if (replayHandler.IsDone())
	{
		printf("Done.\n");
		printf("Difficulty rating: %f%%\n", replayHandler.GetDifficulty());
	}
}

void Pathfinder::Fail(gd::PlayLayer* playLayer)
{
	//printf("FAIL! frame=%d\n", frame);
	replayHandler.Fail(frame);
	if (replayHandler.IsDone())
	{
		printf("Done.\n");
		printf("Difficulty rating: %f%%\n", replayHandler.GetDifficulty());
		Hooks::PlayLayer::levelComplete(playLayer);
	}
	else
		Hooks::PlayLayer::resetLevel_h(playLayer);
}

bool Pathfinder::IsDone() const
{
	return replayHandler.IsDone();
}

float Pathfinder::GetDeltaTime() const
{
	return 1.0f / fps;
}
