// Copyright 2017-2018 Csaba Molnar, Daniel Butum
#pragma once

#include "DlgNode.h"
#include "DlgTextArgument.h"
#include "DlgNode_Speech.generated.h"

class USoundWave;
class UDialogueWave;
class UTexture2D;
struct FDlgTextArgument;

/**
 * Normal dialogue node - someone says something.
 */
UCLASS(BlueprintType)
class DLGSYSTEM_API UDlgNode_Speech : public UDlgNode
{
	GENERATED_BODY()

public:
	// Begin UObject Interface.
	FString GetDesc() override
	{
		if (bIsVirtualParent)
		{
			return TEXT("Virtual Parent Node. Acts like a fake parent (proxy) to other child nodes. (aka makes it get the grandchildren)\nOn revaluate children, it does not get the direct children but the children of the first satisfied direct child node (grandchildren).\nIt should have at least one satisified child otherwise the Dialogue is terminated.");
		}

		return TEXT("Normal dialogue node - someone says something.");
	}

#if WITH_EDITOR
	/**
	 * Called when a property on this object has been modified externally
	 *
	 * @param PropertyChangedEvent the property that was modified
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	// Begin UDlgNode Interface.
	bool HandleNodeEnter(UDlgContextInternal* DlgContext, TSet<const UDlgNode*> NodesEnteredWithThisStep) override;
	bool ReevaluateChildren(UDlgContextInternal* DlgContext, TSet<const UDlgNode*> AlreadyEvaluated) override;
	void GetAssociatedParticipants(TArray<FName>& OutArray) const override;
	const TArray<FDlgTextArgument>& GetTextArguments() const { return TextArguments; };

	// Getters:
	const FText& GetNodeText() const override { return (TextArguments.Num() > 0 && !ConstructedText.IsEmpty()) ? ConstructedText : Text; }
	const FText& GetRawNodeText() const override { return Text; }
	USoundWave* GetNodeVoiceSoundWave() const override { return VoiceSoundWave; }
	UTexture2D* GetNodeImage() const override { return ImageDialogue; }
	UDialogueWave* GetNodeVoiceDialogueWave() const override { return VoiceDialogueWave; }
	FName GetSpeakerState() const override { return SpeakerState; }
	void AddSpeakerStates(TSet<FName>& States) const { States.Add(SpeakerState); }

#if WITH_EDITOR
	FString GetNodeTypeString() const override { return bIsVirtualParent ? TEXT("Virtual Parent") : TEXT("Speech"); }
#endif

	// Begin own functions.
	/** Is this node a virtual parent? */
	virtual bool IsVirtualParent() const { return bIsVirtualParent; }

	/** Sets the virtual parent status */
	virtual void SetIsVirtualParent(bool bValue) { bIsVirtualParent = bValue; }

	/** Sets the Text of the Node. */
	virtual void SetNodeText(const FText& InText) { Text = InText; }

	/** Helper functions to get the names of some properties. Used by the DlgSystemEditor module. */
	static FName GetMemberNameText() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, Text); }
	static FName GetMemberNameTextArguments() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, TextArguments); }
	static FName GetMemberNameVoiceSoundWave() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, VoiceSoundWave); }
	//+ИТ
	static FName GetMemberNameImage() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, ImageDialogue); }
	//-ИТ
	static FName GetMemberNameVoiceDialogueWave() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, VoiceDialogueWave); }
	static FName GetMemberNameSpeakerState() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, SpeakerState); }
	static FName GetMemberNameIsVirtualParent() { return GET_MEMBER_NAME_CHECKED(UDlgNode_Speech, bIsVirtualParent); }

protected:

	/** Text that will appear when this node participant name speaks to someone else. */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData, Meta = (MultiLine = true))
	FText Text;

	UPROPERTY(EditAnywhere, EditFixedSize, Category = DialogueNodeData)
	TArray<FDlgTextArgument> TextArguments;

	/** Voice attached to this node. The Sound Wave variant. */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData, Meta = (DlgSaveOnlyReference))
	USoundWave* VoiceSoundWave;

	//+ИТ
	/** Voice attached to this node. The Sound Wave variant. */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData, Meta = (DlgSaveOnlyReference))
	UTexture2D* ImageDialogue;
	//-ИТ

	/** Voice attached to this node. The Dialogue Wave variant. Only the first wave from the dialogue context array should be used. */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData, Meta = (DlgSaveOnlyReference))
	UDialogueWave* VoiceDialogueWave;

	/** State of the speaker attached to this node. Passed to the GetParticipantIcon function. */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	FName SpeakerState;

	/**
	 * Make this Node act like a fake parent (proxy) to other child nodes. (aka makes it get the grandchildren)
	 * On revaluate children, it does not get the direct children but the children of the first satisfied direct child node (grandchildren).
	 * It should have at least one satisfied child otherwise the Dialogue is terminated.
	 */
	UPROPERTY(EditAnywhere, Category = DialogueNodeData)
	bool bIsVirtualParent = false;

	/** Constructed at runtime from the original text and the arguments if there is any. */
	FText ConstructedText;
};
