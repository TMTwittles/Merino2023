// Fill out your copyright notice in the Description page of Project Settings.
#include "IndexIter.h"

IndexIter::IndexIter(int StartSize)
{
	StartIndex = 0;
	StartingSize = StartSize;
	BuildIndexQueue();
}

IndexIter::IndexIter(int StartIndex, int StartSize)
{
	this->StartIndex = StartIndex;
	this->StartingSize = StartSize;
	BuildIndexQueue();
}

IndexIter::~IndexIter()
{
	StartingSize = -1;
	IndexQueue.Empty();
}

void IndexIter::ReorderIndexQueue(int NewStartIndex)
{
	StartIndex = NewStartIndex;
	BuildIndexQueue();
}

void IndexIter::RebuildIndexQueue(int NewStartIndex, int NewSize)
{
	StartIndex = NewStartIndex;
	StartingSize = NewSize;
	BuildIndexQueue();
}

int IndexIter::GetNextIndex()
{
	int NextIndex = -1;
	if (IndexQueue.Dequeue(NextIndex) == false)
	{
		BuildIndexQueue();
		IndexQueue.Dequeue(NextIndex);
	}
	return NextIndex;
}

void IndexIter::BuildIndexQueue()
{
	if (StartIndex >= StartingSize)
	{
		UE_LOG(LogClass, Error, TEXT("Error: Unable to build index queue, start index {%i} greater than start size {%i}"), StartIndex, StartingSize);
		return;
	}
	
	IndexQueue.Empty();
	for (int i = StartIndex; i < StartingSize; i++)
	{
		IndexQueue.Enqueue(i);
	}
	// Populate remaining values.
	for (int i = 0; i < StartIndex; i++)
	{
		IndexQueue.Enqueue(i);	
	}
}






