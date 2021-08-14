forAll(fluidRegions, i)
{
    kappaCellIn.rmap(thermoFluid[i].kappa(),fluidCellMap[i]);
    rhoCellIn.rmap(thermoFluid[i].rho(),fluidCellMap[i]);
    CpCellIn.rmap(thermoFluid[i].Cp(),fluidCellMap[i]);
    KCellIn.rmap(KFluid[i],fluidCellMap[i]);
    UgCellIn.rmap(UgFluid[i],fluidCellMap[i]);

    rhoPhiCellIn.rmap
    (
        linearInterpolate(thermoFluid[i].rho())
      * phiFluid[i].internalField()
      * fluidInternalFaceMask[i],
        fluidInternalFaceMap[i]
    );

    rhoCpPhiCellIn.rmap
    (
        linearInterpolate(thermoFluid[i].rho())
      * linearInterpolate(thermoFluid[i].Cp())
      * phiFluid[i].internalField()
      * fluidInternalFaceMask[i],
        fluidInternalFaceMap[i]
    );

    forAll(fluidRegions[i].boundary(), patchI)
    {
        const fvPatch& patch = fluidRegions[i].boundary()[patchI];
        const label patchJ = fluidPatchesMap[i][patchI];

        if(patchJ != -1 && patch.type() != "empty")
        {
             const scalarField maskJ = fluidPatchMask[i][patchI];

             const fvPatch& patch = fluidRegions[i].boundary()[patchI];
             const fvPatchField<scalar>& prho = patch.lookupPatchField<volScalarField, scalar>("rho");
             const fvPatchField<scalar>& pCp = patch.lookupPatchField<volScalarField, scalar>("Cp");
             const fvPatchField<scalar>& pK = patch.lookupPatchField<volScalarField, scalar>("K");
             const fvPatchField<scalar>& pUg = patch.lookupPatchField<volScalarField, scalar>("Ug");

             kappaCell.boundaryField()[patchJ] = thermoFluid[i].kappa(patchI);
             rhoCell.boundaryField()[patchJ] = thermoFluid[i].rho(patchI);
             CpCell.boundaryField()[patchJ] = thermoFluid[i].Cp(TCell, thermoFluid[i].p(), patchI);

             KCell.boundaryField()[patchJ] = pK * maskJ;
             UgCell.boundaryField()[patchJ] = pUg * maskJ;
             rhoPhiCell.boundaryField()[patchJ] = prho * phiFluid[i].boundaryField()[patchI] * maskJ;
             rhoCpPhiCell.boundaryField()[patchJ] = prho * pCp * phiFluid[i].boundaryField()[patchI] * maskJ;
        }
    }
}
