#include "GameHUD.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Texture2D.h"

void AGameHUD::DrawHUD() {
	Super::DrawHUD();

	FVector2D ViewPortSize;
	if(GEngine) {
		GEngine->GameViewport->GetViewportSize(ViewPortSize);

		DrawCrosshair(CrosshairTexture, ViewPortSize);
	}
}

void AGameHUD::DrawCrosshair(UTexture2D* TextureToDraw, FVector2D& ViewPortSize) {
	const FVector2D ViewportCenter(ViewPortSize.X / 2, ViewPortSize.Y / 2);
	const float TextureWidth = TextureToDraw->GetSizeX();
	const float TextureHeight = TextureToDraw->GetSizeY();
	const FVector2D TextureDrawPosition = FVector2D(ViewportCenter.X - (TextureWidth / 2), ViewportCenter.Y - (TextureHeight / 2));

	DrawTexture(TextureToDraw,
				TextureDrawPosition.X,
				TextureDrawPosition.Y,
				TextureWidth,
				TextureHeight,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				FColor::White
	);
}
