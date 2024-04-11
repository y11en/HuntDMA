﻿#include "Pch.h"
#include "PlayerEsp.h"
#include "globals.h"
#include "CheatFunction.h"
#include "Drawing.h"
#include "ConfigInstance.h"
#include <WorldEntity.h>
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	
	EnvironmentInstance->UpdatePlayerList();
	

});
std::shared_ptr<CheatFunction> UpdateZombies = std::make_shared<CheatFunction>(20, [] {
	EnvironmentInstance->UpdateZombieList();


	});


void DrawPlayers()
{
	if (EnvironmentInstance == nullptr)
		return;
	if (EnvironmentInstance->GetObjectCount() == 0)
		return;
	
	for(std::shared_ptr<WorldEntity> ent : EnvironmentInstance->GetZombieList())
	{ 
	
		if(ent == nullptr)
			continue;
		if (Vector3::Distance(ent->GetPosition(), CameraInstance->GetPosition()) <= 1)
			continue; // local player, ignore
		if(!ent->GetValid())
			continue;
	
		Vector2 pos = CameraInstance->WorldToScreen(ent->GetPosition());
		if (pos.x == 0 || pos.y == 0)
			continue;
		std::wstring distance = L"[" +  std::to_wstring((int)Vector3::Distance(ent->GetPosition(), CameraInstance->GetPosition())) + L"m]";
		DrawText(pos.x, pos.y, ent->GetName() + distance, "Verdana", 12, Colour(255, 0, 0, 255), Centre);


	}
	for (std::shared_ptr<WorldEntity> ent : EnvironmentInstance->GetPlayerList())
	{
		if (ent == nullptr)
			continue;
		if (Vector3::Distance(ent->GetPosition(), CameraInstance->GetPosition()) <= 1)
			continue; // local player, ignore
		int distance = (int)Vector3::Distance(ent->GetPosition(), CameraInstance->GetPosition());
		if (distance <= 0)
			continue;
		if(distance > Configs.Player.MaxDistance)
			continue;
		if (!ent->GetValid())
			continue;
		Vector2 pos = CameraInstance->WorldToScreen(ent->GetPosition());
		if (pos.x == 0 || pos.y == 0)
			continue;
		std::wstring wname = Configs.Player.Name ? ent->GetName() : L"";
		std::wstring wdistance = Configs.Player.Distance ?  L"[" + std::to_wstring(distance) + L"m]" : L"";
		DrawText(pos.x, pos.y, wname + wdistance, "Verdana", Configs.Player.FontSize, ent->GetType() == EntityType::FriendlyPlayer ? Configs.Player.FriendColour :  Configs.Player.TextColour, Centre);


	}
}