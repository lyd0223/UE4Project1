// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomMainWidget.h"
#include "Store/StoreMainWidget.h"


void UWaitingRoomMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	m_StoreMainWidget = Cast<UStoreMainWidget>(GetWidgetFromName(TEXT("UI_StoreMain")));
	m_RelicMainWidget = nullptr;
	m_CategoryText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CategoryText")));
	m_CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));
	
}

void UWaitingRoomMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}
