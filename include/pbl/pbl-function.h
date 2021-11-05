///
/// Function-related types
///
/// @author Luna-Klatzer

#include "./additional/va-opt.h"
#include "./pbl-string.h"
#include "./pbl-types.h"
#include "./pbl-mem.h"

#ifndef PARAC_MODULES_FUNCTION_H
#define PARAC_MODULES_FUNCTION_H

#ifdef __cplusplus
extern "C" {
#endif

// ---- Raise Exception Macros ----------------------------------------------------------------------------------------

/// @brief This a "one-liner" constructor, which will allocate a new exception and raise it (return to the caller of the
/// stack).
/// @param exception The exception that shall be raised.
/// @param call_return_type The return type of the function where this macro is invoked.
/// @note This requires the existence of 'this_call_meta' of type 'PblMetaFunctionCallCtx_T'.
#define PBL_RAISE_EXCEPTION(exception, call_return_type)                                                               \
  PblRaiseNewException(this_call_meta, exception);                                                                     \
  return call_return_type##_DeclDefault;

// ---- Invoke with Exception handling (in C or Para-C context) -------------------------------------------------------

/// @brief Calls a function, passes the args and creates the appropriate unique identifier for the function call.
/// @param func The function that should be called with the passed variadic arguments.
/// @param var_to_pass The variable the return of the function should be passed to.
/// @param unique_id The unique id the call ctx should be declared as. It follows the following scheme: unique##_##func.
/// @param is_threaded Whether this macro is invoked in a threaded context. This variable is directly passed to the
/// created context.
/// @param meta_ctx The meta_ctx that should be used as a parent ctx (invocation context) of the child function
/// @param args The arguments to pass to the local function
#define PBL_CALL_FUNC_WITH_META_CTX(func, var_to_pass, unique_id, is_threaded, meta_ctx, args)                         \
  PblMetaFunctionCallCtx_T *unique_id##_callctx_##func = PblGetMetaFunctionCallCtxT(                                   \
    PblGetStringT(#func), PblGetBoolT(false), PblGetUIntT(0), is_threaded, NULL, meta_ctx, NULL);                      \
  (var_to_pass) = func(unique_id##_callctx_##func IFN(args)(, args));

// ---- Invoke and Catch Exception handling ---------------------------------------------------------------------------

/// @brief This is a "one-liner" constructor for Para-C functions, which will call the passed function with the args
/// (__VA_ARGS__) and if an exception is raised update the local ctx appropriately
/// @param func The function that should be called with the passed variadic arguments.
/// @param var_to_pass The variable the return of the function should be passed to.
/// @param unique_id The unique id the call ctx should be declared as. It follows the following scheme: unique##_##func.
/// @param is_threaded Whether this macro is invoked in a threaded context. This variable is directly passed to the
/// created context.
/// @param args the arguments to pass to the function, leave empty if none shall be passed.
#define PBL_C_BASE_EXCEPTION_CATCH_CONSTRUCTOR(func, var_to_pass, unique_id, is_threaded, meta_ctx, args)              \
  PBL_CALL_FUNC_WITH_META_CTX(func, var_to_pass, unique_id, is_threaded, meta_ctx, IFN(args)(args))                    \
  if (unique_id##_callctx_##func->actual.is_failure.actual) {                                                          \
    (meta_ctx)->actual.is_failure = PblGetBoolT(true);                                                                 \
    (meta_ctx)->actual.exception = unique_id##_callctx_##func->actual.exception;                                       \
    (meta_ctx)->actual.failure_origin_ctx = unique_id##_callctx_##func->actual.failure_origin_ctx                      \
                                              ? unique_id##_callctx_##func->actual.failure_origin_ctx                  \
                                              : unique_id##_callctx_##func;                                            \
  }

/// @brief This is a "one-liner" constructor for Para-C functions, which will call the passed function with the args
/// (__VA_ARGS__) and return to the caller of the stack, if the called function returns with a raised exception.
/// @param func The function that should be called with the passed variadic arguments.
/// @param var_to_pass The variable the return of the function should be passed to.
/// @param ctx_rtype The return type of the context (function) where this macro is used. If an exception occurs the
/// default value (_DeclDefault) will be returned.
/// @param unique_id The unique id the call ctx should be declared as. It follows the following scheme: unique##_##func.
/// @note This requires the existence of 'this_call_meta' of type 'PblMetaFunctionCallCtx_T'
#define PBL_EXCEPTION_CATCH_FUNC_CONSTRUCTOR(func, var_to_pass, ctx_rtype, unique_id, args...)                         \
  PBL_CALL_FUNC_WITH_META_CTX(func, var_to_pass, unique_id, this_call_meta->actual.is_threaded, this_call_meta,        \
                              IFN(args)(args))                                                                         \
  if (unique_id##_callctx_##func->actual.is_failure.actual) {                                                          \
    this_call_meta->actual.is_failure = PblGetBoolT(true);                                                             \
    this_call_meta->actual.exception = unique_id##_callctx_##func->actual.exception;                                   \
    this_call_meta->actual.failure_origin_ctx = unique_id##_callctx_##func;                                            \
    return ctx_rtype##_DeclDefault;                                                                                    \
  }

// ---- Exception Catching (try-except) -------------------------------------------------------------------------------

/// @brief Creates a try-except block, which contain the executed code-block and the except-block if an exception is
/// raised
/// @param block The block to execute
/// @param except_block The except block, which should contain checks created by EXCEPTION_CREATE_EXCEPT_BLOCK()
/// @param block_identifier The unique local identifier, which should be passed to all items in the blocks as well to
/// correctly update the information.
/// @param meta_ctx The meta_ctx that should be used as a parent ctx (invocation context) of the child function
/// @param call_return_type The return type of the function where this macro is invoked.
#define PBL_EXCEPTION_TRY_EXCEPT_BLOCK(block, except_block, block_identifier, meta_ctx, call_return_type)              \
  PblException_T block_identifier##_local_catched_exc;                                                                 \
  PblBool_T block_identifier##_invoke_except = PblGetBoolT(false);                                                     \
  PblBool_T block_identifier##_except_handled = PblGetBoolT(false);                                                    \
  block;                                                                                                               \
  block_identifier##_except_block : (except_block);                                                                      \
  block_identifier##_finish_up : {                                                                                     \
    if (block_identifier##_invoke_except.actual && !block_identifier##_except_handled.actual) {                        \
      return call_return_type##_DeclDefault;                                                                           \
    }                                                                                                                  \
  }

/// @brief This is a "one-liner" constructor for functions that accept arguments and have a return, which will call the
/// passed function with the args (__VA_ARGS__) and if an exception is raised jump to the except blocks.
/// @param func The function that should be called with the passed variadic arguments.
/// @param var_to_pass The variable the return of the function should be passed to.
/// @param ctx_rtype The return type of the context (function) where this macro is used. If an exception occurs the
/// default value (_DeclDefault) will be returned.
/// @param unique_id The unique id the call ctx should be declared as. It follows the following scheme: unique##_##func.
/// @note This requires the existence of 'this_call_meta' of type 'PblMetaFunctionCallCtx_T'
#define PBL_EXCEPTION_TRY_BLOCK_CATCH_FUNC_CONSTRUCTOR(func, var_to_pass, ctx_rtype, unique_id, block_identifier,      \
                                                       args...)                                                        \
  PBL_CALL_FUNC_WITH_META_CTX(func, var_to_pass, unique_id, this_call_meta->actual.is_threaded, this_call_meta,        \
                              IFN(args)(args))                                                                         \
  if (unique_id##_callctx_##func->actual.is_failure.actual) {                                                          \
    block_identifier##_local_catched_exc = *((PblException_T *) unique_id##_callctx_##func->actual.exception);         \
    block_identifier##_invoke_except = PblGetBoolT(true);                                                              \
    goto block_identifier##_except_block;                                                                              \
  }

/// @brief Adds an exception clause to the current block - this should be used to create a block statement which then is
/// passed as an argument to EXCEPTION_TRY_EXCEPT_BLOCK()
#define PBL_EXCEPTION_CREATE_EXCEPT_BLOCK(exception_name, block_to_execute, block_identifier)                          \
  if (block_identifier##_invoke_except.actual) {                                                                       \
    block_to_execute;                                                                                                  \
    block_identifier##_except_handled = PblGetBoolT(true);                                                             \
    goto block_identifier##_finish_up;                                                                                 \
  }

// ---- Exception Implementation --------------------------------------------------------------------------------------

/// (Never use this for malloc - this only indicates the usable memory space)
/// Returns the size in bytes of the PBL Long Double type
#define PblException_T_Size (4 * PblString_T_Size + PblUInt_T_Size + 2 * sizeof(void*))
/// Returns the declaration default for the type 'PblException_T'
#define PblException_T_DeclDefault PBL_DECLARATION_CONSTRUCTOR(PblException_T)
/// Returns the definition default, for the type 'PblREPLACE_T', where the children have not been set yet and only the
/// value itself 'exists' already. This means when accessing the children the Declaration Defaults are returned, unless
/// they have been altered/set
#define PblException_T_DefDefault                                                                                      \
  PBL_DEFINITION_UNSET_CONSTRUCTOR(                                                                             \
    PblException_T, .msg = PblString_T_DefDefault, .name = PblString_T_DefDefault, .filename = PblString_T_DefDefault, \
    .line = PblUInt_T_DefDefault, .line_content = PblString_T_DefDefault, .parent_exc = NULL, .child_exc = NULL)
/// Returns the definition default, with the children having been as well initialised, for the type 'PblException_T'
#define PblException_T_DefWithSetChildrenDefault                                                                       \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(                                                                                   \
    PblException_T, .msg = PblString_T_DefWithSetChildrenDefault, .name = PblString_T_DefWithSetChildrenDefault,       \
    .filename = PblString_T_DefWithSetChildrenDefault, .line = PblUInt_T_DefWithSetChildrenDefault,                    \
    .line_content = PblString_T_DefWithSetChildrenDefault, .parent_exc = NULL, .child_exc = NULL)

struct PblException_Base {
  /// Returns the message of the exception
  PblString_T msg;
  /// Returns the name of the exception
  PblString_T name;
  /// Returns the filename where the exception occurred
  PblString_T filename;
  /// Returns the line where the exception occurred
  PblUInt_T line;
  /// Returns the content of the line - macro inserted
  PblString_T line_content;
  /// Returns the parent exception if it exists
  /// (Reserved for PblException_T)
  void *parent_exc;
  /// Returns the child exception if it exists
  /// (Reserved for PblException_T)
  void *child_exc;
};

/// Exception implementation
struct PblException PBL_TYPE_DEFINITION_WRAPPER_CONSTRUCTOR(struct PblException_Base)
/// Exception implementation
typedef struct PblException PblException_T;


// ---- Function Meta Type --------------------------------------------------------------------------------------------

/// (Never use this for malloc - this only indicates the usable memory space)
/// Returns the size in bytes of the PBL MetaFunctionCallCtx type
#define PblMetaFunctionCallCtx_T_Size \
  (PblBool_T_Size + PblUInt_T_Size + PblBool_T_Size + 2 * sizeof(PblMetaFunctionCallCtx_T*) + sizeof(NULL))
/// Returns the declaration default for the type 'PblMetaFunctionCallCtx_T'
#define PblMetaFunctionCallCtx_T_DeclDefault PBL_DECLARATION_CONSTRUCTOR(PblMetaFunctionCallCtx_T)
/// Returns the definition default, for the type 'PblREPLACE_T', where the children have not been set yet and only the
/// value itself 'exists' already. This means when accessing the children the Declaration Defaults are returned, unless
/// they have been altered/set
#define PblMetaFunctionCallCtx_T_DefDefault                                                                            \
  PBL_DEFINITION_UNSET_CONSTRUCTOR(PblMetaFunctionCallCtx_T, .function_identifier = PblString_T_DefDefault,     \
                                          .is_failure = PblBool_T_DefDefault, .arg_amount = PblUInt_T_DefDefault,      \
                                          .is_threaded = PblBool_T_DefDefault, .failure_origin_ctx = NULL,             \
                                          .call_origin_ctx = NULL, .exception = NULL)
/// Returns the definition default, with the children having been as well initialised, for the type 'PblMetaFunctionCallCtx_T'
#define PblMetaFunctionCallCtx_T_DefWithSetChildrenDefault                                                             \
  PBL_DEFINITION_STRUCT_CONSTRUCTOR(                                                                                   \
    PblMetaFunctionCallCtx_T, .function_identifier = PblString_T_DefWithSetChildrenDefault,                            \
    .is_failure = PblBool_T_DefWithSetChildrenDefault, .arg_amount = PblUInt_T_DefWithSetChildrenDefault,              \
    .is_threaded = PblBool_T_DefWithSetChildrenDefault, .failure_origin_ctx = NULL, .call_origin_ctx = NULL,           \
    .exception = NULL)

/// Base Meta Type passed to all functions
struct PblMetaFunctionCallCtx_Base {
  /// Returns the function name - identifier
  PblString_T function_identifier;
  /// Returns whether the function failed due to an exception occurring
  PblBool_T is_failure;
  /// Returns the amount of arguments passed
  PblUInt_T arg_amount;
  /// Returns whether the function is threaded -> in an thread / threaded context
  PblBool_T is_threaded;
  /// Returns the origin meta variable for the function where the exception occurred
  /// Only available when is_failure is true
  /// (Reserved for PblMetaFunctionCallCtx_T)
  void* failure_origin_ctx;
  /// Returns the call origin ctx, which called the function associated with *this* context
  /// (Reserved for PblMetaFunctionCallCtx_T)
  void* call_origin_ctx;
  /// Returns the exception whether one was raised
  /// Only available when is_failure is true
  /// (Reserved for PblException_T)
  PblException_T* exception;
};

struct PblMetaFunctionCallCtx PBL_TYPE_DEFINITION_WRAPPER_CONSTRUCTOR(struct PblMetaFunctionCallCtx_Base)

/// Base Meta Type passed to all functions
typedef struct PblMetaFunctionCallCtx PblMetaFunctionCallCtx_T;

// ---- Helper Functions ----------------------------------------------------------------------------------------------

/**
 * @brief Allocates a new function call ctx, which will be located in the heap to store the function info publicly
 * as long as necessary, and avoid the destruction after leaving the function stack
 * @return The new allocated ctx (pointer)
 */
PblMetaFunctionCallCtx_T *PblAllocateMetaFunctionCallCtxT();

/**
 * @brief Gets a new function call ctx, which will be located in the heap
 * @return The newly created function call ctx (pointer)
 */
PblMetaFunctionCallCtx_T *PblGetMetaFunctionCallCtxT(PblString_T function_identifier, PblBool_T is_failure,
                                                     PblUInt_T arg_amount, PblBool_T is_threaded,
                                                     PblMetaFunctionCallCtx_T *failure_origin_ctx,
                                                     PblMetaFunctionCallCtx_T *call_origin_ctx,
                                                     PblException_T *exception);

/**
 * @brief Deallocates the passed function call ctx and safely resets all values
 * @param ctx The function call ctx to deallocate
 */
PblVoid_T PblSafeDeallocateMetaFunctionCallCtxT(PblMetaFunctionCallCtx_T *ctx);

/**
 * @brief Allocates a new Exception type ctx, which is located in the heap
 * @return The new allocated exception (pointer)
 */
PblException_T *PblAllocateExceptionType();

/**
 * @brief Gets a new Exception Type, which is located in the heap
 * @return The newly created exception (pointer)
 */
PblException_T *PblGetExceptionT(PblString_T msg, PblString_T name, PblString_T filename, PblUInt_T line,
                                 PblString_T line_content, PblVoid_T *parent_exc, PblVoid_T *child_exc);

/**
 * @brief Raises a new exception by updating the local context info
 * @param this_call_meta The current context info that should be updated
 * @param exception The exception that was initialised
 */
PblVoid_T PblRaiseNewException(PblMetaFunctionCallCtx_T* this_call_meta, PblException_T *exception);

/**
 * @brief Deallocates the passed exception type and safely resets all values
 * @param exc The exception to deallocate
 * @notes This function will de-allocate the children and parents exceptions as well
 */
PblVoid_T PblSafeDeallocateExceptionT(PblException_T *exc);

/**
 * @brief Cleanups the current exception Context and deallocates the memory that isn't used anymore
 * @param cleanup_ctx The function call ctx that should be cleaned up (including all of it's children)
 */
PblVoid_T PblCleanupExceptionContext(PblMetaFunctionCallCtx_T* cleanup_ctx);


#ifdef __cplusplus
}
#endif

#endif//PARAC_MODULES_FUNCTION_H
