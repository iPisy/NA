#pragma once

struct BoundaryCondition{
public:
    enum class Type{
        Complete,
        Natural,
        Periodic,
        Theorem3_58,
        Nothing,
        D2
    };
    Type type;
protected:
    BoundaryCondition(Type type):type(type){}
};

struct BoundaryCondition_Complete:public BoundaryCondition{
    double lv,rv;
    BoundaryCondition_Complete(double lv,double rv):BoundaryCondition(BoundaryCondition::Type::Complete),lv(lv),rv(rv){}
};

struct BoundaryCondition_Natural:public BoundaryCondition{
    BoundaryCondition_Natural():BoundaryCondition(BoundaryCondition::Type::Natural){}
};

struct BoundaryCondition_Periodic:public BoundaryCondition{
    BoundaryCondition_Periodic():BoundaryCondition(BoundaryCondition::Type::Periodic){}
};

struct BoundaryCondition_Theorem3_58:public BoundaryCondition{
    double l,r,lv,rv;
    BoundaryCondition_Theorem3_58(double l,double lv,double r,double rv):BoundaryCondition(BoundaryCondition::Type::Theorem3_58),l(l),r(r),lv(lv),rv(rv){}
};

struct BoundaryCondition_Nothing:public BoundaryCondition{
    BoundaryCondition_Nothing():BoundaryCondition(BoundaryCondition::Type::Nothing){}
};

struct BoundaryCondition_D2:public BoundaryCondition{
    double l,r;
    BoundaryCondition_D2(double l,double r):BoundaryCondition(BoundaryCondition::Type::D2),l(l),r(r){}
};