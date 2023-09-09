// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MERINO23_API IndexIter
{
public:
	IndexIter(int Size);
	IndexIter(int StartIndex, int StartSize);
	~IndexIter();
	void ReorderIndexQueue(int NewStartIndex);
	void RebuildIndexQueue(int NewStartIndex, int NewSize);
	int GetNextIndex();

private:
	void BuildIndexQueue();
	int StartingSize;
	int StartIndex;
	TQueue<int> IndexQueue;
};
