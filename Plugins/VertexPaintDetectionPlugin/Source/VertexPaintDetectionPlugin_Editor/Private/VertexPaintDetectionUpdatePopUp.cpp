// Copyright 2022 Alexander Floden, Alias Alex River. All Rights Reserved. 

#include "VertexPaintDetectionUpdatePopUp.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "SWebBrowser.h"
#include "Interfaces/IPluginManager.h"
#include "EditorStyleSet.h"
#include "VertexPaintDetectionUpdatConfig.h"


//--------------------------------------------------------

// On Browser Link Clicked

void VertexPaintDetectionUpdatePopUp::OnBrowserLinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata) {

	const FString* URL = Metadata.Find(TEXT("href"));

	if (URL)
	{
		FPlatformProcess::LaunchURL(**URL, nullptr, nullptr);
	}
}


//--------------------------------------------------------

// Register

void VertexPaintDetectionUpdatePopUp::Register() {

	
	UVertexPaintDetectionUpdatConfig* updatePopupConfig = GetMutableDefault<UVertexPaintDetectionUpdatConfig>();

	if (updatePopupConfig) {


		IPluginManager& PluginManager = IPluginManager::Get();
		auto pluginTemp = PluginManager.FindPlugin(TEXT("VertexPaintDetectionPlugin"));


		if (pluginTemp.IsValid()) {

			const FString UpdatedConfigFile = pluginTemp.Get()->GetBaseDir() + "/Config/UpdateConfig.ini";

			if (FPaths::FileExists(UpdatedConfigFile)) {

				updatePopupConfig->LoadConfig(nullptr, *UpdatedConfigFile);
			}

			else {

				updatePopupConfig->SaveConfig(CPF_Config, *UpdatedConfigFile);
			}


			const FPluginDescriptor& Descriptor = pluginTemp.Get()->GetDescriptor();

			if (Descriptor.VersionName != updatePopupConfig->PluginVersionUpdate) {

				updatePopupConfig->PluginVersionUpdate = Descriptor.VersionName;
				updatePopupConfig->SaveConfig(CPF_Config, *UpdatedConfigFile);

				FCoreDelegates::OnPostEngineInit.AddLambda([]() {
					Open();
				});
			}
		}
	}
}


//--------------------------------------------------------

// Open

void VertexPaintDetectionUpdatePopUp::Open() {

	if (!FSlateApplication::Get().CanDisplayWindows())
	{
		return;
	}

	TSharedRef<SBorder> WindowContent = SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		.Padding(FMargin(8.0f, 8.0f));

	TSharedPtr<SWindow> Window = SNew(SWindow)
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		.SizingRule(ESizingRule::FixedSize)
		.ClientSize(FVector2D(700, 600))
		.Title(FText::FromString("Runtime Vertex Color Paint & Detection Plugin"))
		.IsTopmostWindow(true)
		[
			WindowContent
		];

	const FSlateFontInfo HeadingFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
	const FSlateFontInfo ContentFont = FCoreStyle::GetDefaultFontStyle("Regular", 12);

	TSharedRef<SVerticalBox> InnerContent = SNew(SVerticalBox)
		// Default settings example
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(STextBlock)
			.Font(HeadingFont)
		.Text(FText::FromString("Runtime Vertex Color Paint & Detection Plugin"))
		]
	+ SVerticalBox::Slot()
		.FillHeight(1.0)
		.Padding(10)
		[
			SNew(SBorder)
			.Padding(10)

#if ENGINE_MAJOR_VERSION == 4

		.BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))

#elif ENGINE_MAJOR_VERSION == 5

	#if ENGINE_MINOR_VERSION == 0

		.BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))

	#else

		.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))

	#endif
#endif

		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		[
			SNew(SRichTextBlock)
			.Text(FText::FromString(R"(
<LargeText>Thank you for using Runtime Vertex Color Paint & Detection Plugin!</>

If you are new to the Plugin then check out the <a id="browser" href="https://youtu.be/UHX0zzDwP9M">Video Tutorial</> which can help you get started more quickly! The <a id="browser" href="https://docs.google.com/document/d/1bIarYezV921XkSbbZ8Pknla_4qEqKlY_NHvVwIYHGks/edit?usp=sharing">Documentation </> can also give you a better understanding of the plugin works. You can also join the <a id="browser" href="https://discord.gg/YkxMsxb4eP">Discord </> if you need any help or just want to share your work!

If you enjoy the plugin then please consider leaving a <a id="browser" href="https://www.unrealengine.com/marketplace/en-US/product/runtime-vertex-color-paint-detection-plugin">Review on the Marketplace Page</>, as it really helps the plugin alot! <3 



<RichTextBlock.Bold>UNREAL ENGINE 4 SUPPORT IS DISCONTINUED!</>

Unfortunately Epic has made it so you can't Update the UE4 plugin anymore. 
Because of this I have made the decision to move up to UE5, so the plugin will continue to be developed in the UE5.0 version of the Example Project, so there will be no more new Example Projects for UE4. However, with some simple modifications to the source code of the plugin (so we can manually register physics surfaces etc. in the data assets, since we can't use the editor widget) you will be able to use the latest version of the plugin in UE4! This <a id="browser" href="https://youtu.be/X3D0Ax_Fel8">Tutorial</> will go through how to Enable this. 

If you want to use the latest Example Project that showcases the latest features and have the most optimimized solutions for those simple examples, then you will have to move up to UE5!


<LargeText>Version 1.17</>


<RichTextBlock.Bold>Example Project</>

* Added example with puddle so you can paint expanding circles and set the falloff type etc. to can showcase the new paint at location with min and max AoE etc.

* Added a component that can paint water ripples when taking footsteps, that paints at location and increases the area min and max so it goes from the center outwards, as well as paint entire mesh that removes on it so the Ripple goes down. Ofc. not the optimal way to do ripples but fun way to test out the new min and max area of effect, as well as playing around with normals with the material. 


<RichTextBlock.Bold>New Features</>

* Added so you can paint at location with a Minimum and Maximum Area of Effect, and with 3 different falloff types, Outward (same as before), inward (opposite of outward), and spherical. You can now set the Distance to base the falloff from (which has replaced the old Area of Effect with Full strength since it can do the same). So you can for instance paint circles now, and have the falloff go from centre outward, or from the max distance inward, or you can set the distance to base falloff from to be in between them, and use the spherical falloff type if you want it to get stronger in the centre of the circle. 

* Added so Paint Within Area also has distanceToBaseFalloffFrom, where depeending on the falloff type, we start the falloff either farther from the center, from the bottom, or from the top. It has also replaced the old AreaOfEffectWithFullStrength, as it can do the same but even more. 


<RichTextBlock.Bold>Misc</>

* Added so paint strengths gets Clamped if not 0, so even if you set to paint with 0.000001, you will paint with 0.005 which is the smallest amount to paint to make any difference since it is 1 when converted to FColor (which range from 0-255)

* Split up and moved Paint Color Limit so we have a seperate one in Apply Colors Using Physics Surface where we only set the limit to whatever channel the physics surface is on, and another for the RGBA values which limits them. 
  This fixes an issue when painting using physics surface, where we may not know which vertex channel the physics surface is registered to. Before we had to know that, and limit that specific channel, but now it will just automatically limit the one the physics surface is at.

* Improved our debugging by moving the debug settings from the component to the task jobs struct, so you can set to debug a specific task instead of all tasks being started by that component. Cleaned up and improved it code wise as well so it's less boiler plate. 

* Added so when we print what physics surface we're trying to apply, we print the actual display name of it instead of just the index

 * Added so if trying to paint with physics surface, but none of the mesh materials has it, or any blendable surfaces etc., then we don't even start the task but it fails at CheckValid. 

* Improved the UX in the Editor Widget regarding blendable surfaces.


<RichTextBlock.Bold>Bug Fixes</>

* Fixed pretty big bug when Registering Physics Surface if the first elements in the Physics Surface list was None, or if elements in between phys surfaces was None. Then we got an issue because GetAllPhysicsSurfaces, and GetDefault<UPhysicsSettings>()->PhysicalSurfaces didn't actually returned those elements, so we got a miss match where we filled the drop down lists with only actual physics surfaces, so when selecting a surface that came After a None element, the selected index didn't match the physics surface we thought we selected, so we would register another physics surface. 
  So fixed so we fill in so if there are any Nones in between physics surface etc., they will also be added, with SurfaceType13 for instance, so the drop down list matches and what we select there will always be the matching physics surface. 

* Fixed issue with paint component if adding it in runtime in BP and then Immediediately calling a paint job where we got crash. Now every paint job checks if it's been intialized properly, and if not, it does that. 

* Fixed bugg with Auto Add Color Component of using it with physics surface, where it didn't set include amount of painted colors correctly, and thus didn't get the correct result back since it used paint strength on channel, instead of paint strength on physics surface. 

* Fixed crashes when using Set Members in Apply Colors using Physics Surface structs as the tooltips was too big. 

* Fixed Paint Limit bug where if set to limit color if limitColorIfTheColorWasAlreadyOverTheLimit was true

* Increased delay until we run CleanUpOldVertexColorBuffer(), as well as added a valid index check, which should hopefully fix a very rare crash that occur there. 



<LargeText>Version 1.16</>

<RichTextBlock.Bold>Example Project</>

* Added so you can Add/Remove Actors & Mesh Components in Runtime to Rain Example, additional polish and small bug fixes. 

* Added Unreal Water Blueprint and Paint Within Area Logic on it to the Example Project. 

* Big Pass at Rain Example where it supports replication where server and clients are in sync with which seeds to use for each paint loops so they paint randomly the same. Really useful if what you want to paint randomly may affect gameplay, like Acid that should damage players where clients has to see it at the exact places the server has it. 

* Pass at Auto Add Color Component where we fixed bug where if the Mesh constnatly got painted, it reset it's timer so it never for instance started drying the character in the example project if they where standing in a body of water, so the parts of the character not in water didn't get dried. Also some general improvements and clean up of logic


<RichTextBlock.Bold>New Features</>

* Added so you can choose to only randomize vertices within area of effect instead of the entire mesh, which is a much more optimized solution for things such as shower heads. 

* Added to the Material Data Asset a TMap with a Family of Physics Surface and DoesPhysicsSurfaceBelongToPhysicsSurfaceFamily() function to check if a physics surface is a part of a family, as well as editor widget implementation where you can Create a Family and Add childs. 
  This can be used if you want to Apply Colors Using Physics Surface where we can use Parents and Childs of a Family to get the Channel to Apply color on, so for instance a Wheel with Sand can Paint on a Material that may not have Sand Registered, but has a Child of it like Cobble-Sand Registered, then we can apply color to whatever channel that is on just by applying colors with Sand. The same can be done vice versa. You can also make much more comfortable implementations where you need to check if a physics surface is a part of a family, for example if electricity should be able to be spread on all Metallic Surfaces, and you have like Aluminium, Steel Crate etc. Then instead of having a bunch of branches for each Metallic one, you just run DoesPhysicsSurfaceBelongToPhysicsSurfaceFamily with Metallic, and any new Metallic like physics surface can just be registered in the Editor Widget, you don't have to jump around and update any logic in a bunch of BPs. 

* Added so you can Apply Colors Using Physics Surface, if the Material has the Physics Surface Registered it will apply colors to whatever channel it is registered to. You can also choose if a Parent Physics Surface can Apply colors on a child, and vice versa, which is quite useful if for instance a Character that has fundemental surfaces such as Sand, and is walking on Cobble-Sand or Asphalt-Sand, then if the Physics Surface Family is setup correctly where they're children of Sand, we can apply colors on whatever channel the character has Sand on. If we failed to get any colors to apply then you can optionally fall back to use whatever colors is set to the regular RGBA. 
  The Example Project has been updated so almost everything is using this now. Highly Recommend checking out the Example Projects Physics Surface Family how it's setup, and implementations of like character when we're painting his feet with whatever surface we walked on. 


<RichTextBlock.Bold>Misc</>

* Set includeAmountOfPaintedColorsOfEachChannel to be True, since it only makes tasks such as GetAllColorsOnly, Paint Color Snippet, Paint Jobs with Set instead of Adding colors, SetMeshColorsUsingColorArray to take a bit longer to finish since it will require tasks that doesn't need to loop through all vertices to do so (unless they've also been set to include vertex colors or something). 
  These are not super common, and the data from this is something we often want to use. So think it will easier for users just to set this to false if they're doing one of those tasks instead of requiring everyone to remember to turn it on.

* Removed old unnecessary parameter in Auto Add Colors Entire Mesh Component

* Added so you in Task Result can get the Associated Paint Component, as well as the Vertex Color Channels that got affected. 

* Removed so you don't have to set any Face Index for Static Mesh Components anymore since we could get the Material of the section just through code! So line traces doesn't have to be Trace Complex True etc. 

* Changed it back so we store color snippets as TArrays FColor again, since it was Much much more expensive with serialized strings. For instance a cheap mesh with 1000 verts cost 56kb, and with TArray it cost 3.9kb. If it was a 100 000 verts it would've been 5.6MB which is way to much for just 1 snippet on one mesh. 

* Did a pass at Auto Add Color Component we added last patch, where i've added a function so you can now auto paint using a physics surface, and not just on specified channel. Great if you don't know which channel for instance Wet is on! Also changed so instead of setting default values on the components we set them in the start function parameters, was more understandable since we now have paint on channel option, and with physics surface option. Also made it possible so you can Stop it, in case you want to start a new one. Added small fixes so a new one won't be started if it's already running

* Updated GetColorsToApplyFromPhysicsSurface() so it now uses the new Physics Surface Family instead of the old thing we had where we per material registered how much to return for each surface. I removed that old stuff from the editor widget since it was hard to understand etc. It ofc. also checks with whatever is registered on the channels and the blendables as well. 

* Added so in mesh vertex data per lod you get the amount of vertices as well

* Added the option IF the paint job should even be applied, so you can get things like Comparison %, amount of colors of each channel IF you apply the paint job, but without actually applying it. Also stuff like Task Duration

* Made it possible to override the seed when running Paint Entire Mesh Randomness, so you can have server and clients be synched so they all get painted randomly exactly the same. 


<RichTextBlock.Bold>Bug Fixes</>

* Fixed warning of Monolithic Headers, i.e. removed include of Engine.h and added BoxComponent

* Removed Settings from AdditionalDataToPassThrough to make it much more lightweight. It also fixed a crash issue i got with shipping. Added more floats etc. instead so whatever you used with the settings, you can simply just use the regular floats and vectors instead. 

* Fixed important bug regarding how we set the sections vertex amount, where if the previous section had more vertices, then the task failed. This could be the issue if it was a Merged Mesh. 

* Minor fix to Auto Add Colors where it doesn't add more tasks unless it doesn't have any active tasks itself. I.e. just because something else finished a paint task on the mesh, doesn't mean that it adds on itself. 

* Fixed crash issue if no material data asset was set. 

* Fixed bug in Game Instance Paint Task Finished Delegate where the amount of colors of each channel it passed through wasn't the amount After paint job has been applied, but before. 

* Fixed compile issue that could occur because of a logical ambiguous if branch

)"))


#if ENGINE_MAJOR_VERSION == 4

.TextStyle(FEditorStyle::Get(), "NormalText")
.DecoratorStyleSet(&FEditorStyle::Get())

#elif ENGINE_MAJOR_VERSION == 5

	#if ENGINE_MINOR_VERSION == 0

.TextStyle(FEditorStyle::Get(), "NormalText")
.DecoratorStyleSet(&FEditorStyle::Get())

	#endif

.TextStyle(FAppStyle::Get(), "NormalText")
.DecoratorStyleSet(&FAppStyle::Get())

#endif


.AutoWrapText(true)
+ SRichTextBlock::HyperlinkDecorator(TEXT("browser"), FSlateHyperlinkRun::FOnClick::CreateStatic(&OnBrowserLinkClicked))
		]
		]
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(1.0f)
		[
			SNew(SButton)
			.Text(FText::FromString("Leave a Review"))
		.HAlign(HAlign_Center)
		.OnClicked_Lambda([]()
			{
				const FString URL = "https://www.unrealengine.com/marketplace/en-US/product/runtime-vertex-color-paint-detection-plugin";
				FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);

				return FReply::Handled();
			})
		]
	+ SHorizontalBox::Slot().AutoWidth()
		[
			SNew(SSpacer)
			.Size(FVector2D(20, 10))
		]
	+ SHorizontalBox::Slot().FillWidth(1.0f)
		[
			SNew(SButton)
			.Text(FText::FromString("Close Window"))
		.HAlign(HAlign_Center)
		.OnClicked_Lambda([Window]()
			{
				Window->RequestDestroyWindow();

				return FReply::Handled();
			})
		]
		];

	WindowContent->SetContent(InnerContent);
	Window = FSlateApplication::Get().AddWindow(Window.ToSharedRef());
}
