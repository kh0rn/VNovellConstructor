// Copyright 2018 Kanev Sergey
#pragma once
#include "UMGStyle.h"
#include "SObjectWidget.h"
#include "IUMGModule.h"
#include "UserWidget.h"
#include "UMG.h"

//#include "DlgUAnimatedImage.generated.h"
/**
* UMG Animated Image.
* Make sure you add "UMG", "Slate" and "SlateCore" to your module's dependencies.
* It doesn't use flipbook data. All animation frames must be the same size and position in grid on the texture.
* Set frame size by setting "Image Size" and "Total Frames" http://i.imgur.com/5WuZmKA.png
*/

class DlgUAnimatedImage;

UCLASS()
class DlgUAnimatedImage : public UImage
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Animation)
		void SetCurrentFrame(int32 Frame);

	UFUNCTION(BlueprintCallable, Category = Animation)
		void Play();

	UFUNCTION(BlueprintCallable, Category = Animation)
		void Stop();

	virtual void SynchronizeProperties();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 FramesPerSecond = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 CurrentFrame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 TotalFrames = 1;

	void TimerTick();

	FTimerHandle TimerHandle;
};