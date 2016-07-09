////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     DelayNode.h (features)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// model
#include "Node.h"
#include "ModelTransformer.h"
#include "OutputPortElementList.h"
#include "InputPort.h"
#include "OutputPort.h"

// stl
#include <string>
#include <vector>

namespace nodes
{
    /// <summary> A feature that takes a signal and returns a delayed sample of the signal </summary>
    template <typename ValueType>
    class DelayNode : public model::Node
    {
    public:
        /// <summary> Constructor </summary>
        /// <param name="input"> The signal to delay </param>
        /// <param name="windowSize"> The number of samples to delay the signal </param>
        DelayNode(const model::OutputPortElementList<ValueType>& input, size_t windowSize);
        
        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return "DelayNode"; }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Exposes the output port as a read-only property </summary>
        const model::OutputPort<ValueType>& output = _output;

        virtual void Copy(model::ModelTransformer& transformer) const override;
        virtual void Refine(model::ModelTransformer& transformer) const override;

    protected:
        virtual void Compute() const override;

    private:
        // Inputs
        model::InputPort<ValueType> _input;

        // Output
        model::OutputPort<ValueType> _output;

        // Buffer
        mutable std::vector<std::vector<ValueType>> _samples;
        size_t _windowSize;
    };
}

#include "../tcc/DelayNode.tcc"