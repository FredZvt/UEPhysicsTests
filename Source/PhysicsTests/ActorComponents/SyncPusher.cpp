#include "SyncPusher.h"

USyncPusher::USyncPusher()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USyncPusher::BeginPlay()
{
	Super::BeginPlay();

	const AActor* OwnerActor = GetOwner();
	if (!IsValid(OwnerActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("USyncPusher::BeginPlay: OwnerActor is not valid."));
		return;
	}

	PrimitiveComponent = OwnerActor->GetComponentByClass<UPrimitiveComponent>();
	if (!IsValid(PrimitiveComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("USyncPusher::BeginPlay: PrimitiveComponent is not valid."));
	}
}

void USyncPusher::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Abort if primitive component was not found.
	if (!IsValid(PrimitiveComponent)) return;

	const FVector WorldSpacePusherLocation = GetComponentLocation();
	const FVector WorldSpacePushVector = GetForwardVector() * PushForce * DeltaTime;
	PrimitiveComponent->AddForceAtLocation(WorldSpacePushVector, WorldSpacePusherLocation);
}
