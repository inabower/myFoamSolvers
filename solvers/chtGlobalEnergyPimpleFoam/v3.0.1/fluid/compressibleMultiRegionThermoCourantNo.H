    scalar CoNum = -GREAT;

    forAll(fluidRegions, regionI)
    {
      if(frozenFlowFluid[regionI])
      {
          CoNum = SMALL;
          Info<< "Region: " << fluidRegions[regionI].name() << " is frozenFluid" << endl;
      }
      else
      {
        CoNum = max
        (
            compressibleCourantNo
            (
                fluidRegions[regionI],
                runTime,
                rhoFluid[regionI],
                phiFluid[regionI]
            ),
            CoNum
        );
        Info<< "Region: " << fluidRegions[regionI].name() << " is not frozenFluid" << endl;
      }
    }
/*
    forAll (porousFluidRegions, porousI)
    {
        CoNum = max
        (
            compressibleCourantNo
            (
                porousFluidRegions[porousI],
                runTime,
                rhoPorous[porousI],
                phiPorous[porousI]
            ),
            CoNum
        );
    }
*/
