/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2015 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    chtMultiRegionFoam

Description
    Combination of heatConductionFoam and buoyantFoam for conjugate heat
    transfer between solid regions and fluid regions. Both regions include
    the fvOptions framework.

    It handles secondary fluid or solid circuits which can be coupled
    thermally with the main fluid region. i.e radiators, etc.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "rhoThermo.H"
#include "turbulentFluidThermoModel.H"
#include "fixedGradientFvPatchFields.H"
#include "regionProperties.H"
#include "compressibleCourantNo.H"
#include "cellRegionDiffNo.H"
#include "solidThermo.H"
#include "radiationModel.H"
#include "fvIOoptionList.H"
#include "coordinateSystem.H"
#include "fixedFluxPressureFvPatchScalarField.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"

    regionProperties rp(runTime);

    #include "createCellMeshes.H"
    #include "createFluidMeshes.H"
    #include "createSolidMeshes.H"

    bool firstTime = true;

        //pimple loop

        #include "createCellFields.H"
        #include "createFluidFields.H"
        #include "createSolidFields.H"

        #include "initContinuityErrs.H"

        #include "createTimeControls.H"
        #include "readCellTimeControls.H"
        #include "readTimeControls.H"

        #include "compressibleMultiRegionThermoCourantNo.H"
        #include "cellRegionDiffusionNo.H"
        #include "setInitialMultiRegionDeltaT.H"

        while (runTime.run())
        {
            #include "createTimeControls.H"
            #include "readTimeControls.H"
            #include "readCellTimeControls.H"
            #include "readPIMPLEControls.H"

            #include "compressibleMultiRegionThermoCourantNo.H"
            #include "cellRegionDiffusionNo.H"
            #include "setMultiRegionDeltaT.H"

            runTime++;

            Info<< "Time = " << runTime.timeName() << nl << endl;

            if (nOuterCorr != 1)
            {
                forAll(fluidRegions, i)
                {
                    p_rghFluid[i].storePrevIter();
                    rhoFluid[i].storePrevIter();
                }
            }

            // --- PIMPLE loop
            for (int oCorr=0; oCorr<nOuterCorr; oCorr++)
            {
                bool finalIter = oCorr == nOuterCorr-1;

                forAll(fluidRegions, i)
                {
                    #include "solveUFluid.H" // At first you calculate vitesse if fluid is not frozenflow
                }

                if(runTime.value() >= Tstart) // you can choose the time to start the calculation of energy
                {
                    #include "mapToCell.H"
                    #include "solveTCell.H"
                    #include "mapFromCell.H"
                }

                forAll(fluidRegions, i)
                {
                    #include "solvePFluid.H" // At last you calculate pressure if fluid is not frozenflow
                }
            }

            if(firstTime)
            {
                firstTime = false;
            }

            runTime.write();

            Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
                << "  ClockTime = " << runTime.elapsedClockTime() << " s"
                << nl << endl;
        }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
