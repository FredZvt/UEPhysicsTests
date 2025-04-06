#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AsyncPusher.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PHYSICSTESTS_API UAsyncPusher : public USceneComponent
{
	GENERATED_BODY()

public:

	UAsyncPusher();

	virtual void BeginPlay() override;

	virtual void AsyncPhysicsTickComponent(
		float DeltaTime,
		float SimTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float PushForce = 500000.f;
	
private:
	
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> PrimitiveComponent;
};
