/**
 * @file helperfunctions.cpp
 * @brief implementation file for helper functions
 */

#include <numeric>

#include "helperfunctions.hpp"

std::vector<std::vector<uint8_t>> integerPartitions(uint8_t _integer,
	uint8_t _partcount, uint8_t _minpart, uint8_t _maxpart)
{
	if(!_integer || !_partcount || _integer < _partcount || _integer < _minpart
		|| _minpart > _maxpart) return {};
	if(_partcount == 1) return {{_integer}};
	std::vector<std::vector<uint8_t>> partitions;
	std::vector<uint8_t> current(_partcount, 1);//TODO init with _minpart?
	current[0] = _integer - _partcount + 1;
	while (true){
		while (true){
			if(current.front() <= _maxpart && current.back() >= _minpart)
				partitions.push_back(current);
			if(current[1] >= current[0] - 1){
				if(_partcount < 3) return partitions;
				break;
			}
			current[0]--;
			current[1]++;
		}
		uint8_t index = 2;
		uint8_t newFirst = current[0] + current[1] - 1;
		if(current[index] >= current[0]-1){
			do{	
				newFirst += current[index];
				index++;
				if(index >= _partcount) return partitions;
			}while(current[index] >= current[0] - 1);
		}
		current[index]++;
		uint8_t newFill = current[index];
		index--;
		while (index > 0){
			current[index] = newFill;
			newFirst -= newFill;
			index--;
		}
		current[0] = newFirst;
	}
}

bool isValidNumberSequence(std::string_view _sequence)
{
	if(_sequence.size() == 0) return false;
	for(const char& chr : _sequence)
	{
		if(std::isdigit(chr) == false) return false;
	}
	return true;
}

std::vector<std::string_view> partitionString(std::string_view _string, const std::vector<uint8_t>& _partition)
{
	size_t partitionSize = std::accumulate(begin(_partition), end(_partition), 0ULL);
	if(_string.size() != partitionSize)	return {};//? 0?
	std::vector<std::string_view> partitioned;
	partitioned.reserve(_partition.size());
	uint8_t beginOffset = 0;
	for(uint8_t count : _partition){
		partitioned.push_back(_string.substr(beginOffset, count));
		beginOffset += count;
	}
	return partitioned;
}