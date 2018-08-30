// Copyright 2017-2018 Csaba Molnar, Daniel Butum, Kanev Sergey
#include "DlgContext.h"
#include "DlgSystemPrivatePCH.h"
#include "DlgNode.h"
#include "DlgDialogueParticipant.h"
#include "DlgMemory.h"

//+ИТ
 
//
//void UDlgContext::SynchronizePropertiesAnimation()
//{
// 
//	/*UTexture2D* Texture = Cast<UTexture2D>(GetImageBrush().GetResourceObject());
//	if (Texture == nullptr) return;
//	FVector2D TextureSize(Texture.GetSizeX(), Texture.GetSizeY());
//
//	int32 MaxColumns = FMath::FloorToInt(TextureSize.X / imageBrush->ImageSize.X);
//	int32 Row = FMath::FloorToInt(CurrentFrame / MaxColumns);
//	int32 Column = CurrentFrame % MaxColumns;
//
//	FVector2D Min(imageBrush.ImageSize.X * Column, imageBrush.ImageSize.Y * Row);
//	FVector2D Max = Min + imageBrush.ImageSize;
//	FBox2D UVCoordinates(Min / TextureSize, Max / TextureSize);
//	UVCoordinates.bIsValid = true;
//
//	imageBrush->SetUVRegion(MoveTemp(UVCoordinates));*/
//}
////-ИТ

bool UDlgContext::ChooseChildBasedOnAllOptionIndex(int32 Index)
{
	if (!AllChildren.IsValidIndex(Index))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid index %d in UDlgContext::ChooseChildBasedOnAllOptionIndex!"), Index);
		return false;
	}

	if (!AllChildren[Index].bSatisfied)
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Index %d is an unsatisfied edge! (UDlgContext::ChooseChildBasedOnAllOptionIndex!) Call failed!"), Index);
		return false;
	}

	for (int32 i = 0; i < AvailableChildren.Num(); ++i)
	{
		if (AvailableChildren[i] == AllChildren[Index].EdgePtr)
		{
			return ChooseChild(i);
		}
	}

	ensure(false);
	return false;
}

const FText& UDlgContext::GetOptionText(int32 OptionIndex) const
{
	check(Dialogue);

	if (!AvailableChildren.IsValidIndex(OptionIndex))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option = %d in GetOptionText!"), OptionIndex);
		return FText::GetEmpty();
	}

	return AvailableChildren[OptionIndex]->GetEdgeText();
}

FName UDlgContext::GetOptionSpeakerState(int32 OptionIndex) const
{
	check(Dialogue);

	if (!AvailableChildren.IsValidIndex(OptionIndex))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option = %d in GetOptionSpeakerState!"), OptionIndex);
		return NAME_None;
	}

	return AvailableChildren[OptionIndex]->SpeakerState;
}

const FDlgEdge& UDlgContext::GetOption(int32 OptionIndex) const
{
	check(Dialogue);

	if (!AvailableChildren.IsValidIndex(OptionIndex))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option index %d in GetOption!"), OptionIndex);
		return FDlgEdge::GetInvalidEdge();
	}

	return *AvailableChildren[OptionIndex];
}

const FText& UDlgContext::GetOptionTextFromAll(int32 Index) const
{
	check(Dialogue);

	if (!AllChildren.IsValidIndex(Index))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option = %d in GetOptionTextFromAll!"), Index);
		return FText::GetEmpty();
	}

	return AllChildren[Index].EdgePtr->GetEdgeText();
}

bool UDlgContext::IsOptionSatisfied(int32 Index) const
{
	check(Dialogue);

	if (!AllChildren.IsValidIndex(Index))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option index %d in IsOptionSatisfied!"), Index);
		return false;
	}

	return AllChildren[Index].bSatisfied;
}

FName UDlgContext::GetOptionSpeakerStateFromAll(int32 Index) const
{
	check(Dialogue);

	if (!AllChildren.IsValidIndex(Index))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option = %d in GetOptionSpeakerStateFromAll!"), Index);
		return NAME_None;
	}

	return AllChildren[Index].EdgePtr->SpeakerState;
}

const FDlgEdge& UDlgContext::GetOptionFromAll(int32 Index) const
{
	check(Dialogue);

	if (!AvailableChildren.IsValidIndex(Index))
	{
		UE_LOG(LogDlgSystem, Error, TEXT("Invalid option index %d in GetOptionFromAll!"), Index);
		return FDlgEdge::GetInvalidEdge();
	}

	return *AllChildren[Index].EdgePtr;
}


const FText& UDlgContext::GetActiveNodeText() const
{
	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return FText::GetEmpty();
	}

	return Node->GetNodeText();
}

FName UDlgContext::GetActiveSpeakerState() const
{
	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return NAME_None;
	}

	return Node->GetSpeakerState();
}

USoundWave* UDlgContext::GetActiveNodeVoiceSoundWave() const
{
	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}

	return Node->GetNodeVoiceSoundWave();
}

UDialogueWave* UDlgContext::GetActiveNodeVoiceDialogueWave() const
{
	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}

	return Node->GetNodeVoiceDialogueWave();
}

//+ИТ
//вызов метода получить изображение в контексте нода
UImage* UDlgContext::GetActiveNodeImage() const
{
	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}
	//получаем изображение
	UTexture2D* Texture = Node->GetNodeImage();

	TAssetPtr<UTexture2D> icon;
	//FSlateBrush imageBrusher{};
	//imageBrusher.ImageSize = FVector2D(Texture->GetSizeX, Texture->GetSizeY);
	//imageBrusher.SetResourceObject(Texture);

	//UImage *image = NewObject<UImage>(); // im creating the image widget in code as well
	//image->SetBrush(imageBrusher);

	/*imageBrush.ImageSize = FVector2D(Texture.GetSizeX, Texture.GetSizeY);
	 
	imageBrush.SetResourceObject(Texture);

	CurrentAnimationImage = new NewObject(UImage);
	CurrentAnimationImage->SetBrush(imageBrush);

	CurrentFrame++;
	if (CurrentFrame > TotalFrames - 1) CurrentFrame = 0;
	SynchronizePropertiesAnimation();*/

	return CurrentAnimationImage;
}
 
//вызов метода класса для предоставление диалога выбора класса UTexture 
UTexture2D* UDlgContext::GetActiveParticipantImage() const
{
	if (!IsValid(Dialogue))
	{
		return nullptr;
	}

	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}

	FName SpeakerName = Node->GetNodeParticipantName();
	UObject* const* Item = Participants.Find(SpeakerName);
	if (Item == nullptr || !IsValid(*Item))
	{
		return nullptr;
	}

	//return IDlgDialogueParticipant::Execute_GetParticipantIcon(*Item, SpeakerName, Node->GetSpeakerState());

	return Node->GetNodeImage();
}
//-ИТ

UTexture2D* UDlgContext::GetActiveParticipantIcon() const
{
	if (!IsValid(Dialogue))
	{
		return nullptr;
	}

	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}

	FName SpeakerName = Node->GetNodeParticipantName();
	UObject* const* Item = Participants.Find(SpeakerName);
	if (Item == nullptr || !IsValid(*Item))
	{
		return nullptr;
	}

	return IDlgDialogueParticipant::Execute_GetParticipantIcon(*Item, SpeakerName, Node->GetSpeakerState());
}

UObject* UDlgContext::GetActiveParticipant() const
{
	if (!IsValid(Dialogue))
	{
		return nullptr;
	}

	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return nullptr;
	}

	UObject* const* Item = Participants.Find(Node->GetNodeParticipantName());
	return Item == nullptr ? nullptr : *Item;
}

FName UDlgContext::GetActiveParticipantName() const
{
	if (!IsValid(Dialogue))
	{
		return NAME_None;
	}

	const UDlgNode* Node = GetActiveNode();
	if (!IsValid(Node))
	{
		return NAME_None;
	}

	return Node->GetNodeParticipantName();
}


const UObject* UDlgContext::GetConstParticipant(FName DlgParticipantName) const
{
	const UObject* const* ParticipantPtr = Participants.Find(DlgParticipantName);
	if (ParticipantPtr != nullptr)
	{
		return *ParticipantPtr;
	}

	return nullptr;
}


bool UDlgContext::IsEdgeConnectedToVisitedNode(int32 Index, bool bLocalHistory, bool bIndexSkipsUnsatisfiedEdges) const
{
	int32 TargetIndex = INDEX_NONE;

	if (bIndexSkipsUnsatisfiedEdges)
	{
		if (!AvailableChildren.IsValidIndex(Index))
		{
			UE_LOG(LogDlgSystem, Error, TEXT("UDlgContext::IsEdgeConnectedToVisitedNode failed - invalid index %d"), Index);
			return false;
		}
		TargetIndex = AvailableChildren[Index]->TargetIndex;
	}
	else
	{
		if (!AllChildren.IsValidIndex(Index))
		{
			UE_LOG(LogDlgSystem, Error, TEXT("UDlgContext::IsEdgeConnectedToVisitedNode failed - invalid index %d"), Index);
			return false;
		}
		TargetIndex = AllChildren[Index].EdgePtr->TargetIndex;
	}

	if (bLocalHistory)
	{
		return VisitedNodeIndices.Contains(TargetIndex);
	}
	else
	{
		if (Dialogue == nullptr)
		{
			UE_LOG(LogDlgSystem, Error, TEXT("UDlgContext::IsEdgeConnectedToVisitedNode called, but the context does not have a valid dialogue!"));
			return false;
		}

		return FDlgMemory::GetInstance()->IsNodeVisited(Dialogue->GetDlgGuid(), TargetIndex);
	}
}

//+ИТ
void UAnimationImage::SetCurrentFrame(int32 Frame)
{
	CurrentFrame = Frame;
	if (CurrentFrame < 0) CurrentFrame = 0;
//	if (CurrentFrame > TotalFrames - 1) CurrentFrame = TotalFrames - 1;
	SynchronizeProperties();
}

void UAnimationImage::SetFillFromFolder(bool FillArray)
{
	FillFromFolder = FillArray;

	if (FillFromFolder == true)
	{
		//if (AnimationImages.Num() > 0) {
		 		 
		UTexture2D* Texture = Cast<UTexture2D>(Brush.GetResourceObject());
		FString FolderName = Texture->GetFullGroupName(true);
		AnimationImages.Empty();
		getFilesInFolder(FolderName);
		 
	}
}



void UAnimationImage::SynchronizeProperties()
{
	//Super::SynchronizeProperties();

	//UTexture2D* Texture = Cast<UTexture2D>(Brush.GetResourceObject());
	//if (Texture == nullptr) return;
	//FVector2D TextureSize(Texture->GetSizeX(), Texture->GetSizeY());

	////int32 MaxColumns = FMath::FloorToInt(TextureSize.X / Brush.ImageSize.X);
	//
	//int32 Row = FMath::FloorToInt(CurrentFrame / RowsCount);
	////int32 Column = CurrentFrame % CountColumns;
	//int32 Column = CurrentFrame % ColumnsCount;

	////FVector2D Min(Brush.ImageSize.X * Column, Brush.ImageSize.Y * Row);
	//FVector2D Min(Brush.ImageSize.X * Column, Brush.ImageSize.Y * Row);
	//FVector2D Max = Min + Brush.ImageSize;
	//FBox2D UVCoordinates(Min / TextureSize, Max / TextureSize);
	//UVCoordinates.bIsValid = true;

	//Brush.SetUVRegion(MoveTemp(UVCoordinates));

	Super::SynchronizeProperties();

	if (AnimationImages.Num() > 0) {
		if (CurrentFrame < AnimationImages.Num()) {
			UTexture2D* Texture = Cast<UTexture2D>(AnimationImages[CurrentFrame]);

			if (Texture == nullptr) return;

			FVector2D TextureSize(Texture->GetSizeX(), Texture->GetSizeY());
		
			SetBrushFromTexture(Texture);
		}
	}
}
//-ИТ

void UAnimationImage::Play()
{
	if (!TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&UAnimationImage::TimerTick,
			1.0f / FramesPerSecond,
			true
		);
	}
}

void UAnimationImage::Stop()
{
	if (TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		TimerHandle.Invalidate();
	}

}

void UAnimationImage::TimerTick()
{
	CurrentFrame++;
	if (CurrentFrame > AnimationImages.Num() && Loop) CurrentFrame = 0;
	SynchronizeProperties();
}

void UAnimationImage::getFilesInFolder(FString Directory)
{
	Super::SynchronizeProperties();
	 
	TArray<FString> output; 
 

	if (FPaths::DirectoryExists(Directory))
	{
		FString path = Directory + "*.uasset";
		FFileManagerGeneric::Get().FindFiles(output, *path, true, false);
		for (int i = 0; i < output.Num(); i++)
		{
	
			output[i] = Directory + output[i];

			FStringAssetReference assetRef(output[i]);
			
			AnimationImages.Add(Cast<UTexture2D>(assetRef.TryLoad()));
		}
	}
}


UAnimationImage::UAnimationImage()
{
	TArray<FString> DefOptions;

	DefOptions.AddUnique("Flash");
	DefOptions.AddUnique("Flash2");
	DefOptions.AddUnique("Flash3");
	//-ИТ

	// Initialize the set of options from the default set only once.
	for (const FString& DefOption : DefOptions)
	{
		EffectsName->AddOption(DefOption);
	}
} 

//bool UEffectAnimationComboBox::Initialize()
//{
//	if (!Super::Initialize())
//	{
//		return false;
//	}
//	if (!effectSettings)
//	{
//		return false;
//	}
//
//	//Delete all the text
//	effectSettings->ClearOptions();
//
//	effectSettings->AddOption(TEXT("Low"));
//	effectSettings->AddOption(TEXT("Medium"));
//	effectSettings->AddOption(TEXT("High"));
//	effectSettings->AddOption(TEXT("Epic"));
//	effectSettings->AddOption(TEXT("Cinematic"));
//
//	return true;
//}

//-ИТ
