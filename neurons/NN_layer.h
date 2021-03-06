#pragma once
#include "Matrix.h"

namespace neurons
{
    class NN_layer_op;

    class NN_layer
    {
    protected:

        mutable std::vector<std::shared_ptr<NN_layer_op>> m_ops;

    public:
        NN_layer();

        NN_layer(lint threads);

        NN_layer(const NN_layer & other);

        NN_layer(NN_layer && other);

        NN_layer & operator = (const NN_layer & other);

        NN_layer & operator = (NN_layer && other);

        std::vector<std::shared_ptr<NN_layer_op>>& operation_instances() const;

        virtual double commit_training();

        virtual double commit_testing();

        virtual Shape output_shape() const = 0;
    };

    class NN_layer_op
    {
    protected:

        // loss calculated in the training
        double m_loss;

    public:
        NN_layer_op();

        NN_layer_op(const NN_layer_op & other);

        NN_layer_op(NN_layer_op && other);

        NN_layer_op & operator = (const NN_layer_op & other);

        NN_layer_op & operator = (NN_layer_op && other);

    public:

        //--------------------------------------------
        // Forward propagation
        //--------------------------------------------

        virtual Matrix forward_propagate(const Matrix &input) = 0;

        virtual Matrix forward_propagate(const Matrix &input, const Matrix &target) = 0;

        //--------------------------------------------
        // Backward propagation
        //--------------------------------------------

        virtual Matrix backward_propagate(double l_rate, const Matrix & E_to_y_diff) = 0;

        virtual Matrix backward_propagate(double l_rate) = 0;

        
        //--------------------------------------------
        // Forward propagation via batch learning
        //--------------------------------------------

        virtual std::vector<Matrix> batch_forward_propagate(const std::vector<Matrix> & inputs) = 0;

        virtual std::vector<Matrix> batch_forward_propagate(
            const std::vector<Matrix> & inputs, const std::vector<Matrix> & targets) = 0;

        //--------------------------------------------
        // Backward propagation via batch learning
        //--------------------------------------------

        virtual std::vector<Matrix> batch_backward_propagate(double l_rate, const std::vector<Matrix> & E_to_y_diffs) = 0;

        virtual std::vector<Matrix> batch_backward_propagate(double l_rate) = 0;

        virtual Shape output_shape() const = 0;

        double get_loss() const;

        void clear_loss();
    };
}

