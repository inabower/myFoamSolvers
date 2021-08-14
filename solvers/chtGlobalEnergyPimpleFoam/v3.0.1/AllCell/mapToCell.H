{
    // Map to cell.  In practice, fields will come from
    // components but currently they are constant

    scalarField& rhoCellIn = rhoCell;
    rhoCellIn = 0.0;

    scalarField& CpCellIn = CpCell;
    CpCellIn = 0.0;

    scalarField& rhoPhiCellIn = rhoPhiCell;
    rhoPhiCellIn = 0.0;

    scalarField& rhoCpPhiCellIn = rhoCpPhiCell;
    rhoCpPhiCellIn = 0.0;

    scalarField& kappaCellIn = kappaCell;
    kappaCellIn = 0.0;

    scalarField& KCellIn = KCell;
    KCellIn = 0.0;

    scalarField& UgCellIn = UgCell;
    UgCellIn = 0.0;

    scalarField& TsourceCellIn = TsourceCell;
    TsourceCellIn = 0.0;

    #include "mapFluidToCell.H"
    #include "mapSolidToCell.H"

    kappaCell.correctBoundaryConditions();

}

scalar rhoPhimax = phimax*Foam::gMax(rhoCell.internalField());
scalar rhoPhimin = phimin*Foam::gMax(rhoCell.internalField());

scalar rhoCpPhimax = phimax*Foam::gMax(CpCell.internalField())*Foam::gMax(rhoCell.internalField());
scalar rhoCpPhimin = phimin*Foam::gMax(CpCell.internalField())*Foam::gMax(rhoCell.internalField());

scalar Kmax = 0.5*Umax*Umax;

rhoPhiCell.max(rhoPhimin);
rhoPhiCell.min(rhoPhimax);

rhoCpPhiCell.max(rhoCpPhimin);
rhoCpPhiCell.min(rhoCpPhimax);

KCell.min(Kmax);

const volScalarField& rho = rhoCell;
const volScalarField& Cp = CpCell;
const volScalarField& kappa = kappaCell;
const volScalarField& K = KCell;
const volScalarField& Ug = UgCell;
const surfaceScalarField& rhoPhi = rhoPhiCell;
const surfaceScalarField& rhoCpPhi = rhoCpPhiCell;
volScalarField& h = hCell;
volScalarField& T = TCell;




