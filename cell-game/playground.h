#pragma once
#include <vector>

class Playground {
public:
	Playground(uint16_t const width, const uint16_t height, const float aliveperc);
	Playground(const uint16_t size);
	Playground(const uint16_t width, const uint16_t height);
	Playground(const uint16_t size, const float aliveperc);
	Playground(const uint16_t height, const uint16_t width, const uint16_t top, const uint16_t left, const std::vector<std::vector<bool> >& Vektor);
public:
	void GenerateGrid(const uint16_t width, const uint16_t height, const float aliveperc);
	void printGrid(const std::vector<std::vector<bool>> grid) const;
	void PlayGame();
	uint8_t getNeighbours(const uint16_t i, const uint16_t j, const std::vector<std::vector<bool> >& grid) const;
	uint8_t getState(const bool current_state, const uint8_t n) const;
	uint16_t DeadCellsCount(const std::vector<std::vector<bool> >& grid) const;
	std::vector<std::vector<bool>>& GetPlayground();
private:
	std::vector<std::vector<bool>> grid;
};
