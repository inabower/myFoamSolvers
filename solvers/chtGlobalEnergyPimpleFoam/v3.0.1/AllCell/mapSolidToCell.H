forAll(solidRegions, i)
{
    rhoCellIn.rmap(thermos[i].rho(), solidCellMap[i]);
    CpCellIn.rmap(thermos[i].Cp(), solidCellMap[i]);
    kappaCellIn.rmap(thermos[i].kappa(), solidCellMap[i]);

    forAll(solidRegions[i].boundary(), patchI)
    {
        const fvPatch& patch = solidRegions[i].boundary()[patchI];
        const label patchJ = solidPatchesMap[i][patchI];

        if(patchJ != -1 && patch.type() != "empty")
        {
            rhoCell.boundaryField()[patchJ] = thermos[i].rho(patchI);
            CpCell.boundaryField()[patchJ] = thermos[i].Cp(TCell, pCell, patchI);
            kappaCell.boundaryField()[patchJ] = thermos[i].kappa(patchI);
        }
    }
}
