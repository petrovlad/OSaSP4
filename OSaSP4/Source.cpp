#include <stdio.h>
#include "TaskQueue.h"
#include "TaskPerformer.h"
#include <string>
#include <fstream>
#include <vector>

#define MAX_THREADS_NUMBER 5
#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

typedef std::vector<std::string> TstringVector;

void addTask(TstringVector *vect, TaskQueue &queue) 
{
	queue.pushTask([vect]() { sort(vect->begin(), vect->end()); });
}

TstringVector mergeTwo(const TstringVector &firstVector, const TstringVector &secondVector)
{
	size_t firstSize = firstVector.size();
	size_t secondSize = secondVector.size();

	TstringVector result;
	result.reserve(firstSize + secondSize);
	size_t i = 0, j = 0;
	while (i < firstSize && j < secondSize) {

		if (firstVector[i] <= secondVector[j])
		{
			result.push_back(firstVector[i]);
			i++;
		}
		else
		{
			result.push_back(secondVector[j]);
			j++;
		}
	}

	while (i < firstSize)
	{
		result.push_back(firstVector[i]);
		i++;
	}

	while (j < secondSize)
	{
		result.push_back(secondVector[j]);
		j++;
	}

	return result;
}

TstringVector mergeVectors(std::vector<TstringVector*>*& vectorParts) 
{
	TstringVector tmpVector;
	if (vectorParts->size() > 0) {
		tmpVector = *(*vectorParts)[0];
	}
	for (size_t i = 1; i < vectorParts->size(); i++) {
		tmpVector = mergeTwo(tmpVector, *(*vectorParts)[i]);
	}
	return tmpVector;
}

void splitVectors(TaskQueue &taskQueue, TstringVector*& vectorStrings, 
					std::vector<TstringVector*>*& vectorParts, int threadsCount) 
{
	auto onePartCount = (int)floor((((double)vectorStrings->size()) / threadsCount) + .5);
	for (size_t i = 0; i < vectorStrings->size(); i += onePartCount) {
		auto* newVector = new std::vector<std::string>;
		vectorParts->push_back(newVector);
		for (size_t j = i; j < i + onePartCount; j++) {
			if (j < vectorStrings->size()) {
				std::string str = (*vectorStrings)[j];
				newVector->push_back(str);
			}
		}
		addTask(newVector, taskQueue);
	}
}

int main() 
{
	const std::string fileName = INPUT_FILENAME;
	std::ifstream inFile(fileName);

	if (!inFile.good()) {
		printf("Can't open file.");
		return -1;
	}
	auto* stringVector = new TstringVector();
	auto* partsVector = new std::vector<TstringVector*>();
	
	std::string line;
	while (getline(inFile, line)) {
		std::string new_line;
		new_line = line + "\n";

		if (new_line.size() != 0)
			stringVector->push_back(new_line);
	}
	inFile.close();


	TaskQueue taskQueue;
	int numOfThreads = MAX_THREADS_NUMBER;

	splitVectors(taskQueue, stringVector, partsVector, numOfThreads);
	try {
		TaskPerformer taskPerformer(taskQueue, numOfThreads);
		taskPerformer.Perform();
	}
	catch (const char* exceptionMessage) {
		printf("Exception: %s\n", exceptionMessage);
	}

	TstringVector vector = mergeVectors(partsVector);


	std::ofstream outFile(OUTPUT_FILENAME);
	if (outFile.is_open()) {
		for (auto str : vector) {
			outFile.write(str.c_str(), str.length());
		}
	}
	else {
		printf("Can't open output file");
	}

	return 0;
}