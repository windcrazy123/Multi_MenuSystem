// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup();

protected:

	virtual bool Initialize() override;
private:
	//BindWidget: the button widget on BP will be linked to these button variable in C++
	//and the C++ variable has to have the exact same name as the button on BP
	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	//bind this function to an on click event or delegate that exists in the UButton class
	//these have to be UFUNCTION
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtionClicked();

};
