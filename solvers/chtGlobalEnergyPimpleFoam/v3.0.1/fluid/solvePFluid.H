fvMesh& mesh = fluidRegions[i];

rhoThermo& thermo = thermoFluid[i];
thermo.validate(args.executable(), "h", "e");

volScalarField& rho = rhoFluid[i];
volVectorField& U = UFluid[i];
surfaceScalarField& phi = phiFluid[i];
const volScalarField& rAU = rAUFluid[i];
const volVectorField& HbyA = HbyAFluid[i];

compressible::turbulenceModel& turb = turbulence[i];
volScalarField& K = KFluid[i];
volScalarField& dpdt = dpdtFluid[i];
volScalarField& p = thermo.p();
const volScalarField& psi = thermo.psi();

volScalarField& p_rgh = p_rghFluid[i];

const volScalarField& gh = ghFluid[i];
const surfaceScalarField& ghf = ghfFluid[i];

//    radiation::radiationModel& rad = radiation[i];

IOMRFZoneList& MRF = MRFfluid[i];
fv::IOoptionList& fvOptions = fluidFvOptions[i];

const dimensionedScalar initialMass
(
    "initialMass",
    dimMass,
    initialMassFluid[i]
);

const bool frozenFlow = frozenFlowFluid[i];
const dictionary& pimple = mesh.solutionDict().subDict("PIMPLE");
const int nCorr = pimple.lookupOrDefault<int>("nCorrectors", 1);
const int nNonOrthCorr = pimple.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);

if (!frozenFlow)
{
    // --- PISO loop
    for (int corr=0; corr<nCorr; corr++)
    {
        #include "pEqn.H"
    }

    turb.correct();

    rho = thermo.rho();
}

if (finalIter)
{
    mesh.data::remove("finalIteration");
}
