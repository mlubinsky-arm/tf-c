
//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT 2013-2017 ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifdef MBED_CLOUD_CLIENT_USER_CONFIG_FILE
#include MBED_CLOUD_CLIENT_USER_CONFIG_FILE
#endif

#include <stdint.h>

#ifdef MBED_CLOUD_DEV_UPDATE_ID
const uint8_t arm_uc_vendor_id[] = {
    0xfa, 0x6b, 0x4a, 0x53, 0xd5, 0xad, 0x5f, 0xdf, 0xbe, 0x9d, 0xe6, 0x63, 0xe4, 0xd4, 0x1f, 0xfe
};
const uint16_t arm_uc_vendor_id_size = sizeof(arm_uc_vendor_id);

const uint8_t arm_uc_class_id[]  = {
    0x1a, 0xba, 0xd2, 0x2, 0xea, 0xf8, 0x5a, 0xe3, 0xa3, 0x3e, 0x28, 0x7, 0x75, 0x74, 0x18, 0xc2
};
const uint16_t arm_uc_class_id_size = sizeof(arm_uc_class_id);
#endif

#ifdef MBED_CLOUD_DEV_UPDATE_CERT
const uint8_t arm_uc_default_fingerprint[] =  {
    0x7, 0xda, 0xe9, 0xa, 0x10, 0x4b, 0x5e, 0x70, 0x93, 0x81, 0x9c, 0x4d, 0xc6, 0xe9, 0x82, 0x9f,
    0x27, 0xfb, 0x45, 0xf6, 0x43, 0x31, 0x70, 0x78, 0xba, 0xb9, 0xb4, 0xe3, 0x6a, 0xe4, 0xdb, 0x76
};
const uint16_t arm_uc_default_fingerprint_size =
    sizeof(arm_uc_default_fingerprint);

const uint8_t arm_uc_default_subject_key_identifier[] =  {
    0x61, 0x31, 0xf, 0x56, 0x31, 0xd1, 0x9f, 0xa8, 0xb7, 0xfb, 0xfa, 0xe1, 0x90, 0x59, 0x47, 0x15,
    0x3d, 0x83, 0xaa, 0xc9
};
const uint16_t arm_uc_default_subject_key_identifier_size =
    sizeof(arm_uc_default_subject_key_identifier);

const uint8_t arm_uc_default_certificate[] = {
    0x30, 0x82, 0x1, 0x80, 0x30, 0x82, 0x1, 0x25, 0xa0, 0x3, 0x2, 0x1, 0x2, 0x2, 0x14, 0x26,
    0xf8, 0xdf, 0xcd, 0x60, 0x20, 0xec, 0x5e, 0xbd, 0x6, 0xb3, 0x80, 0x16, 0x8b, 0x38, 0xea, 0xfe,
    0x76, 0xe0, 0xfd, 0x30, 0xa, 0x6, 0x8, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x4, 0x3, 0x2, 0x30,
    0x12, 0x31, 0x10, 0x30, 0xe, 0x6, 0x3, 0x55, 0x4, 0x3, 0xc, 0x7, 0x61, 0x72, 0x6d, 0x2e,
    0x63, 0x6f, 0x6d, 0x30, 0x1e, 0x17, 0xd, 0x32, 0x30, 0x30, 0x34, 0x31, 0x36, 0x30, 0x33, 0x34,
    0x38, 0x35, 0x37, 0x5a, 0x17, 0xd, 0x32, 0x30, 0x30, 0x37, 0x31, 0x35, 0x30, 0x33, 0x34, 0x38,
    0x35, 0x37, 0x5a, 0x30, 0x12, 0x31, 0x10, 0x30, 0xe, 0x6, 0x3, 0x55, 0x4, 0x3, 0xc, 0x7,
    0x61, 0x72, 0x6d, 0x2e, 0x63, 0x6f, 0x6d, 0x30, 0x59, 0x30, 0x13, 0x6, 0x7, 0x2a, 0x86, 0x48,
    0xce, 0x3d, 0x2, 0x1, 0x6, 0x8, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x3, 0x1, 0x7, 0x3, 0x42,
    0x0, 0x4, 0xef, 0xc, 0x31, 0x47, 0x62, 0xfb, 0xd6, 0x8b, 0x9b, 0xf2, 0x79, 0x6d, 0xa7, 0x70,
    0x46, 0x1f, 0x9, 0xc9, 0x8a, 0xde, 0x91, 0xa, 0x6a, 0x63, 0x27, 0xaf, 0x43, 0x71, 0xeb, 0xd3,
    0x97, 0x48, 0x28, 0xbc, 0xa7, 0x72, 0x27, 0x44, 0x64, 0x81, 0x7, 0xcf, 0x59, 0xc9, 0xae, 0x5b,
    0x36, 0xfb, 0x90, 0x85, 0x3b, 0x3f, 0x61, 0x53, 0x13, 0x81, 0x71, 0xcf, 0x71, 0x92, 0x78, 0xda,
    0x43, 0xeb, 0xa3, 0x59, 0x30, 0x57, 0x30, 0xb, 0x6, 0x3, 0x55, 0x1d, 0xf, 0x4, 0x4, 0x3,
    0x2, 0x7, 0x80, 0x30, 0x14, 0x6, 0x3, 0x55, 0x1d, 0x11, 0x4, 0xd, 0x30, 0xb, 0x82, 0x9,
    0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x68, 0x6f, 0x73, 0x74, 0x30, 0x13, 0x6, 0x3, 0x55, 0x1d, 0x25,
    0x4, 0xc, 0x30, 0xa, 0x6, 0x8, 0x2b, 0x6, 0x1, 0x5, 0x5, 0x7, 0x3, 0x3, 0x30, 0x1d,
    0x6, 0x3, 0x55, 0x1d, 0xe, 0x4, 0x16, 0x4, 0x14, 0x61, 0x31, 0xf, 0x56, 0x31, 0xd1, 0x9f,
    0xa8, 0xb7, 0xfb, 0xfa, 0xe1, 0x90, 0x59, 0x47, 0x15, 0x3d, 0x83, 0xaa, 0xc9, 0x30, 0xa, 0x6,
    0x8, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x4, 0x3, 0x2, 0x3, 0x49, 0x0, 0x30, 0x46, 0x2, 0x21,
    0x0, 0xc5, 0x1f, 0xaf, 0x9a, 0xda, 0x54, 0x6d, 0x82, 0x53, 0xcc, 0x85, 0x51, 0xef, 0x59, 0xb4,
    0xb2, 0x6e, 0x39, 0x2e, 0x34, 0xf0, 0x70, 0xfb, 0xf4, 0x3a, 0xee, 0x7, 0xc5, 0x2c, 0x41, 0x5b,
    0xca, 0x2, 0x21, 0x0, 0x91, 0xbb, 0x38, 0x55, 0x5, 0xc, 0xfe, 0x97, 0xd, 0x2e, 0xaa, 0x42,
    0x1f, 0xda, 0x77, 0x11, 0x86, 0xd1, 0xe4, 0xf1, 0x37, 0x5c, 0x92, 0xc2, 0xb9, 0xe1, 0xdd, 0x61,
    0xd2, 0x68, 0x2c, 0xb
};
const uint16_t arm_uc_default_certificate_size = sizeof(arm_uc_default_certificate);
#endif


#ifdef MBED_CLOUD_DEV_UPDATE_PSK
const uint8_t arm_uc_default_psk[] = {
    
};
const uint8_t arm_uc_default_psk_size = sizeof(arm_uc_default_psk);
const uint16_t arm_uc_default_psk_bits = sizeof(arm_uc_default_psk)*8;

const uint8_t arm_uc_default_psk_id[] = {
    
};
const uint8_t arm_uc_default_psk_id_size = sizeof(arm_uc_default_psk_id);
#endif
