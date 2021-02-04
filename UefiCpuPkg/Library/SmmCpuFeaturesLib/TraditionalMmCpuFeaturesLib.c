#include <PiMm.h>
#include <Library/PcdLib.h>
#include "SmmCpuFeaturesLib.h"

/**
  Gets the maximum number of logical processors from the PCD
  PcdCpuMaxLogicalProcessorNumber.

  This access is abstracted from the PCD services to enforce
  that the PCD be FixedAtBuild in the Standalone MM build of
  this driver.

  @retval  The value of PcdCpuMaxLogicalProcessorNumber.

**/
UINT32
GetCpuMaxLogicalProcessorNumber (
  VOID
  )
{
  return PcdGet32 (PcdCpuMaxLogicalProcessorNumber);
}

/**
  The Traditional MM library constructor.

  @param[in]  ImageHandle  The firmware allocated handle for the EFI image.
  @param[in]  SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS      This constructor always returns success.

**/
EFI_STATUS
EFIAPI
TraditionalMmCpuFeaturesLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return CpuFeaturesLibInitialization ();
}

