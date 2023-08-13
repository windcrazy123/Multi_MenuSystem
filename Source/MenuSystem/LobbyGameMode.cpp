// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// GameState in UE5 is TObjectPtr<AGameStateBase>, AGameStateBase* need GameState.Get() function
	if (GameState)
	{
		int32 NumberOfPlayers = GameState->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,// 1 means if there is a new message with the same key will replace the old one
				600.f, FColor::Yellow,
				FString::Printf(TEXT("Players in game: %d"),NumberOfPlayers)
			);

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					2,
					60.f, FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(
			1,
			600.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers - 1)// When calling the logout function the number haven't update
		);

		FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			2,
			60.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has exited the game!"), *PlayerName)
		);
	}
}
