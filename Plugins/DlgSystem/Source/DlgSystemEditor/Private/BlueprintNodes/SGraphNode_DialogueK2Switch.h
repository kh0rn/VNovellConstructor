// Copyright 2017-2018 Csaba Molnar, Daniel Butum, Kanev Sergey
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SGraphNodeK2Base.h"


class UDialogueK2Node_SwitchDialogueCallback;

class SGraphNode_DialogueK2Switch : public SGraphNodeK2Base
{
	typedef SGraphNodeK2Base Super;
	typedef SGraphNode_DialogueK2Switch Self;

public:
	SLATE_BEGIN_ARGS(Self) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueK2Node_SwitchDialogueCallback* InNode);

	// SGraphNode interface
	void CreatePinWidgets() override;

protected:
	void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;
	EVisibility IsAddPinButtonVisible() const override;
	FReply OnAddPin() override;
	// End of SGraphNode interface

private:
	// The blueprint dialogue switch this view represents
	UDialogueK2Node_SwitchDialogueCallback* DialogueK2Node_Switch = nullptr;
};

