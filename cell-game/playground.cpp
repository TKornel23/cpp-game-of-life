#include "playground.h"
#include <iostream>
#include <random>


Playground::Playground(const uint16_t width, const uint16_t height, const float aliveperc) {
	this->GenerateGrid(width, height, aliveperc);
}

Playground::Playground(const uint16_t size) {
	this->GenerateGrid(size, size, 0.1f);
}

Playground::Playground(const uint16_t width, const uint16_t height) {
	this->GenerateGrid(width, height, 0.1f);
}

Playground::Playground(const uint16_t size, const float aliveperc) {
	this->GenerateGrid(size, size, aliveperc);
}

Playground::Playground(const uint16_t height, const uint16_t width, const uint16_t top, const uint16_t left, const std::vector<std::vector<bool>>& Vektor)
{
	for (uint16_t i = left; i < width + left; i++)
	{
		std::vector<bool> innerVector;
		for (uint16_t j = top; j < height + top; j++)
		{
			innerVector.emplace_back(Vektor[i][j]);
		}
		this->grid.emplace_back(innerVector);
	}
}


uint8_t Playground::getState(const bool current_state, const uint8_t n) const
{
	if (current_state && (n < 2)) {
		return 0;
	}
	else if (current_state && (n == 2 || n == 3))
	{
		return 1;
	}
	else if (current_state && (n > 3))
	{
		return 0;
	}
	else if ((current_state == 0) && (n == 3))
	{
		return 1;
	}

	return current_state;
}

void Playground::PlayGame()
{
	printGrid(this->grid);
	std::vector<std::vector<bool>> tmpGrid(this->grid.size(), std::vector<bool>(this->grid[0].size(), 0));
	uint8_t k = 0;
	while(k < 100 && DeadCellsCount(grid) < grid.size() * grid[0].size())
	{
		for (uint16_t i = 0; i < this->grid.size()-1; i++)
		{
			for (uint16_t j = 0; j < this->grid[0].size()-1; j++)
			{
				uint8_t local_n = getNeighbours(i, j, grid);
				bool survival = getState(grid[i][j], local_n);
				tmpGrid[i][j] = survival;
			}
		}
		printGrid(tmpGrid);
		grid = tmpGrid;
		std::cin.get();
		k++;
	}
}

uint16_t Playground::DeadCellsCount(const std::vector<std::vector<bool>>& grid) const
{
	uint16_t count = 0;
	for (uint16_t i = 0; i < this->grid.size(); i++)
	{
		for (uint16_t j = 0; j < this->grid[0].size(); j++)
		{
			if (grid[i][j] == 0) {
				count++;
			}
		}
	}
	return count;
}

std::vector<std::vector<bool>>& Playground::GetPlayground()
{
	return grid;
}

uint8_t Playground::getNeighbours(const uint16_t i, const uint16_t j, const std::vector<std::vector<bool> >& grid) const
{
	uint8_t count = 0;

	if ((i > 0) && (j > 0))                         // Top Left
	{
		if (grid[i - 1][j - 1]) {
			count++;
		}
	}

	if (i > 0)                                      // Top Mid
	{
		if (grid[i - 1][j]) {
			count++;
		}
	}

	if ((i > 0) && (j < grid.size() - 1))               // Top Right
	{
		if (grid[i - 1][j + 1]) {
			count++;
		}
	}

	if ((j > 0))                                    // Mid Left
	{
		if (grid[i][j - 1]) {
			count++;
		}
	}

	if (j < grid.size() - 1)                            // Mid Right
	{
		if (grid[i][j + 1]) {
			count++;
		}
	}

	if ((j > 0) && (i < grid.size() - 1))               // Bottom Left
	{
		if (grid[i + 1][j - 1]) {
			count++;
		}
	}

	if (i < grid.size() - 1)                            // Bottom Mid
	{
		if (grid[i + 1][j]) {
			count++;
		}
	}

	if ((i < grid.size() - 1) && (j < grid.size() - 1))     // Bottom Right
	{
		if (grid[i + 1][j + 1]) {
			count++;
		}
	}

	return count;
}

void Playground::printGrid(const std::vector<std::vector<bool>> grid) const
{
	std::cout << std::endl;

	for (uint16_t i = 0; i < grid.size(); i++)
	{
		for (uint16_t j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j])
			{
				std::cout << "X";
			}
			else
			{
				std::cout << "+";
			}
		}
		std::cout << std::endl;
	}
}

void Playground::GenerateGrid(const uint16_t width, const uint16_t height, const float aliveperc) {
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<double> normal_disc(0, 1);

	std::vector<bool> innerVector;
	for (uint16_t i = 0; i < width; i++)
	{
		std::vector<bool> innerVector;
		for (uint16_t j = 0; j < height; j++)
		{
			if (normal_disc(re) <= aliveperc) {
				innerVector.emplace_back(1);
			}
			else {
				innerVector.emplace_back(0);
			}
		}
		this->grid.emplace_back(innerVector);
	}
}
