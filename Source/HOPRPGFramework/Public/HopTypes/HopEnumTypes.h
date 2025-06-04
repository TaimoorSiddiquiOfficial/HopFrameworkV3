#pragma once

UENUM()
enum class EHopConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EHopValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EHopSuccessType : uint8
{
	Successful,
	Failed
};