// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"

#include "InventoryManager.generated.h"

DECLARE_DELEGATE_OneParam(FUIDelegate, const FItemTableInfo*);

UCLASS()
class PROJECT1_API UInventoryManager : public UObject , public FTickableGameObject
{
	GENERATED_BODY()

	friend class UProject1GameInstance;

private:
	UInventoryManager();

private:
	TArray<FItem*> m_ItemArray;
	uint8 m_MaxWeight;

	FUIDelegate m_UIDelegate;
	
	ACharacter* m_OwnerCharacter;
public:
	TArray<FItem*>& GetItemArray()
	{
		return m_ItemArray;
	}
	void SetOwnerCharacter(ACharacter* Character)
	{
		m_OwnerCharacter = Character;
	}
private:
	void Init();

public:
	void AddItem(FItem* Item);
	void DeductItem(FItem* Item);

	template <typename T>
	void SetUIDelegate(T* Obj, void (T::* Func)())
	{
		m_UIDelegate.BindUObject(Obj, Func);
	}


	public:
	//tick을위한 함수
	UFUNCTION(BlueprintCallable, Category = Test)
	void CallTimer();

	void TestTimer();

	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	UWorld* GetWorld() const override;

	float TestCounter;
};
