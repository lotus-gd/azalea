#ifndef REPLAYHANDLER_H
#define REPLAYHANDLER_H

#include "replay.h"

class ReplayHandler
{
private:
	Replay currentReplay;
	size_t replaySize, replayID = 0, totalNoOfReplays;
	std::vector<size_t> successfulReplays;

	void NextReplay();
public:
	explicit ReplayHandler(size_t replaySize);

	void Fail(size_t frame);
	void Success();

	bool IsDone() const;
	float GetDifficulty() const;
	bool GetClick(size_t frame) const;
	float GetProgress() const;
};

#endif // REPLAYHANDLER_H
