#include <algorithm>
#include <numeric>

#include "helperfunctions.hpp"

std::vector<std::vector<size_t>> integerPartitions(size_t integer, size_t partcount, size_t minpart, size_t maxpart)
{
	if(integer == 0 || partcount == 0 || integer < partcount || integer < minpart || minpart > maxpart ||
	    partcount * minpart > integer || partcount * maxpart < integer)
	{
		return {};
	}
	if(partcount == 1)
	{
		return {{integer}};
	}

	std::vector<std::vector<size_t>> partitions;
	std::vector<size_t> current(partcount, 1);
	current[0] = integer - partcount + 1;

	while(true)
	{
		while(true)
		{
			if(current.front() <= maxpart && current.back() >= minpart)
			{
				partitions.push_back(current);
			}
			if(current[1] >= current[0] - 1)
			{
				if(partcount < 3)
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
				if(index >= partcount)
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

bool isValidNumberSequence(std::string_view sequence)
{
	return std::all_of(std::begin(sequence), std::end(sequence),
	           [](char chr)
	           {
		           return static_cast<bool>(std::isdigit(chr));
	           }) &&
	       !sequence.empty();
}

std::vector<std::string_view> partitionString(std::string_view string, const std::vector<size_t>& partition)
{
	size_t partitionSize = std::accumulate(begin(partition), end(partition), 0ULL);
	if(string.size() != partitionSize)
	{
		return {};
	}
	std::vector<std::string_view> partitioned;
	partitioned.reserve(partition.size());
	size_t beginOffset = 0;
	for(size_t count : partition)
	{
		partitioned.push_back(string.substr(beginOffset, count));
		beginOffset += count;
	}
	return partitioned;
}

static constexpr size_t FACTORIAL_RESULTS[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
    479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000, 6402373705728000,
    121645100408832000, 2432902008176640000};
size_t factorial(size_t number)
{
	if(number < ((sizeof(FACTORIAL_RESULTS)) / (sizeof(*FACTORIAL_RESULTS))))
	{
		return FACTORIAL_RESULTS[number];
	}
	return 0;
}

size_t countUnique(const std::vector<size_t>& sorted)
{
	if(sorted.empty())
	{
		return 0;
	}
	size_t count = 1;
	[[maybe_unused]] auto _ = std::adjacent_find(std::begin(sorted), std::end(sorted),
	    [&](const size_t& lhs, const size_t& rhs)
	    {
		    count += lhs != rhs;
		    return false;
	    });
	return count;
}

size_t permutationsWithRepetitions(const std::vector<size_t>& partition)
{
	if(partition.empty())
	{
		return 0;
	}
	std::vector<size_t> counts{1};
	[[maybe_unused]] auto _ = std::adjacent_find(std::begin(partition), std::end(partition),
	    [&](const size_t& lhs, const size_t& rhs)
	    {
		    if(lhs != rhs)
		    {
			    counts.push_back(1);
		    }
		    else
		    {
			    counts.back()++;
		    }
		    return false;
	    });
	const size_t divisor = std::accumulate(std::begin(counts), std::end(counts), size_t(1),
	    [](const size_t& total, const size_t& part)
	    {
		    return total * factorial(part);
	    });
	const size_t dividend = factorial(partition.size());
	return dividend / divisor;
}
