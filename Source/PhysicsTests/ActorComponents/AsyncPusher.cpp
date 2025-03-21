#include "AsyncPusher.h"

#include "PhysicsProxy/SingleParticlePhysicsProxy.h"

UAsyncPusher::UAsyncPusher()
{
	SetAsyncPhysicsTickEnabled(true);
}

void UAsyncPusher::BeginPlay()
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

void UAsyncPusher::AsyncPhysicsTickComponent(float DeltaTime, float SimTime)
{
	Super::AsyncPhysicsTickComponent(DeltaTime, SimTime);

	// Abort if primitive component was not found.
	if (!IsValid(PrimitiveComponent)) return;

	const FVector WorldSpacePusherLocation = GetComponentLocation();
	const FVector WorldSpacePushVector = GetForwardVector() * PushForce * DeltaTime;

	FBodyInstanceAsyncPhysicsTickHandle BodyInstanceAsyncPhysicsTickHandle = PrimitiveComponent->GetBodyInstanceAsyncPhysicsTickHandle();
	const FVector WorldSpaceCenterOfMass = BodyInstanceAsyncPhysicsTickHandle->CenterOfMass();
	const FVector WorldSpaceMomentArm = WorldSpacePusherLocation - WorldSpaceCenterOfMass;
	const FVector WorldSpaceTorque = WorldSpaceMomentArm.Cross(WorldSpacePushVector);

	BodyInstanceAsyncPhysicsTickHandle->AddForce(WorldSpacePushVector);
	BodyInstanceAsyncPhysicsTickHandle->AddTorque(WorldSpaceTorque);
}