#include <algorithm>
#include <numeric>

#include "helperfunctions.hpp"

std::vector<std::vector<size_t>> integerPartitions(size_t _integer, size_t _partcount, size_t _minpart, size_t _maxpart)
{
	if(!_integer || !_partcount || _integer < _partcount || _integer < _minpart || _minpart > _maxpart ||
	   _partcount * _minpart > _integer || _partcount * _maxpart < _integer)
	{
		return {};
	}
	if(_partcount == 1)
	{
		return {{_integer}};
	}

	std::vector<std::vector<size_t>> partitions;
	std::vector<size_t> current(_partcount, 1);
	current[0] = _integer - _partcount + 1;

	while(true)
	{
		while(true)
		{
			if(current.front() <= _maxpart && current.back() >= _minpart)
			{
				partitions.push_back(current);
			}
			if(current[1] >= current[0] - 1)
			{
				if(_partcount < 3)
				{
					return partitions;
				}
				break;
			}
			current[0]--;
			current[1]++;
		}

		size_t index = 2;
		size_t newFirst = current[0] + current[1] - 1;
		if(current[index] >= current[0] - 1)
		{
			do
			{
				newFirst += current[index];
				index++;
				if(index >= _partcount)
				{
					return partitions;
				}
			} while(current[index] >= current[0] - 1);
		}

		current[index]++;
		size_t newFill = current[index];
		index--;
		while(index > 0)
		{
			current[index] = newFill;
			newFirst -= newFill;
			index--;
		}
		current[0] = newFirst;
	}
}

bool isValidNumberSequence(std::string_view _sequence)
{
	return std::all_of(
	           std::begin(_sequence), std::end(_sequence),
	           [](char chr)
	           {
		           return static_cast<bool>(std::isdigit(chr));
	           }) &&
	       !_sequence.empty();
}

std::vector<std::string_view> partitionString(std::string_view _string, const std::vector<size_t>& _partition)
{
	size_t partitionSize = std::accumulate(begin(_partition), end(_partition), 0ULL);
	if(_string.size() != partitionSize)
	{
		return {};
	}
	std::vector<std::string_view> partitioned;
	partitioned.reserve(_partition.size());
	size_t beginOffset = 0;
	for(size_t count : _partition)
	{
		partitioned.push_back(_string.substr(beginOffset, count));
		beginOffset += count;
	}
	return partitioned;
}
