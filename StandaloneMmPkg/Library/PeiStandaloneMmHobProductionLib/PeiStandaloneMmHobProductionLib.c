/** @file

  This library provides a single interface the Secured Core infrastructure
  uses to install OEM firmware volumes.

  Copyright (c) Microsoft Corporation<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiPei.h>
#include <Ppi/MpServices.h>
#include <Guid/MpInformation.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>

/**
  Notification function called when EFI_PEI_MP_SERVICES_PPI becomes available. This function produces
  the MP Information HOB needed to initialize Standalone MM.

  @param[in] PeiServices          Indirect reference to the PEI Services Table.
  @param[in] NotifyDescriptor     Address of the notification descriptor data structure.
  @param[in] Ppi                  Address of the PPI that was installed.

  @retval   EFI_SUCCESS           The MP Info HOB was produced successfully.
  @retval   EFI_OUT_OF_RESOURCES  Insufficient memory resources are available to allocate the HOB buffer.

**/
STATIC
EFI_STATUS
EFIAPI
CreateMpInfoHob (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS              Status;
  UINTN                   NumOfCpus;
  UINTN                   NumOfEnabledCpus;
  UINTN                   MpInfoSize;
  UINTN                   Index;
  MP_INFORMATION_HOB_DATA *HobData;
  EFI_PEI_MP_SERVICES_PPI *MpPpi;

  MpPpi = (EFI_PEI_MP_SERVICES_PPI *) Ppi;

  Status = MpPpi->GetNumberOfProcessors (PeiServices, MpPpi, &NumOfCpus, &NumOfEnabledCpus);
  if (EFI_ERROR (Status)) {
    DEBUG ((
      DEBUG_ERROR,
      "[%a] Get number of processors %d, and number of enabled processors %d - %r.\n",
      __FUNCTION__,
      NumOfCpus,
      NumOfEnabledCpus,
      Status
      ));
    goto Done;
  }

  MpInfoSize = sizeof (MP_INFORMATION_HOB_DATA) + (sizeof (EFI_PROCESSOR_INFORMATION) * NumOfCpus);
  HobData = BuildGuidHob (&gMpInformationHobGuid, MpInfoSize);
  ASSERT (HobData != NULL);
  if (HobData == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  ZeroMem (HobData, MpInfoSize);

  HobData->NumberOfProcessors = NumOfCpus;
  HobData->NumberOfEnabledProcessors = NumOfEnabledCpus;

  for (Index = 0; Index < NumOfCpus; Index++) {
    Status = MpPpi->GetProcessorInfo (PeiServices, MpPpi, (UINT32) Index, &HobData->ProcessorInfoBuffer[Index]);
    DEBUG ((DEBUG_INFO, "[%a] Get processor information returned %r.\n", __FUNCTION__, Status));
    DEBUG ((DEBUG_INFO, "[%a] Location.Core %x.\n", __FUNCTION__, HobData->ProcessorInfoBuffer[Index].Location.Core));
    DEBUG ((DEBUG_INFO, "[%a] ProcessorId %x.\n", __FUNCTION__, HobData->ProcessorInfoBuffer[Index].ProcessorId));
    DEBUG ((DEBUG_INFO, "[%a] StatusFlag %x.\n", __FUNCTION__, HobData->ProcessorInfoBuffer[Index].StatusFlag));
    DEBUG ((DEBUG_INFO, "[%a] ExtendedInformation.Location2.Core %x.\n", __FUNCTION__, HobData->ProcessorInfoBuffer[Index].ExtendedInformation.Location2.Core));
  }

Done:
  return Status;
}

STATIC CONST EFI_PEI_NOTIFY_DESCRIPTOR mMpServicesNotify = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEfiPeiMpServicesPpiGuid,
  CreateMpInfoHob
};

/**
  Performs library initialization.

  @param  FileHandle   The handle of FFS header for the loaded driver.
  @param  PeiServices  A pointer to the PEI services.

  @retval EFI_SUCCESS  This constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
PeiStandaloneMmHobProductionLibConstructor (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS  Status;

  Status = PeiServicesNotifyPpi (&mMpServicesNotify);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "[%a] Failed to set up MP Services callback - %r\n", __FUNCTION__, Status));
  }

  return EFI_SUCCESS;
}
