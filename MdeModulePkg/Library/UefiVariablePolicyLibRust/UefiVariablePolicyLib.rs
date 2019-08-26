#![no_std]

extern crate r_efi;

use core::panic::PanicInfo;

use r_efi::efi;
use r_efi::efi::{Status};
use r_efi::efi::{Boolean};
use r_efi::efi::{Guid};

// TODO: Figure out a common place for this to live. DebugLib?
#[panic_handler]
#[allow(clippy::empty_loop)]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[repr(C)]
#[derive(Copy, Clone, Debug)]
pub struct VariablePolicyEntry {
    pub version:        u32,
    pub size:           u16,
    pub offset_to_name: u16,
    pub namespace:      Guid,
    pub min_size:       u32,
    pub max_size:       u32,
    pub attr_must_have: u32,
    pub attr_cant_have: u32,
    pub lock_policy_type:   u8,
    pub padding_3:      [u8; 3]
}

// TODO: Try to move this to share the r_efi::system::RuntimeServices::get_variable definition.
type EfiGetVariable = extern "win64" fn(_: *const efi::Char16, _: *const Guid, _: *mut u32, _: *mut usize, _: *mut u8) -> Status;

#[no_mangle]
#[export_name = "RegisterVariablePolicy"]
pub extern "win64" fn register_variable_policy (
    new_policy: *const VariablePolicyEntry
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "ValidateSetVariable"]
pub extern "win64" fn validate_set_variable (
    variable_name: *const efi::Char16,
    vendor_guid: *const Guid,
    attributes: u32,
    data_size: usize,
    data: *const u8
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "DisableVariablePolicy"]
pub extern "win64" fn disable_variable_policy (
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "DumpVariablePolicy"]
pub extern "win64" fn dump_variable_policy (
    policy: *mut u8,
    size: *mut usize
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "IsVariablePolicyEnabled"]
pub extern "win64" fn is_variable_policy_enabled (
    ) -> efi::Boolean {
    Boolean::TRUE
}

#[no_mangle]
#[export_name = "LockVariablePolicy"]
pub extern "win64" fn lock_variable_policy (
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "IsVariablePolicyInterfaceLocked"]
pub extern "win64" fn is_variable_policy_interface_locked (
    ) -> efi::Boolean {
    Boolean::FALSE
}

#[no_mangle]
#[export_name = "InitVariablePolicyLib"]
pub extern "win64" fn init_variable_policy_lib (
    get_variable_helper: EfiGetVariable
    ) -> Status {
    Status::SUCCESS
}

#[no_mangle]
#[export_name = "IsVariablePolicyLibInitialized"]
pub extern "win64" fn is_variable_policy_lib_initialized (
    ) -> efi::Boolean {
    Boolean::TRUE
}

#[no_mangle]
#[export_name = "DeinitVariablePolicyLib"]
pub extern "win64" fn deinit_variable_policy_lib (
    ) -> Status {
    Status::SUCCESS
}