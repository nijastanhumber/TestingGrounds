// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

public:
	FVector Location;
	float Rotation;
	float Scale;
};

class UActorPool;
UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinSpawningExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxSpawningExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool *InPool);

private:
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition &SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition &SpawnPosition);

	TArray<FSpawnPosition> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	bool CastSphere(FVector Location, float Radius);

	void PositionNavMeshBoundsVolume();
	
	UActorPool *Pool;

	AActor *NavMeshBoundsVolume;

private:

	template<typename T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);
};