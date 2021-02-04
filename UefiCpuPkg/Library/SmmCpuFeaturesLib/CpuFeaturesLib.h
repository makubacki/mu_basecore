/** @file
  Internal library function definitions.

  Copyright (C) Microsoft Corporation.
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _CPU_FEATURES_LIB_H_
#define _CPU_FEATURES_LIB_H_

/**
  Performs library initialization.

  @retval EFI_SUCCESS      This function always returns success.

**/
EFI_STATUS
CpuFeaturesLibInitialization (
  VOID
  );

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
  );

#endif
