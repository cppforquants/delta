#include <ql/quantlib.hpp>
#include <iostream>

using namespace QuantLib;

int main() {
    Calendar calendar = TARGET();
    Date today(23, June, 2025);
    Settings::instance().evaluationDate() = today;

    // Common option parameters
    Real underlying = 100.0;
    Real strike = 100.0;
    Spread dividendYield = 0.0;
    Rate riskFreeRate = 0.05;
    Volatility volatility = 0.20;
    Date maturity = today + Period(1, Years);
    DayCounter dayCounter = Actual365Fixed();

    // Market data handles
    Handle<Quote> underlyingH(boost::shared_ptr<Quote>(new SimpleQuote(underlying)));
    Handle<YieldTermStructure> flatDividendTS(boost::shared_ptr<YieldTermStructure>(
        new FlatForward(today, dividendYield, dayCounter)));
    Handle<YieldTermStructure> flatRiskFreeTS(boost::shared_ptr<YieldTermStructure>(
        new FlatForward(today, riskFreeRate, dayCounter)));
    Handle<BlackVolTermStructure> flatVolTS(boost::shared_ptr<BlackVolTermStructure>(
        new BlackConstantVol(today, calendar, volatility, dayCounter)));

    boost::shared_ptr<BlackScholesMertonProcess> bsmProcess(
        new BlackScholesMertonProcess(underlyingH, flatDividendTS, flatRiskFreeTS, flatVolTS));

    // Loop over Call and Put options
    for (auto type : {Option::Call, Option::Put}) {
        std::string typeStr = (type == Option::Call ? "Call" : "Put");

        boost::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
        boost::shared_ptr<Exercise> exercise(new EuropeanExercise(maturity));
        VanillaOption option(payoff, exercise);

        option.setPricingEngine(boost::shared_ptr<PricingEngine>(
            new AnalyticEuropeanEngine(bsmProcess)));

        std::cout << typeStr << " Delta: " << option.delta() << std::endl;
    }

    return 0;
}
