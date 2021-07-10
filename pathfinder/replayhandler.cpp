#include "pch.h"

#include "replayhandler.h"

void ReplayHandler::NextReplay()
{
	++replayID;
	if (replayID >= totalNoOfReplays) return;

	currentReplay = Replay(replaySize);
	for (size_t i = 0; i < replaySize; ++i)
		if (replayID & (1 << (replaySize - i - 1)))
			currentReplay.Set(i, true);
}

ReplayHandler::ReplayHandler(size_t replaySize)
	: currentReplay(replaySize), replaySize(replaySize)
{
	totalNoOfReplays = 1 << replaySize; // pow(2, replaySize); pow func doesnt work for me idk why
	printf("replaySize = %d\n", replaySize);
	printf("totalNoOfReplays = %d\n", totalNoOfReplays);
}

void ReplayHandler::Fail(size_t frame)
{
	//replayID += (1u << (replaySize - frame)) - 1u; // pow(2, replaySize - frame) - 1; pow func doesnt work for me idk why
	bool orig = currentReplay[frame];
	while (currentReplay[frame] == orig)
		NextReplay();
}

void ReplayHandler::Success()
{
	successfulReplays.push_back(replayID);
	NextReplay();
}

bool ReplayHandler::IsDone() const
{
	return replayID >= totalNoOfReplays - 1;
}

float ReplayHandler::GetDifficulty() const
{
	return 100.0f - ((float)successfulReplays.size() / (float)totalNoOfReplays * 100.0f);
}

bool ReplayHandler::GetClick(size_t frame) const
{
	return currentReplay[frame];
}

float ReplayHandler::GetProgress() const
{
	return min(100.0f, (float)replayID / float(totalNoOfReplays - 1) * 100.0f);
}
