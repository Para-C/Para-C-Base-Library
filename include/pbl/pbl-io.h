///
/// IO Implementation based on stdio.h
///
/// @author Luna-Klatzer

#include <stdbool.h>
#include <stdio.h>

#include "./pbl-string.h"
#include "./pbl-types.h"

#ifndef PARAC_MODULES_IO_H
#define PARAC_MODULES_IO_H

#ifdef __cplusplus
extern "C" {
#endif

// ---- Declarations --------------------------------------------------------------------------------------------------

// ---- File ----------------------------------------------------------------------------------------------------------

/// Size of the type 'PblFile_T' in bytes
#define PblFile_T_Size sizeof(FILE *)
/// Returns the declaration default for the type 'PblFile_T'
#define PblFile_T_DeclDefault PBL_DECLARATION_CONSTRUCTOR(PblFile_T)
/// Returns the definition default, for the type 'PblFile_T', where the children have not been set yet and only the
/// value itself 'exists' already. This means when accessing the actual value the Declaration Default is returned,
/// unless the value has been altered/set
#define PblFile_T_DefDefault PBL_DEFINITION_UNSET_CONSTRUCTOR(PblFile_T, )
/// Returns the definition default, with the children having been as well initialised, for the type 'PblFile_T'
#define PblFile_T_DefWithSetChildrenDefault PBL_DEFINITION_SINGLE_CONSTRUCTOR(PblFile_T, NULL)

/// File Descriptor used to perform I/O actions on a file
struct PblFile PBL_TYPE_DEFINITION_WRAPPER_CONSTRUCTOR(FILE*)
/// Stream type, which is a unique alias for PBLFileDescriptor_T
typedef struct PblFile PblFile_T;

// ---- Stream --------------------------------------------------------------------------------------------------------

/// Size of the type 'PblStream_T' in bytes
#define PblStream_T_Size (PblUInt_T_Size + PblFile_T_Size + PblBool_T_Size + PblString_T_Size)
/// Returns the declaration default for the type 'PblStream_T'
#define PblStream_T_DeclDefault PBL_DECLARATION_CONSTRUCTOR(PblStream_T)
/// Returns the definition default, for the type 'PblStream_T', where the children have not been set yet and only the
/// value itself 'exists' already. This means when accessing the children the Declaration Defaults are returned, unless
/// they have been altered/set
#define PblStream_T_DefDefault                                                                                         \
  PBL_DEFINITION_UNSET_CONSTRUCTOR(PblStream_T, .fd = PblUInt_T_DefDefault, .file = PblFile_T_DefDefault,       \
                                          .open = PblBool_T_DefDefault, .mode = PblString_T_Def)
/// Returns the definition default, with the children having been as well initialised, for the type 'PblStream_T'
#define PblStream_T_DefWithSetChildrenDefault                                                                          \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(                                                                                   \
    PblStream_T, .fd = PblUInt_T_DefWithSetChildrenDefault, .file = PblFile_T_DefWithSetChildrenDefault,               \
    .open = PblBool_T_DefWithSetChildrenDefault, .mode = PblString_T_DefWithSetChildrenDefault)

/// Base Struct of PblString - avoid using this type
struct PblStream_Base {
  /// The unique integer identifier associated with the file Descriptor
  PblUInt_T fd;
  /// The FILE pointer, which points to the stream/file - defined if the stream was opened
  PblFile_T file;
  /// Describes whether the file descriptor is currently in use
  PblBool_T open;
  /// The mode the FILE* was opened
  PblString_T mode;
};

/// File Descriptor used to perform I/O actions on a file
struct PblStream PBL_TYPE_DEFINITION_WRAPPER_CONSTRUCTOR(struct PblStream_Base)
/// Stream type, which is a unique alias for PBLFileDescriptor_T
typedef struct PblStream PblStream_T;

// ---- Streams -------------------------------------------------------------------------------------------------------

/// Standard stream for getting input on the default program console
#define PBL_STREAM_STDIN                                                                                               \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(PblStream_T, .fd = PblGetUIntT(0), .file = PblGetFileT(stdin),                     \
                                    .open = PblGetBoolT(true), .mode = PblGetStringT("a"))

/// Standard stream for outputting to the default program console
#define PBL_STREAM_STDOUT                                                                                              \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(PblStream_T, .fd = PblGetUIntT(1), .file = PblGetFileT(stdout),                    \
                                    .open = PblGetBoolT(true), .mode = PblGetStringT("a"))

/// Standard stream for outputting error messages to the default program console
#define PBL_STREAM_STDERR                                                                                              \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(PblStream_T, .fd = PblGetUIntT(2), .file = PblGetFileT(stderr),                    \
                                    .open = PblGetBoolT(true), .mode = PblGetStringT("a"))

// ---- Handler functions ---------------------------------------------------------------------------------------------

/**
 * @brief Converts the low level C-Type to a PBL File type
 * @param val The FILE pointer C-type
 * @return The newly created PBL File type
 * @note This is a C to Para-C type conversion function - args are in C therefore
 */
PblFile_T PblGetFileT(FILE *val);

/**
 * @brief Converts the low level C-Type to a PBL Stream type. Creates the FILE* pointer as well
 * @param fd The file descriptor that will be converted
 * @param mode The mode that should be used to open the FILE*
 * @return The newly created PBL Stream type
 * @note This is a C to Para-C type conversion function - args are therefore in C
 */
PblStream_T PblGetStreamT(int fd, const char *mode);

/// Arguments struct for PblPrint (PblPrintOverhead)
struct PblPrint_Args {
  PblString_T *out;
  PblStream_T stream;
  PblChar_T end;
};

/**
 * @brief Prints the content of the passed string
 * @param out The string that should be printed out
 * @param stream The stream it should be printed onto
 * @param end The end character that should be printed after 'out'
 * @note This is the base function that is wrapped using 'PblPrintOverhead'
 */
PblVoid_T PblPrint_Base(PblString_T *out, PblStream_T stream, PblChar_T end);

/**
 * @brief Printing overhead for 'PblPrintBase' - this it the function called by the macro 'PblPrint'
 * @param in The parameter struct
 */
PblVoid_T PblPrint_Overhead(struct PblPrint_Args in);

/**
 * @brief Prints the content of the passed string
 * @param out The string that should be printed out (Pointer)
 * @param stream The stream it should be printed onto
 * @param end The end character that should be printed after 'out'
 */
#define PblPrint(...) PblPrint_Overhead((struct PblPrint_Args){__VA_ARGS__});

#ifdef __cplusplus
}
#endif

#endif//PARAC_MODULES_IO_H
