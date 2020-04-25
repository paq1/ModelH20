//
// Created by evamo on 25/04/2020.
//

#include "viewer.hpp"

// region Matrix

Matrix_4x4::Matrix_4x4(){
    m_grid = std::vector<std::vector<double>>(4);
    for (int i = 0; i<4; i++){
        m_grid[i] = { 0.0, 0.0, 0.0, 0.0};
    }
}
/*virtual*/ Matrix_4x4::~Matrix_4x4(){}

std::vector<double> Matrix_4x4::Multiply_vector_matrix(const std::vector<double> &v_in) const{
    std::vector<double> v_out(4);
    v_out[0] = v_in[0]*m_grid[0][0] + v_in[1]*m_grid[1][0]
             + v_in[2]*m_grid[2][0] + v_in[3]*m_grid[3][0];
    v_out[1] = v_in[0]*m_grid[0][1] + v_in[1]*m_grid[1][1]
             + v_in[2]*m_grid[2][1] + v_in[3]*m_grid[3][1];
    v_out[2] = v_in[0]*m_grid[0][2] + v_in[1]*m_grid[1][2]
             + v_in[2]*m_grid[2][2] + v_in[3]*m_grid[3][2];
    v_out[3] = v_in[0]*m_grid[0][3] + v_in[1]*m_grid[1][3]
             + v_in[2]*m_grid[2][3] + v_in[3]*m_grid[3][3];
    return v_out;
}

std::vector<std::vector<double>>& Matrix_4x4::get_modif_grid(){
    return m_grid;
}

// endregion

// region Model_mol

Model_mol::Model_mol(const molecule& mol){
    m_vec_O = std::vector<double>(4);
    m_vec_O[0] = mol.atomes[0].pos.x;
    m_vec_O[1] = mol.atomes[0].pos.y;
    m_vec_O[2] = mol.atomes[0].pos.z;
    m_vec_O[3] = 1.0;

    m_vec_H1 = std::vector<double>(4);
    m_vec_H1[0] = mol.atomes[1].pos.x;
    m_vec_H1[1] = mol.atomes[1].pos.y;
    m_vec_H1[2] = mol.atomes[1].pos.z;
    m_vec_H1[3] = 1.0;

    m_vec_H2 = std::vector<double>(4);
    m_vec_H2[0] = mol.atomes[2].pos.x;
    m_vec_H2[1] = mol.atomes[2].pos.y;
    m_vec_H2[2] = mol.atomes[2].pos.z;
    m_vec_H2[3] = 1.0;
}

/*virtual*/ Model_mol::~Model_mol(){}

const std::vector<double>& Model_mol::get_O() const {
    return m_vec_O;
}
const std::vector<double>& Model_mol::get_H1() const {
    return m_vec_H1;
}
const std::vector<double>& Model_mol::get_H2() const {
    return m_vec_H2;
}

// endregion

// region View_mol

View_mol::View_mol(
        const Model_mol& model,
        const Matrix_4x4& projection_matrix
){

    std::vector<double> temp_O = projection_matrix.Multiply_vector_matrix(model.get_O());
    m_vue_O = {temp_O[0], temp_O[1]};

    std::cout << m_vue_O[0] << " " << m_vue_O[1] << std::endl;

    std::vector<double> temp_H1 = projection_matrix.Multiply_vector_matrix(model.get_H1());
    m_vue_H1 = {temp_H1[0], temp_H1[1]};

    std::cout << m_vue_H1[0] << " " << m_vue_H1[1] << std::endl;

    std::vector<double> temp_H2 = projection_matrix.Multiply_vector_matrix(model.get_H2());
    m_vue_H2 = {temp_H2[0], temp_H2[1]};

    std::cout << m_vue_H2[0] << " " << m_vue_H2[1] << std::endl;

    if (temp_O[3] != 0.0) {
        m_vue_O[0] /= temp_O[3];
        m_vue_O[1] /= temp_O[3];
    }
    if (temp_H1[3] != 0.0) {
        m_vue_H1[0] /= temp_H1[3];
        m_vue_H1[1] /= temp_H1[3];
    }
    if (temp_H2[3] != 0.0) {
        m_vue_H2[0] /= temp_H2[3];
        m_vue_H2[1] /= temp_H2[3];
    }

}
/*virtual*/ View_mol::~View_mol(){}
std::vector<double>& View_mol::get_vue_O() {
    return m_vue_O;
}
std::vector<double>& View_mol::get_vue_H1() {
    return m_vue_H1;
}
std::vector<double>& View_mol::get_vue_H2() {
    return m_vue_H2;
}

// endregion