#include "DlgUAnimatedImage.h"

void DlgUAnimatedImage::SetCurrentFrame(int32 Frame)
{
	CurrentFrame = Frame;
	if (CurrentFrame < 0) CurrentFrame = 0;
	if (CurrentFrame > TotalFrames - 1) CurrentFrame = TotalFrames - 1;
	SynchronizeProperties();
}

void DlgUAnimatedImage::Play()
{
	if (!TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&DlgUAnimatedImage::TimerTick,
			1.0f / FramesPerSecond,
			true
		);
	}
}

void DlgUAnimatedImage::Stop()
{
	if (TimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		TimerHandle.Invalidate();
	}
}

void DlgUAnimatedImage::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	UTexture2D* Texture = Cast<UTexture2D>(Brush.GetResourceObject());
	if (Texture == nullptr) return;
	FVector2D TextureSize(Texture->GetSizeX(), Texture->GetSizeY());

	int32 MaxColumns = FMath::FloorToInt(TextureSize.X / Brush.ImageSize.X);
	int32 Row = FMath::FloorToInt(CurrentFrame / MaxColumns);
	int32 Column = CurrentFrame % MaxColumns;

	FVector2D Min(Brush.ImageSize.X * Column, Brush.ImageSize.Y * Row);
	FVector2D Max = Min + Brush.ImageSize;
	FBox2D UVCoordinates(Min / TextureSize, Max / TextureSize);
	UVCoordinates.bIsValid = true;

	Brush.SetUVRegion(MoveTemp(UVCoordinates));
}

void DlgUAnimatedImage::TimerTick()
{
	CurrentFrame++;
	if (CurrentFrame > TotalFrames - 1) CurrentFrame = 0;
	SynchronizeProperties();
}