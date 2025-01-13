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

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;
};
