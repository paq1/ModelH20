//
// Created by evamo on 25/04/2020.
//

#ifndef MODELH2O_VIEWER_HPP
#define MODELH2O_VIEWER_HPP

#include <vector>
#include "type_atomiques.hpp"

class Matrix_4x4 {
private:
    std::vector<std::vector<double>> m_grid;
public:
    Matrix_4x4();
    virtual ~Matrix_4x4();
    std::vector<double> Multiply_vector_matrix(const std::vector<double> &v_in) const;
    std::vector<std::vector<double>>& get_modif_grid();
};

class Model_mol{
private:
    std::vector<double> m_vec_O,
                        m_vec_H1,
                        m_vec_H2;

public:
    Model_mol(const molecule& mol);
    virtual ~Model_mol();
    const std::vector<double>& get_O() const;
    const std::vector<double>& get_H1() const;
    const std::vector<double>& get_H2() const;
};

class View_mol{
private:
    std::vector<double> m_vue_O,
                        m_vue_H1,
                        m_vue_H2;
public:
    View_mol(const Model_mol& model,
             const Matrix_4x4& projection_matrix);
    virtual ~View_mol();
    std::vector<double>& get_vue_O();
    std::vector<double>& get_vue_H1();
    std::vector<double>& get_vue_H2();

    const std::vector<double>& get_vue_O() const { return m_vue_O; }
    const std::vector<double>& get_vue_H1() const { return m_vue_H1; }
    const std::vector<double>& get_vue_H2() const { return m_vue_H2; }
};


#endif //MODELH2O_VIEWER_HPP
