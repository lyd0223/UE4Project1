// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletWidget.h"


void UBulletWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	m_BulletListView = Cast<UListView>(GetWidgetFromName(TEXT("BulletListView")));
}

void UBulletWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}