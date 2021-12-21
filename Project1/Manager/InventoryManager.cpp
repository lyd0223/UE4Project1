// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"

#include "Project1/Project1GameModeBase.h"
#include "Project1/Effect/NormalEffect.h"
#include "Project1/Player/PlayerCharacter.h"
#include "Project1/UI/MainHUDWidget.h"
#include "Project1/UI/QuickItemSlotWidget.h"


UInventoryManager::UInventoryManager()
{
	m_MaxWeight = 36;
}

void UInventoryManager::Init()
{
	
}

void UInventoryManager::AddItem(FItem* Item)
{
	//아이템이 이미 인벤토리에 있는지 판단한다.
	bool IsAlreadyHave = false;
	for(auto MyItem : m_ItemArray)
	{
		//이미 있다면 카운트만 추가.
		if(MyItem->ItemTableInfo == Item->ItemTableInfo)
		{
			MyItem->Count += Item->Count;
			IsAlreadyHave = true;

			//delete Item;
			Item = MyItem;
			
			break;
		}
	}
	//인벤토리에 이미 잇지않다면 ItemArray에 추가.
	if(!IsAlreadyHave)
		m_ItemArray.Add(Item);

	if(m_OwnerCharacter)
	{
		UWorld* World = m_OwnerCharacter->GetWorld();
		if(World)
		{
			AProject1GameModeBase* GameModeBase = Cast<AProject1GameModeBase>(World->GetAuthGameMode());
			if(GameModeBase)
			{
				GameModeBase->GetMainHUDWidget()->GetMenuWidget()->GetInventoryWidget()->AddItem(Item);
				GameModeBase->GetMainHUDWidget()->GetQuickSlotWidget()->RefreshItems(Item);
			}
		}
	}
	//게임모드에맞는 UI 수정.
	/*
	 WaitingRoom	-> 
	 Main			->
	 */
	//m_UIDelegate.Execute(ItemTableInfo);
}

void UInventoryManager::DeductItem(FItem* Item)
{
	for(auto MyItem : m_ItemArray)
	{
		if(MyItem == Item)
		{
			Item->Count--;

			if(Item->Count == 0)
			{
				m_ItemArray.Remove(Item);

				//delete Item;
			}

			//사용 아이템일 시 처리
			if(Item->ItemTableInfo->ItemType == EItemType::Uses)
			{
				for(auto ItemOption : Item->ItemTableInfo->ItemOptionArray)
				{
					
					if(m_OwnerCharacter)
					{
						APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(m_OwnerCharacter);
						FPlayerInfo& PlayerInfo = PlayerCharacter->GetPlayerInfo();
						switch (ItemOption.OptionType)
						{
						case EItemOptionType::Attack : 
							PlayerInfo.ATK += ItemOption.OptionAmount;
							break;
						case EItemOptionType::HPRecovery : 
							PlayerInfo.HP += ItemOption.OptionAmount;
							if(PlayerInfo.HP > PlayerInfo.HPMax)
								PlayerInfo.HP = PlayerInfo.HPMax;
							break;
						case EItemOptionType::AttackSpeed : 
							PlayerInfo.AttackSpeed += ItemOption.OptionAmount;
							break;
							
						}
						PlayerCharacter->SetUI();
						
						FActorSpawnParameters param;
						param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						ANormalEffect* Effect = PlayerCharacter->GetWorld()->SpawnActor<ANormalEffect>(ANormalEffect::StaticClass(), PlayerCharacter->GetActorLocation(),
							FRotator::ZeroRotator, param);
						Effect->LoadSoundAsync(TEXT("PotionDrink"));
						Effect->SetSoundVolume(0.5f);
						Effect->SetLifeTime(1.f);
					}
				}
				
			}
		}
	}
}



void UInventoryManager::CallTimer()
{
	FTimerHandle tHandle;
	const float Delay = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(tHandle, this, &UInventoryManager::TestTimer, Delay, false);
}

void UInventoryManager::TestTimer()
{
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Red, "Hello World");
}

void UInventoryManager::Tick(float DeltaTime)
{
	TestCounter += DeltaTime;

	for(int i = 0 ; i<m_ItemArray.Num(); i++)
	{
		if(!m_ItemArray[i])
			PrintViewport(1.f, FColor::Red, "!!!!!error");
	}
	GEngine->AddOnScreenDebugMessage(0, 0, FColor::Green, FString::SanitizeFloat(TestCounter));

}

bool UInventoryManager::IsTickable() const
{
	return true;
}

bool UInventoryManager::IsTickableInEditor() const
{
	return false;
}

bool UInventoryManager::IsTickableWhenPaused() const
{
	return false;
}

TStatId UInventoryManager::GetStatId() const
{
	return TStatId();
}

UWorld* UInventoryManager::GetWorld() const
{
	return m_OwnerCharacter->GetWorld();
}