#include "InteractableComponent.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/GameplayStatics.h"
#include "mega/Character/MegaCharacter.h"
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

void UInteractableComponent::TraceUnderCursor() {
	FVector2D viewport;
	if(GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(viewport);
	}

	FVector2D CrosshairLocation(viewport.X / 2, viewport.Y / 2);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	);

	if(bScreenToWorld) {
		FVector Start = CrosshairWorldPosition;

		FVector End = Start + (CrosshairWorldDirection * InteractDistance);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

		FCollisionShape Shape;
		Shape.SetSphere(InteractRadius);

		TArray<FHitResult> Hits;

		bool bHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);

		FocusedActor = nullptr;

		for(FHitResult Hit: Hits) {
			AActor* HitActor = Hit.GetActor();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, HitActor->GetName());
			if(HitActor) {
				if(HitActor->Implements<UIInteractable>()) {
					FocusedActor = HitActor;
					break;
				}
			}
		}

		// if focused show default ui 
	}
}
