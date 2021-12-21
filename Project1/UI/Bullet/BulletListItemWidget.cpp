// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletListItemWidget.h"


void UBulletListItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	m_DescText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescText")));
	m_SPCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SPCostText")));
}

void UBulletListItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBulletListItemWidget::NativeOnListItemObjectSet(
	UObject* ListItemObject)
{
	// UQuestDescCompleteListData* Item = 
	// 	Cast<UQuestDescCompleteListData>(ListItemObject);
	//
	// Item->SetOwnerWidget(this);
	// m_TypeText->SetText(FText::FromString(Item->GetTypeText()));
	// m_DestText->SetText(FText::FromString(Item->GetDestText()));
	// m_CountText->SetText(FText::FromString(Item->GetCountText()));
	// m_Index = Item->GetIndex();
}

void UBulletListItemWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
}
