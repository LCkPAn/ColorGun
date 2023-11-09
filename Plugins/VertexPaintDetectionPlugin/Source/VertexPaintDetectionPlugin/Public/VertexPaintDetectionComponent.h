// Copyright 2022 Alexander Floden, Alias Alex River. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VertexPaintDetectionStructs.h"
#include "Engine/StreamableManager.h"
#include "VertexPaintDetectionComponent.generated.h"


class UVertexPaintDetectionGISubSystem;


//-------------------------------------------------------


DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineParams(FVertexColorGetClosestVertexData, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexDetectInfoStruct, detectedMeshWithSettings, FVertexDetectClosestVertexDataResultStruct, closestVertexInfo, FVertexDetectEstimatedColorAtHitLocationResultStruct, estimatedColorAtHitLocationInfo, FVertexDetectAvarageColorInAreaInfo, avarageColorInAreaInfo, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FVertexColorGetAllVertexColorsOnly, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexDetectGetColorsOnlyStruct, gotAllVertexColorsWithSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineParams(FVertexColorPaintedAtLocation, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPaintAtLocationStruct, meshPaintedWithSettings, FVertexDetectClosestVertexDataResultStruct, closestVertexInfoAfterApplyingColor, FVertexDetectEstimatedColorAtHitLocationResultStruct, estimatedColorAtHitLocationInfo, FVertexDetectAvarageColorInAreaInfo, avarageColorInAreaInfo, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FVertexColorPaintedWithinArea, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPainthWithinAreaStruct, areaWithinMeshPaintedWithSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FVertexColorPaintedEntireMesh, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPaintOnEntireMeshStruct, entireMeshPaintedWithSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FVertexColorPaintColorSnippet, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPaintColorSnippetStruct, paintColorSnippetWithSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FSetMeshComponentVertexColors, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPaintStruct, setMeshComponentVertexColorSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FSetMeshComponentVertexColorsUsingSerializedString, FVertexDetectTaskResultInfo, taskResultInfo, FVertexDetectMeshDataStruct, meshVertexData, FVertexPaintSetMeshComponentVertexColorsUsingSerializedString, setMeshComponentVertexColorUsingSerializedStringSettings, FVertexDetectAmountOfPaintedColorsOfEachChannel, amountOfPaintedColorsOfEachChannel, FVertexDetectVertexColorsOnEachBone, vertexColorsOnEachBone, FVertexDetectAdditionalDataToPassThrough, additionalData);


//-------------------------------------------------------

// NOTE Not blueprint spawnable so only the Blueprint Component that inherits from this can be added to BPs in case we add something important on that layer
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom))
class VERTEXPAINTDETECTIONPLUGIN_API UVertexPaintDetectionComponent : public UActorComponent {

	GENERATED_BODY()

public:


	//---------- PAINT & DETECT FUNCTIONS ----------//

	UVertexPaintDetectionComponent();

	void GetClosestVertexDataOnMesh(FVertexDetectInfoStruct getClosestVertexDataStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void GetClosestVertexDataOnMeshTaskFinished();

	void GetAllVertexColorsOnly(FVertexDetectGetColorsOnlyStruct getAllVertexColorsStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void GetAllVertexColorsOnlyTaskFinished();

	void PaintOnMeshAtLocation(FVertexPaintAtLocationStruct paintAtLocationStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void PaintOnMeshAtLocationTaskFinished();

	void PaintOnMeshWithinArea(FVertexPainthWithinAreaStruct paintWithinAreaStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void PaintOnMeshWithinAreaTaskFinished();

	void PaintOnEntireMesh(FVertexPaintOnEntireMeshStruct paintOnEntireMeshStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void PaintOnEntireMeshTaskFinished();

	void PaintColorSnippetOnMesh(FVertexPaintColorSnippetStruct paintColorSnippetStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);
	void PaintColorSnippetOnMeshTaskFinished();

	UFUNCTION(BlueprintCallable, Category = "Runtime Vertex Color Paint and Detection Plugin", meta = (ToolTip = "This returns the amount of Tasks that this component has queued up but have not finished yet. Can be useful if you for instance want to make sure another task of a certain type doesn't start if there's already one going. "))
		void GetCurrentTasksInitiatedByComponent(int& totalAmountOfTasks, int& amountOfGetClosestVertexDataTasks, int& amountOfGetAllVertexColorsOnlyTasks, int& amountOfPaintAtLocationTasks, int& amountOfPaintWithinAreaTasks, int& amountOfPaintEntireMeshTasks, int& amountOfPaintColorSnippetTasks);


	//---------- VERTEX PAINT / DETECTION SETTINGS ----------//

	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Detection")
		FVertexColorGetClosestVertexData getClosestVertexDataDelegate; // Broadcasts when Finished Getting Vertex Data, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show


	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Detection", meta = (ToolTip = "Broadcasts when Finished Getting All Vertex Colors Only, either successfully or unsuccessfully."))
		FVertexColorGetAllVertexColorsOnly getAllVertexColorsOnlyDelegate; // Broadcasts when Finished Getting Vertex Data, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show


	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when Finished Painting Vertex Colors, either successfully or unsuccessfully."))
		FVertexColorPaintedAtLocation vertexColorsPaintedAtLocationDelegate; // Broadcasts when Finished Painting Vertex Colors, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show

	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when Finished Painting Vertex Colors on Mesh within Area, either successfully or unsuccessfully."))
		FVertexColorPaintedWithinArea vertexColorsPaintedMeshWithinAreaDelegate; // Broadcasts when Finished Painting Vertex Colors on Mesh within Area, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show

	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when Finished Painting Vertex Colors on Entire Mesh, either successfully or unsuccessfully."))
		FVertexColorPaintedEntireMesh vertexColorsPaintedEntireMeshDelegate; // Broadcasts when Finished Painting Vertex Colors on Entire Mesh, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show

	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when Finished Paint Color Snippet, either successfully or unsuccessfully. "))
		FVertexColorPaintColorSnippet vertexColorsPaintColorSnippetDelegate; // Broadcasts when Finished Paint Color Snippet, either successfully or unsuccessfully. NOTE you may have to type in .AddDynamic() manually if it doesn't show

	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when VertexPaintDetectionGISubSystem has run it's SetMeshComponentVertexColors IF you provided a component. Useful if you're loading vertex data and want to start each task when the previous is finished. "))
		FSetMeshComponentVertexColors vertexColorsSetMeshColorsDelegate; // Broadcasts when VertexPaintDetectionGISubSystem has run it's SetMeshComponentVertexColors IF you provided a component. Useful if you're loading vertex data and want to start each task when the previous is finished. NOTE you may have to type in .AddDynamic() manually if it doesn't show


	UPROPERTY(BlueprintAssignable, Category = "Runtime Vertex Color Paint and Detection Plugin|Painting", meta = (ToolTip = "Broadcasts when VertexPaintDetectionGISubSystem has run it's SetMeshComponentVertexColorsUsingSerializedString IF you provided a component. Useful if you're loading vertex data and want to start each task when the previous is finished. "))
		FSetMeshComponentVertexColorsUsingSerializedString vertexColorsSetMeshColorsUsingSerializedStringDelegate; // Broadcasts when VertexPaintDetectionGISubSystem has run it's SetMeshComponentVertexColorsUsingSerializedString IF you provided a component. Useful if you're loading vertex data and want to start each task when the previous is finished. NOTE you may have to type in .AddDynamic() manually if it doesn't show

private:

	void PaintColorSnippetOnMesh_FinishedLoadingColorSnippetDataAsset(int finishedID, FVertexPaintColorSnippetStruct paintColorSnippetStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough);

	void CheckIfRegisteredAndInitialized();


	//---------- PROPERTIES ----------//

	TMap<int, TSharedPtr<FStreamableHandle>> colorSnippetAsyncLoadHandleMap;

	UPROPERTY()
		UVertexPaintDetectionGISubSystem* vertexPaintGameInstanceSubsystem_Global = nullptr;

	int amountOfGetClosestVertexDataTasksCache = 0;
	int amountOfGetAllVertexColorsOnlyTasksCache = 0;
	int amountOfPaintAtLocationTasksCache = 0;
	int amountOfPaintWithinAreaTasksCache = 0;
	int amountOfPaintEntireMeshTasksCache = 0;
	int amountOfPaintColorSnippetTasksCache = 0;
};
