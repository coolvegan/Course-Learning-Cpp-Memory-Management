int i = 0;
for(; i < 20; ++i) {
    doThing(someVar[i]);
}



int i = 0;
for(; i < 20; ++i) {
    if (someTest(i)) {
        ++I;
    }
    doThing(someVar[i]);
}

function doWork(int i) {
   // .. some work
}

vector<int> someInts;
fillVector(vector);
for_each(someInts.begin(),someInts.end(),doWork);


const CDatum *cpDatum;

while ( NULL != (cpDatum = getNextDatum())) {
    ServicePerformer sp;
    sp.performService(cpDatum);
    .
    .
    .
}


Should be

const CDatum *cpDatum;
ServicePerformer sp;

while ( NULL != (cpDatum = getNextDatum()) ) {
    sp.performService(cpDatum);
    .
    .
    .
}