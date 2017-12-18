{

gSystem->AddIncludePath("-I$ROOFITSYS/include");
gROOT->GetInterpreter()->AddIncludePath("$ROOFITSYS/include");
gSystem->SetIncludePath("-I$ROOFITSYS/include");
gSystem->Load("$ROOFITSYS/lib/libRooFit.so") ;
gSystem->Load("$ROOFITSYS/lib/libRooFitCore.so") ;
gSystem->Load("$ROOFITSYS/lib/libRooStats.so") ;
gROOT->ProcessLine(" .L RooDCBShape/RooDCBShape.cxx");
//gSystem->Load(".L RooDCBShape/RooDCBShape.cxx");

}

