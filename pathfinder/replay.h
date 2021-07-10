#ifndef REPLAY_H
#define REPLAY_H

#include <vector>
#include <iostream>

class Replay
{
private:
	std::vector<unsigned char> data;
	size_t bitSize;
public:
	explicit Replay(size_t size);

	bool operator[](size_t index) const;
	void Set(size_t index, bool val);

	std::string ToString(bool decoration=true) const;
};

#endif // REPLAY_H
