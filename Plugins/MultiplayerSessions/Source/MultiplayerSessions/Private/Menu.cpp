// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"

#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UMenu::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this,&UMenu::JoinButtonClicked); 
	}
	return true;
}

void UMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	MenuTearDown();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UMenu::HostButtonClicked()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1, 15.f, FColor::Yellow,
			FString::Printf(TEXT("Host button clicked"))
		);
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections,MatchType);
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/Lobby?listen");
		}
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			-1, 15.f, FColor::Yellow,
			FString::Printf(TEXT("Join button clicked"))
		);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeGameOnly;
			PlayerController->SetInputMode(InputModeGameOnly);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
