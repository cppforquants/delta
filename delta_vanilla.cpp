#include <cmath>
#include <iostream>

// Cumulative normal distribution function
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

double black_scholes_delta(
    bool is_call,
    double S,     // Spot
    double K,     // Strike
    double T,     // Time to maturity
    double r,     // Risk-free rate
    double sigma  // Volatility
) {
    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
                / (sigma * std::sqrt(T));

    if (is_call) {
        return norm_cdf(d1);
    } else {
        return norm_cdf(d1) - 1.0;
    }
}

int main() {
    double S = 100.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;

    double delta_call = black_scholes_delta(true, S, K, T, r, sigma);
    double delta_put  = black_scholes_delta(false, S, K, T, r, sigma);

    std::cout << "Call Delta: " << delta_call << std::endl;
    std::cout << "Put Delta: "  << delta_put  << std::endl;
    return 0;
}