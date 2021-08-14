    PtrList<topoSet> sets(nRegion);

    forAll(sets, regionI)
    {
        std::ostringstream s;
        int i(regionI);
        s<<i;
        std::string stri = s.str();

        const word regionName = "region" + stri;
        const word setType = "cellSet";

        sets.set
        (
            regionI,
            topoSet::New
            (
                setType,
                mesh,
                regionName,
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            ).ptr()
        );

        const label maxN = sets[regionI][sets[regionI].size()-1];
        const label minN = sets[regionI][0];

        Info << "reading region" << stri << " set. size is " << sets[regionI].size() << "(" << minN << " to " << maxN << ")" << endl;
    }
