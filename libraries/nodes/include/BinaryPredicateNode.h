////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     BinaryPredicateNode.h (nodes)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "CompilableNodeUtilities.h"
#include "CompilableNode.h"
#include "IRMapCompiler.h"
#include "MapCompiler.h"
#include "Model.h"
#include "ModelTransformer.h"
#include "Node.h"

// emitters
#include "EmitterTypes.h"

// utilities
#include "Exception.h"
#include "IArchivable.h"
#include "TypeName.h"

// stl
#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A node that performs a coordinatewise binary boolean-valued operation on its inputs. </summary>
    template <typename ValueType>
    class BinaryPredicateNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* input1PortName = "input1";
        static constexpr const char* input2PortName = "input2";
        static constexpr const char* outputPortName = "output";
        const model::InputPort<ValueType>& input1 = _input1;
        const model::InputPort<ValueType>& input2 = _input2;
        const model::OutputPort<bool>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        BinaryPredicateNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="input1"> The left-hand input of the arithmetic expression. </param>
        /// <param name="input2"> The right-hand input of the arithmetic expression. </param>
        /// <param name="predicate"> The type of predicate to apply. </param>
        BinaryPredicateNode(const model::PortElements<ValueType>& input1, const model::PortElements<ValueType>& input2, emitters::BinaryPredicateType predicate);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("BinaryPredicateNode"); }

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

        /// <summary> Gets the predicate performed by this node </summary>
        ///
        /// <returns> The predicate </returns>
        emitters::BinaryPredicateType GetPredicate() const { return _predicate; }

    protected:
        virtual void Compute() const override;

        template <typename Operation>
        std::vector<bool> ComputeOutput(Operation&& fn) const;

        virtual void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;

    private:
        void CompileLoop(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void CompileExpanded(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);

        // Inputs
        model::InputPort<ValueType> _input1;
        model::InputPort<ValueType> _input2;

        // Output
        model::OutputPort<bool> _output;

        // Operation
        emitters::BinaryPredicateType _predicate;
    };
}
}

#include "../tcc/BinaryPredicateNode.tcc"