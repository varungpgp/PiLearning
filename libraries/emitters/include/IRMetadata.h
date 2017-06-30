////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     IRMetadata.h (emitters)
//  Authors:  Lisa Ong
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "IRModuleEmitter.h"

// stl
#include <string>
#include <unordered_set>
#include <vector>

namespace ell
{
namespace emitters
{
    //
    // Metadata tags
    //

    /// <summary> Indicates that a function is a callback. </summary>
    static const std::string c_callbackFunctionTagName = "ell.fn.callback";

    /// <summary> Indicates the Predict function. </summary>
    static const std::string c_predictFunctionTagName = "ell.fn.predict";

    /// <summary> Indicates the Step function, with the value set to the output count. </summary>
    static const std::string c_stepFunctionTagName = "ell.fn.step";

    /// <summary> Indicates the time functions associated with Step, such as GetInterval(). </summary>
    /// <remarks>
    /// Set the value to the API name of the function.
    /// </remarks>
    static const std::string c_stepTimeFunctionTagName = "ell.fn.stepTime";

    /// <summary> Indicates that a function or type should be declared in a generated header. </summary>
    /// <remarks>
    /// For functions, set a function-level tag with an empty value.
    /// For types, set a module-level tag, using the type name as the value.
    /// </remarks>
    static const std::string c_declareInHeaderTagName = "ell.header.declare";

    //
    // Utilities for reading metadata (that wrap IRModuleEmitter)
    //

    /// <summary> Holds a pointer to an llvm::Function and a set of tag values. </summary>
    struct FunctionTagValues
    {
        llvm::Function* function;
        std::vector<std::string> values;
    };

    /// <summary> Gets functions associated with a function-level metadata tag. </summary>
    ///
    /// <param name="moduleEmitter"> The `IRModuleEmitter` containing the module to search </param>
    /// <param name="tag"> The function-level metadata tag. </param>
    ///
    /// <returns> A vector of LLVM functions with values for the given metadata tag. </returns>
    std::vector<FunctionTagValues> GetFunctionsWithTag(IRModuleEmitter& moduleEmitter, const std::string& tag);

    /// <summary> Gets values associated with a module-level metadata tag. </summary>
    ///
    /// <param name="moduleEmitter"> The `IRModuleEmitter` containing the module to search </param>
    /// <param name="tag"> The global metadata tag. </param>
    ///
    /// <returns> An unordered_set of values for the given metadata tag. </returns>
    std::unordered_set<std::string> GetModuleTagValues(IRModuleEmitter& moduleEmitter, const std::string& tag);
}
}
