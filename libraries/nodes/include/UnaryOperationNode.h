////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     UnaryOperationNode.h (nodes)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "CompilableNode.h"
#include "IRMapCompiler.h"
#include "InputPort.h"
#include "MapCompiler.h"
#include "ModelTransformer.h"
#include "Node.h"
#include "OutputPort.h"
#include "PortElements.h"

// emitters
#include "EmitterTypes.h"

// utilities
#include "TypeName.h"

// stl
#include <cmath>
#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A node that represents a unary function of its input </summary>
    template <typename ValueType>
    class UnaryOperationNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* inputPortName = "input";
        static constexpr const char* outputPortName = "output";
        const model::InputPort<ValueType>& input = _input;
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        UnaryOperationNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="input"> The signal to process. </param>
        /// <param name="operation"> The function to use to process the signal. </param>
        UnaryOperationNode(const model::PortElements<ValueType>& input, emitters::UnaryOperationType operation);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("UnaryOperationNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Adds an object's properties to an `Archiver` </summary>
        ///
        /// <param name="archiver"> The `Archiver` to add the values from the object to </param>
        virtual void WriteToArchive(utilities::Archiver& archiver) const override;

        /// <summary> Sets the internal state of the object according to the archiver passed in </summary>
        ///
        /// <param name="archiver"> The `Archiver` to get state from </param>
        virtual void ReadFromArchive(utilities::Unarchiver& archiver) override;

        /// <summary> Makes a copy of this node in the model being constructed by the transformer </summary>
        virtual void Copy(model::ModelTransformer& transformer) const override;

        /// <summary> Gets the operation performed by this node </summary>
        ///
        /// <returns> The operation </returns>
        emitters::UnaryOperationType GetOperation() const { return _operation; }

    protected:
        virtual void Compute() const override;
        virtual void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;

    private:
        llvm::Function* GetOperator(emitters::IRFunctionEmitter& function) const;
        void CompileLoop(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void CompileExpanded(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);

        template <typename Operation>
        std::vector<ValueType> ComputeOutput(Operation&& function) const;

        // Inputs
        model::InputPort<ValueType> _input;

        // Output
        model::OutputPort<ValueType> _output;

        // Operation
        emitters::UnaryOperationType _operation;
    };
}
}

#include "../tcc/UnaryOperationNode.tcc"