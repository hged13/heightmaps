// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "VizData.h"
#include "Kismet/GameplayStatics.h"
#include "Landscape.h"
#include "LandscapeStreamingProxy.h"
#include "LandscapeInfo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VizData.generated.h"

UCLASS()
class DATAVIZ_API AVizData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVizData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		TArray<float> DataArray; // Your 27x31 array data should go here

	UFUNCTION(BlueprintCallable)
		void ColorizeLandscape();

	FLinearColor GetColorBasedOnValue(float Value);

};
