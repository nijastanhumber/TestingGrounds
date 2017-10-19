// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol route
	APawn *ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute *PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Warn about empty patrol routes
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index++]);

	// Cycle the index
	Index %= PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}


