#pragma once

#include "Kismet/KismetSystemLibrary.h"

namespace UHelper
{
	static void PrintToScreen(UObject* WCTXObj, FString Msg, FColor TextColor = FColor::MakeRandomColor(), float Duration = 5.f)
	{
		UKismetSystemLibrary::PrintString(WCTXObj ,Msg, true, true, TextColor, Duration);
	}
}
