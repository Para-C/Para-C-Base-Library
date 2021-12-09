/// @file pbl-int.c
/// @brief Int Type Implementation based on stdint.h
/// @author Luna-Klatzer
/// @date 2021-11-23
/// @copyright Copyright (c) 2021

#include "./pbl-int.h"

// ---- Cleanup Functions ---------------------------------------------------------------------------------------------

__attribute__((unused)) void __PblInt8_T_Cleanup(PblInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUInt8_T_Cleanup(PblUInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblInt16_T_Cleanup(PblInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUInt16_T_Cleanup(PblUInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblInt32_T_Cleanup(PblInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUInt32_T_Cleanup(PblUInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblInt64_T_Cleanup(PblInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUInt64_T_Cleanup(PblUInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblLeastInt8_T_Cleanup(PblLeastInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblULeastInt8_T_Cleanup(PblULeastInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblLeastInt16_T_Cleanup(PblLeastInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblULeastInt16_T_Cleanup(PblULeastInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblLeastInt32_T_Cleanup(PblLeastInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblULeastInt32_T_Cleanup(PblULeastInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblLeastInt64_T_Cleanup(PblLeastInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblULeastInt64_T_Cleanup(PblULeastInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblFastInt8_T_Cleanup(PblFastInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUFastInt8_T_Cleanup(PblUFastInt8_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblFastInt16_T_Cleanup(PblFastInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUFastInt16_T_Cleanup(PblUFastInt16_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblFastInt32_T_Cleanup(PblFastInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUFastInt32_T_Cleanup(PblUFastInt32_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblFastInt64_T_Cleanup(PblFastInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

__attribute__((unused)) void __PblUFastInt64_T_Cleanup(PblUFastInt64_T **value)  PBL_DEFAULT_CLEANUP_CONSTRUCTOR(value);

// ---- Helper Functions ----------------------------------------------------------------------------------------------

PblInt8_T* PblGetInt8T(int8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblInt8_T, int8_t)
}

PblUInt8_T* PblGetUInt8T(uint8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUInt8_T, uint8_t)
}

PblInt16_T* PblGetInt16T(int16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblInt16_T, int16_t)
}

PblUInt16_T* PblGetUInt16T(uint16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUInt16_T, uint16_t)
}

PblInt32_T* PblGetInt32T(int32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblInt32_T, int32_t)
}

PblUInt32_T* PblGetUInt32T(uint32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUInt32_T, uint32_t)
}

PblInt64_T* PblGetInt64T(int64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblInt64_T, int64_t)
}

PblUInt64_T* PblGetUInt64T(uint64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUInt64_T, uint64_t)
}

PblLeastInt8_T* PblGetLeastInt8T(int_least8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblLeastInt8_T, int_least8_t)
}

PblULeastInt8_T* PblGetULeastInt8T(uint_least8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblULeastInt8_T, uint_least8_t)
}

PblLeastInt16_T* PblGetLeastInt16T(int_least16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblLeastInt16_T, int_least16_t)
}

PblULeastInt16_T* PblGetULeastInt16T(uint_least16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblULeastInt16_T, uint_least16_t)
}

PblLeastInt32_T* PblGetLeastInt32T(int_least32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblLeastInt32_T, int_least32_t)
}

PblULeastInt32_T* PblGetULeastInt32T(uint_least32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblULeastInt32_T, uint_least32_t)
}

PblLeastInt64_T* PblGetLeastInt64T(int_least64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblLeastInt64_T, int_least64_t)
}

PblULeastInt64_T* PblGetULeastInt64T(uint_least64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblULeastInt64_T, uint_least64_t)
}

PblFastInt8_T* PblGetFastInt8T(int_fast8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblFastInt8_T, int_fast8_t)
}

PblUFastInt8_T* PblGetUFastInt8T(uint_fast8_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUFastInt8_T, uint_fast8_t)
}

PblFastInt16_T* PblGetFastInt16T(int_fast16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblFastInt16_T, int_fast16_t)
}

PblUFastInt16_T* PblGetUFastInt16T(uint_fast16_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUFastInt16_T, uint_fast16_t)
}

PblFastInt32_T* PblGetFastInt32T(int_fast32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblFastInt32_T, int_fast32_t)
}

PblUFastInt32_T* PblGetUFastInt32T(uint_fast32_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUFastInt32_T, uint_fast32_t)
}

PblFastInt64_T* PblGetFastInt64T(int_fast64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblFastInt64_T, int_fast64_t)
}

PblUFastInt64_T* PblGetUFastInt64T(uint_fast64_t val) {
  PBL_CONVERSION_FUNCTION_DEF_CONSTRUCTOR(PblUFastInt64_T, uint_fast64_t)
}
