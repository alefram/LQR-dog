#include "model.h"
#include <cmath>
#include <mujoco/mujoco.h>
#include <xtensor/xarray.hpp>
#include <xtensor/xshape.hpp>

Model::Model(const mjModel* model, mjData* data): model(model), data(data) {
    g = model->opt.gravity[2];
    // z_CoM = data->xipos[0][2]; TODO:revisar
    w = std::sqrt(g / z_CoM);
    px = 0.0; //TODO:calcular con mujoco
    py = 0.0; //TODO: calcular con mujoco
    // x_CoM = { data->xipos[0], 0.0 }; //TODO:revisar x0
    // y_CoM = { data->xipos[1], 0.0 }; //TODO: revisar el y0
}

void Model::computeA(double t, xt::xarray<double>& A) {
    double cosh_wt = std::cosh(w * t);
    double sinh_wt = std::sinh(w * t);

    A = xt::xarray<double>({{cosh_wt, sinh_wt/w}, 
                            {w * sinh_wt, cosh_wt}});
}

void Model::computeB(double t, xt::xarray<double>& B) {
    double cosh_wt = std::cosh(w * t);
    double sinh_wt = std::sinh(w * t);
    
    B = xt::xarray<double>({{1 - cosh_wt, -w * sinh_wt}});
}

void Model::step(double dt) {
    //TODO: crear implementación
}

xt::xarray<double> Model::getCoM() const {
    return { x_CoM[0], y_CoM[0] }; //TODO: check if it is correct
}


