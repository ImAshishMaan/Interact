#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class MEGA_API AGameHUD : public AHUD {
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
	void DrawCrosshair(UTexture2D* TextureToDraw, FVector2D& ViewPortSize); // call this for crosshair drawing at run time

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};
