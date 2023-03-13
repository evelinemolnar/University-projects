//
// Created by Eveline Molnar on 21.04.2022.
//
#include "Validator.h"
#include <sstream>

void MedValidator::validate(const Medicament& p) {
    vector<string> msgs;
    if (p.getPret() < 0 || p.getPret()>10000) msgs.push_back("Pret incorect!!!");
    if (p.getDenumire().size() == 0 || p.getDenumire().size() > 100) msgs.push_back("Denumire incorecta!!!");
    if (p.getProducator().size() == 0 || p.getProducator().size() > 100) msgs.push_back("Producator incorect!!!");
    if (p.getSubstanta().size() == 0 || p.getSubstanta().size() > 100) msgs.push_back("Substanta incorect!!!");
    if (msgs.size() > 0) {
        throw ValidateException(msgs);
    }
}


ostream& operator<<(ostream& out, const ValidateException& ex) {
    for (const auto& msg : ex.msgs) {
        out << msg<<" ";
    }
    return out;
}

void testValidator() {
    MedValidator v;
    Medicament p{ "",-1,"","" };
    try {
        v.validate(p);
    }
    catch (const ValidateException & ex) {
        std::stringstream sout;
        sout << ex;
        auto mesaj = sout.str();
        assert(mesaj.find("incorect") >= 0);
        assert(mesaj.find("incorecta") >= 0);
    }

}
