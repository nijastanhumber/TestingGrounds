// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
	: ATestingGroundsGameMode()
{
	NavMeshBoundsVoluePool = CreateDefaultSubobject<UActorPool>(FName("NavMeshBoundsVolumePool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	if (GetWorld())
	{
		TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
		while (VolumeIterator)
		{
			AddToPool(*VolumeIterator);
			++VolumeIterator;
		}
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
	NavMeshBoundsVoluePool->Add(VolumeToAdd);
}


