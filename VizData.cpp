// Fill out your copyright notice in the Description page of Project Settings.


#include "VizData.h"

// Sets default values
AVizData::AVizData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVizData::BeginPlay()
{
	Super::BeginPlay();
    ColorizeLandscape();
	
}

// Called every frame
void AVizData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FLinearColor AVizData::GetColorBasedOnValue(float Value)
{
    // Simple gradient from blue to red based on value
    // Assuming your data is normalized between 0 and 1
    return FLinearColor(Value, 0.0f, 1.0f - Value);
}

void AVizData::ColorizeLandscape()
{

    int32 TotalEntries = 31 * 27;
    for (int32 i = 0; i < TotalEntries; i++)
    {
        float RandomValue = FMath::FRand(); // Generates a random float between 0 and 1
        DataArray.Add(RandomValue);
    }
    // Get all landscapes in the scene
    TArray<AActor*> Landscapes;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALandscapeStreamingProxy::StaticClass(), Landscapes);

    if (Landscapes.Num() > 0)
    {
        ALandscapeStreamingProxy* MyLandscape = Cast<ALandscapeStreamingProxy>(Landscapes[0]);

        if (MyLandscape)
        {


         
                // Print the name of the landscape to the screen
            FString LandscapeName = MyLandscape->GetActorLabel();

           

            ULandscapeInfo* LandscapeInfo = MyLandscape->GetLandscapeInfo();
            TMap<FIntPoint, ULandscapeComponent*>& ComponentMap = LandscapeInfo->XYtoComponentMap;
            TMap<FIntPoint, ULandscapeComponent*>::TConstIterator It(ComponentMap);

            // Access the key and value from the iterator
            FIntPoint Key = It->Key;
            ULandscapeComponent* Component = It->Value;

            // Now, you can use the Component pointer for further operations


           
            FIntRect ComponentRect = Component->GetComponentExtent();
            int totalcount = 0;

            for (int x = ComponentRect.Min.X; x < ComponentRect.Max.X; x++)
            {
                for (int y = ComponentRect.Min.Y; y < ComponentRect.Max.Y; y++)
                {
                    totalcount = totalcount + 1;

                }
            }

            
           
            
            


            }


            // Assuming MyLandscape is your landscape actor

            for (ULandscapeComponent* LandscapeComponent : MyLandscape->LandscapeComponents)
            {
                UMaterialInstanceDynamic* DynamicMaterial = LandscapeComponent->CreateDynamicMaterialInstance(0, LandscapeComponent->GetMaterial(0));

                if (DynamicMaterial)
                {
                    DynamicMaterial->SetVectorParameterValue(FName("Param"), FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)); // This sets the color to pure red

                    // If you need to set the dynamic material back to the component:
                    LandscapeComponent->SetMaterial(0, DynamicMaterial);
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("landscape material worked"));


                    UMaterialInterface* CurrentMaterial = LandscapeComponent->GetMaterial(0);
                    if (UMaterialInstanceDynamic* DynamicMat = Cast<UMaterialInstanceDynamic>(CurrentMaterial))
                    {
                        FLinearColor debugColor = DynamicMat->K2_GetVectorParameterValue(FName("Param"));
                        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, debugColor.ToString());
                    }


                }
            }
           



            //UTexture2D* DynamicTexture = UTexture2D::CreateTransient(32, 32);
            //FTexture2DMipMap& Mip = DynamicTexture->GetPlatformData()->Mips[0];


            //void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
            //FColor* TextureData = reinterpret_cast<FColor*>(Data);



            //int32 Index = 0;
            //for (int32 i = 0; i < 32; i++)
            //{
            //    for (int32 j = 0; j < 32; j++)
            //    {
            //        if (Index < DataArray.Num())
            //        {
            //            float Value = DataArray[Index];

            //            FLinearColor Color(0.0f, 0.0f, 1.0f, 1.0f);  // pure blue color
            //            // Set the vertex color for this specific vertex on the landscape
            //            // This might require interfacing with landscape components or data structures

            //            TextureData[Index] = Color.ToFColor(false);  // Convert linear color to FColor

            //            Index++;
            //        }
            //    }
            //}
            //Mip.BulkData.Unlock();  // Unlock the data when done.

            //DynamicTexture->UpdateResource();
            //UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, TEXT("/Game/StarterContent/LandscapeMaterial.LandscapeMaterial"))), this);
            //DynamicMaterial->SetTextureParameterValue(TEXT("Param"), DynamicTexture);


            //if (DynamicMaterial) {


            //}

            //MyLandscape->LandscapeMaterial = DynamicMaterial;
            MyLandscape->PostEditChange();
            MyLandscape->ReregisterAllComponents();

            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End of code reached!"));






        }
    }
