# PEI Memory Buckets

A memory bucket is a dedicated range of memory for a specific type of memory (e.g. code or data) that persists over
the lifespan of system operation (e.g. boot or runtime). These properties allow memory management components throughout
the boot to apply specific attributes to the memory for hardware and software enforcement of functional and security
behavior.

Due to a number of technologies moving earlier into the boot flow, memory buckets that are allocated in PEI may now
persist into OS runtime. This is the case for launch Standalone MM in PEI for example. As-is, the DXE Core is unaware
of these bucket allocations so they are ultimately disjoint with equivalent bucket types allocated in DXE.

PEI memory buckets consolidate PEI memory allocations to be contiguous to reduce fragmentation of the memory map.

This feature is controlled via the following PCDs:

- PcdPeiMemoryBucketRuntimeCode
- PcdPeiMemoryBucketRuntimeData
- PcdPeiMemoryBucketAcpiReclaimMemory
- PcdPeiMemoryBucketAcpiMemoryNvs

Platforms that do not allocate memory persistent into runtime do not need to perform integration for this capability
as the default PCD values (`0`) will disable production of the PEI memory bucket HOB exposed to DXE. The functionality
to read the PCDs and produce the HOB is contained within a library called `MemoryBucketLib` that is linked to PEI Core.

Because `MemoryBucketLib` is a library class dependency on `PeiMain`, the instance must be specified in a platform
DSC regardless of whether its functionality will be activated (via non-zero PCD values).

## How to enable PEI Memory Buckets

Set the PCDs listed in the previous section to a non-zero value.

> If you have any of these values set as a non-zero value and no PEI allocations for
> the relevant memory types are made then no memory bucket structures will be allocated or used.

Be aware that the memory bucket sizes should be tuned match the number of pages each memory type uses in PEI to be the
most space efficient.
