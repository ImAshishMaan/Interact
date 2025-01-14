#include "InteractableComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/GameplayStatics.h"
#include "mega/Character/MegaCharacter.h"
#include "mega/HUD/GameHUD.h"
#include "mega/Interfaces/IInteractable.h"

UInteractableComponent::UInteractableComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay() {
	Super::BeginPlay();
}

void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceUnderCursor();
}

void UInteractableComponent::PrimaryInteract(ACharacter* Character) {
	Interact(FocusedActor, Character);
}

void UInteractableComponent::Interact(AActor* InFocus, ACharacter* Character) {
	if(InFocus == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "No Focus Actor to Interact");
		return;
	}
	if(LastFocusActor == InFocus) {
		LastFocusActor = nullptr;
		return;
	}

	LastFocusActor = InFocus;
	AMegaCharacter* OwnerCharacter = Cast<AMegaCharacter>(Character);
	IIInteractable::Execute_Interact(InFocus, OwnerCharacter);
}

void UInteractableComponent::ShowCrosshairUI(AActor* InFocus) {
	if(InFocus == nullptr) return;

	if(IIInteractable::Execute_GetInteractionType(InFocus) == EInteractionType::CrosshairUI) {
		AGameHUD* GameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
		if(GameHUD) {
			// Replace with actual functionality for showing the crosshair UI
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Interact UI");
		}
	}
}

void UInteractableComponent::TraceUnderCursor() {
	FVector2D ViewportSize;
	if(GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	} else {
		return; // Exit early if we can't get the viewport size
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2, ViewportSize.Y / 2);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	// Deproject the screen position to a world position and direction
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if(bScreenToWorld) {
		FVector Start = CrosshairWorldPosition;
		FVector End = Start + (CrosshairWorldDirection * InteractDistance);

		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_Visibility
		);

		FocusedActor = nullptr;

		if(bHit) {
			AActor* HitActor = HitResult.GetActor();
			if(HitActor && HitActor->Implements<UIInteractable>()) {
				FocusedActor = HitActor;
				// Show default UI or interact prompt if needed
				ShowCrosshairUI(FocusedActor);
			}
		}

		// Debug: Visualize the trace
		if(false) {
			DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);
		}
	}
}
