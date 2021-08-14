fvMesh& mesh = fluidRegions[i];

rhoThermo& thermo = thermoFluid[i];
thermo.validate(args.executable(), "h", "e");

volScalarField& rho = rhoFluid[i];
volVectorField& U = UFluid[i];
surfaceScalarField& phi = phiFluid[i];
volScalarField& Ug = UgFluid[i];
volScalarField& rAU = rAUFluid[i];
volVectorField& HbyA = HbyAFluid[i];

compressible::turbulenceModel& turb = turbulence[i];
volScalarField& K = KFluid[i];
const dimensionedVector& g = gFluid[i];

volScalarField& p_rgh = p_rghFluid[i];

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
const bool momentumPredictor = pimple.lookupOrDefault("momentumPredictor", true);

if (finalIter)
{
    mesh.data::add("finalIteration", true);
}

if (!frozenFlow)
{
    if (oCorr == 0)
    {
        #include "rhoEqn.H"
    }

    #include "UEqn.H"
}

