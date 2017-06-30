////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     ModelTransformer.tcc (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ell
{
namespace model
{
    //
    // ModelTransformer
    //
    template <typename ValueType>
    PortElements<ValueType> ModelTransformer::TransformPortElements(const PortElements<ValueType>& elements)
    {
        auto result = _elementsMap.GetCorrespondingPortElements(PortElementsBase(elements));
        return PortElements<ValueType>(result);
    }

    template <typename ValueType>
    PortElements<ValueType> ModelTransformer::GetCorrespondingOutputs(const OutputPort<ValueType>& port)
    {
        PortElements<ValueType> elements(port);
        return TransformPortElements(elements);
    }

    template <typename ValueType>
    PortElements<ValueType> ModelTransformer::GetCorrespondingOutputs(const PortElements<ValueType>& elements)
    {
        return TransformPortElements(elements);
    }

    template <typename NodeType>
    NodeType* ModelTransformer::GetCorrespondingInputNodeAs(const NodeType* inputNode)
    {
        auto newNodeOutputs = GetCorrespondingOutputs(inputNode->GetOutputPort());
        auto newNodeConst = newNodeOutputs.GetElement(0).ReferencedPort()->GetNode();
        auto newInputNodeConst = dynamic_cast<const NodeType*>(newNodeConst);
        assert(newInputNodeConst != nullptr);
        auto newInputNode = const_cast<NodeType*>(newInputNodeConst);
        return newInputNode;
    }

    template <typename ValueType>
    InputNode<ValueType>* ModelTransformer::GetCorrespondingInputNode(const InputNode<ValueType>* inputNode)
    {
        return GetCorrespondingInputNodeAs(inputNode);
    }

    template <typename ValueType>
    void ModelTransformer::MapNodeOutput(const OutputPort<ValueType>& oldPort, const OutputPort<ValueType>& newPort)
    {
        _elementsMap.MapNodeOutput(&oldPort, PortElementsBase{newPort});
    }

    template <typename ValueType>
    void ModelTransformer::MapNodeOutput(const OutputPort<ValueType>& oldPort, const PortElements<ValueType>& newElements)
    {
        _elementsMap.MapNodeOutput(&oldPort, newElements);
    }

    template <typename ValueType>
    void ModelTransformer::MapNodeOutput(const OutputPort<ValueType>& oldPort, const PortElementsBase& newElements)
    {
        _elementsMap.MapNodeOutput(&oldPort, newElements);
    }

    template <typename NodeType, typename... Args>
    NodeType* ModelTransformer::AddNode(Args&&... args)
    {
        auto newNode = _model.AddNode<NodeType>(std::forward<Args>(args)...);
        _isModelCompilable &= _context.IsNodeCompilable(*newNode);
        return newNode;
    }
}
}
