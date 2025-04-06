#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SyncPusher.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PHYSICSTESTS_API USyncPusher : public USceneComponent
{
	GENERATED_BODY()

public:

	USyncPusher();

	virtual void BeginPlay() override;
	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	float PushForce = 500000.f;
	
private:
	
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> PrimitiveComponent;
};
