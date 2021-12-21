// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BulletListItemWidget.generated.h"

UCLASS()
class PROJECT1_API UBulletListItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_NameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_DescText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* m_SPCostText;

	int32		m_Index;

	public:
	int32 GetIndex()	const
	{
		return m_Index;
	}

	void SetIndex(int32 Index)
	{
		m_Index = Index;
	}


	protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
	public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
	virtual void NativeOnItemSelectionChanged(bool bIsSelected);
};
