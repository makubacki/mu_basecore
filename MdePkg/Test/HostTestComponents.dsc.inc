## @file
# Mde DSC include file that includes package host-based unit tests.
#
# This file can be included in a platform DSC file
# by using "!include MdePkg/MdeLibs.dsc.inc" to specify the library instances
# of some EDKII basic/common library classes.
#
# Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[LibraryClasses]
  RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  SmmCpuRendezvousLib|MdePkg/Library/SmmCpuRendezvousLibNull/SmmCpuRendezvousLibNull.inf

[Components.HOST_APPLICATION]
  #
  # Build HOST_APPLICATION that tests the SafeIntLib
  #
  MdePkg/Test/UnitTest/Library/BaseSafeIntLib/TestBaseSafeIntLibHost.inf
  MdePkg/Test/UnitTest/Library/BaseLib/BaseLibUnitTestsHost.inf
  MdePkg/Test/GoogleTest/Library/BaseSafeIntLib/GoogleTestBaseSafeIntLib.inf
  # MU_CHANGE [BEGIN]
  MdePkg/Test/Library/MockUefiBootServicesTableLib/MockUefiBootServicesTableLib.inf
  MdePkg/Test/Library/MockUefiRuntimeServicesTableLib/MockUefiRuntimeServicesTableLib.inf
  MdePkg/Test/Library/RngLibHostTestLfsr/RngLibHostTestLfsr.inf
  MdePkg/Test/Library/StubHobLib/StubHobLib.inf
  MdePkg/Test/Library/StubUefiLib/StubUefiLib.inf
  MdePkg/Test/Library/SynchronizationLibHostUnitTest/SynchronizationLibHostUnitTest.inf
  # MU_CHANGE [END]
