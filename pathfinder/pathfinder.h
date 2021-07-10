#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "replayhandler.h"

class Pathfinder
{
private:
	static inline Pathfinder* instance = nullptr;
	ReplayHandler replayHandler;
	size_t frame = 0;
	float fps = 60.0f;

	Pathfinder();
public:
	static Pathfinder* GetInstance();

	void OnInit(gd::PlayLayer* playLayer);
	void OnReset(gd::PlayLayer* playLayer);
	void Update(gd::PlayLayer* playLayer);
	void Success();
	void Fail(gd::PlayLayer* playLayer);

	bool IsDone() const;
	float GetDeltaTime() const;
	float GetDifficulty() const;

	Pathfinder(const Pathfinder&) = delete;
	Pathfinder(Pathfinder&&) = delete;
};

#endif // PATHFINDER_H
