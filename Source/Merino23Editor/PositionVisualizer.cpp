// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionVisualizer.h"

void FPositionVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	FComponentVisualizer::DrawVisualization(Component, View, PDI);
}

FPositionVisualizer::FPositionVisualizer()
{
}

FPositionVisualizer::~FPositionVisualizer()
{
}
