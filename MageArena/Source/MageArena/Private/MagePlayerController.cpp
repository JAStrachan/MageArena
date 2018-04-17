// Fill out your copyright notice in the Description page of Project Settings.

#include "MagePlayerController.h"

AMage * AMagePlayerController::GetControlledBody() const
{
	return Cast<AMage>(GetCharacter());
}
