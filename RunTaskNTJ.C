//Run this file with command: aliroot RunTaskNTJ.C

{   const char* launch = "grid"; //local or grid
    const char*  mode = "full"; // test or full
    Int_t cyclenumber = 1;
    Bool_t debug = kTRUE;
    const char* workDir = "NTuplesTest_2Config"; //grid working directory
    const char* outputDir = "output";
    TString testfileslistWithPlugin = "./filesAOD.txt"; //file path to test locally. require a AOD file at this path
    Int_t ttl = 50000;
    Int_t noffiles = 7;
    Int_t runcycle[] = {0,25};
    
    // load essential prerequistes libraries
    LoadLibraries();
    
    TString mkl_filename = "";
    TString efp7_filename = "";
   
    
    if (!gSystem->AccessPathName("libmkl_core_so")) {
        mkl_filename = "libiomp5_so libmkl_avx2_so libmkl_avx_so "
            "libmkl_core_so libmkl_def_so libmkl_intel_lp64_so "
            "libmkl_intel_thread_so libmkl_vml_avx2_so "
            "libmkl_vml_avx_so libmkl_vml_def_so";
    }
    if (!gSystem->AccessPathName("efp7.cc")) {
        efp7_filename =
            "blasdrv.h efp7.cc einstein_sum.h fill_efp7.h";
    }
  
    
    
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/include");
    
    AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
    alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/STEER -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/EMCAL -I$ALICE_ROOT/ANALYSIS -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -IALICE_ROOT/PWG/EMCAL -I$ALICE_ROOT/macros -I$ALICE_ROOT/PYTHIA6 -I$ALICE_ROOT/FASTSIM -I$ALICE_ROOT/EVGEN -I$ALICE_ROOT/LHAPDF -I$ALICE_PHYSICS/PWGHF -I$ALICE_PHYSICS/PWGHF/hfe -I$ALICE_PHYSICS/OADB -I$ALICE_PHYSICS/PWGHF/base -I$ALICE_PHYSICS/include -I$ALICE_PHYSICS/PWGJE -I$ALICE_PHYSICS/JETAN -I$ALICE_PHYSICS/JETAN/FASTJETAN -I$FASTJET/include -g");
    
    alienHandler->SetAdditionalLibs("libCDB.so libSTEER.so libGui.so libMinuit.so libXMLParser.so libRAWDatabase.so libRAWDatarec.so libSTEERBase.so");
    

//-----------------Grid settings-----------------
    alienHandler->SetRunMode(mode);
    alienHandler->SetUser("pdhankhe");
    alienHandler->SetAPIVersion("V1.1x");
    alienHandler->SetAliPhysicsVersion("vAN-20210527_ROOT6-1"); //aliroot version to run on grid
    alienHandler->SetFileForTestMode(testfileslistWithPlugin.Data());
    alienHandler->SetNtestFiles(1); // if "test mode"
    
    
    
//________________________Set data search pattern for DATA and MC
  
    gROOT->LoadMacro("./AddGoodRuns.C"); //list of good run numbers
    alienHandler->SetGridDataDir("/alice/data/2015/LHC15o"); // specify LHC period
    alienHandler->SetDataPattern("/pass1/AOD194/*/AliAOD.root"); // specify reco pass and AOD set
    Int_t totruns=0;
    totruns += AddGoodRuns(alienHandler,"LHC15o_Gir",""); // specify the list from the AddGoodRuns file to be run on the grid
 //-------------------------------------------------------------------------------------
    
    alienHandler->SetGridWorkingDir(workDir);
    alienHandler->SetGridOutputDir(outputDir);
    alienHandler->SetDefaultOutputs(kTRUE);
    alienHandler->SetTTL(ttl); //10000
    alienHandler->SetInputFormat("xml-single");
    alienHandler->SetJDLName("GAMC.jdl");
    alienHandler->SetSplitMode("se");
    alienHandler->SetMasterResubmitThreshold(10);
    alienHandler->SetMergeExcludes("EventStat_temp.root");
    alienHandler->SetOutputToRunNo(kTRUE);
    alienHandler->SetKeepLogs(kTRUE);
    alienHandler->SetMaxMergeStages(4);
    alienHandler->SetMergeViaJDL(kTRUE);
    
    if (!alienHandler) return;
    
    // Use AliRoot includes to compile our task
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/EMCAL");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGGA/");
    gROOT->ProcessLine(".include $ALICE_ROOT/ANALYSIS/");
    gROOT->ProcessLine(".include $PWD/.");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGHF");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/PWGHF/hfe");
    gROOT->ProcessLine(".include $ALICE_PHYSICS/JETAN");
    gROOT->ProcessLine(".include $FASTJET/include");
    
    
    
    alienHandler->SetAdditionalLibs("emcal_correction.yaml EMCALlocal2master.root geometry_2015.root libCDB.so libSTEER.so libGui.so libMinuit.so libXMLParser.so libRAWDatabase.so libRAWDatarec.so libSTEERBase.so "
                                    "libpythia6.so libAliPythia6.so "
                                    "libfastjet.so libsiscone.so "
                                    "libsiscone_spherical.so libfastjetplugins.so "
                                    "libfastjetcontribfragile.so " +
                                    mkl_filename + " " + efp7_filename + " "
                                    );
    
    gSystem->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/STEER -I$ALICE_ROOT/STEER/STEER -I$ALICE_ROOT/EMCAL -I$ALICE_ROOT/ANALYSIS -I$ALICE_ROOT/STEER/STEERBase -I$ALICE_ROOT/STEER/ESD -I$ALICE_ROOT/STEER/AOD -I$ALICE_ROOT/ITS -I$ALICE_ROOT/TPC -IALICE_ROOT/PWG/EMCAL -I$ALICE_ROOT/macros -I$ALICE_ROOT/PYTHIA6 -I$ALICE_ROOT/FASTSIM -I$ALICE_ROOT/EVGEN -I$ALICE_ROOT/LHAPDF -I$ALICE_PHYSICS/PWGHF -I$ALICE_PHYSICS/PWGHF/hfe -I$ALICE_PHYSICS/OADB -I$ALICE_PHYSICS/PWGHF/base -I$ALICE_PHYSICS/include -I$ALICE_PHYSICS/PWGJE -I$ALICE_PHYSICS/JETAN -I$ALICE_PHYSICS/JETAN/FASTJETAN -I$ALICE_PHYSICS/PWGCF/Correlations/Base  -I$ALICE_PHYSICS/PWGCF/Correlations/DPhi -I$ALICE_PHYSICS/PWG/Tools -I$FASTJET/include -g");
    
    AliAnalysisManager *mgr = new AliAnalysisManager("ElectronEffiMC");
    mgr->SetGridHandler(alienHandler);
    
    AliAODInputHandler* aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);
    
  
    gROOT->LoadMacro("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/AddTaskEmcalCorrectionTask.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWGPP/PilotTrain/AddTaskCDBconnect.C");
    gROOT->LoadMacro("$ALICE_PHYSICS/PWGGA/NtuplizerTask/GJNtuples/macros/AddAliAnalysisTaskNTGJ.C");
    
    
    Bool_t isMC=false; // kTRUE in case of MC
    Bool_t is_embed=false; // kTRUE in case of MC
   
    
    //------Task required before the ntupliser task-----------------
  
    //AddTaskPhysicsSelection(isMC,true);
    
    AliTaskCDBconnect *taskCDB = AddTaskCDBconnect();
    taskCDB->SetFallBackToRaw(kTRUE);
    
    AliMultSelectionTask *mult_selection_task = AddTaskMultSelection(false);
    
    
    AliEmcalCorrectionTask * correctionTask = AddTaskEmcalCorrectionTask();
    correctionTask->SelectCollisionCandidates(AliVEvent::kAny);
    correctionTask->SetUserConfigurationFilename("emcal_correction.yaml");
    correctionTask->Initialize();
    //----------------------------------------------------------------
    
    //------------Ntupliser Task settings-----------------
    AddAliAnalysisTaskNTGJ("Ntuples_JE_DiJet","emcal_correction.yaml",14,false,false,true,"geometry_2015.root","EMCALlocal2master.root",false,-1.7976931348623157e+308,-1.7976931348623157e+308,-1.7976931348623157e+308,20.0,10.0,-1.7976931348623157e+308,-1.7976931348623157e+308,-2147483648,-1.7976931348623157e+308,-1.7976931348623157e+308,0,"lhc15o", false,false,"","");
    //----------------------------------------------------------------

   if (!mgr->InitAnalysis())
        return;
    
    mgr->PrintStatus();
    mgr->StartAnalysis(launch);
}

void LoadLibraries()
{
    gSystem->Load("libCore");
    gSystem->Load("libTree");
    gSystem->Load("libGeom");
    gSystem->Load("libVMC");
    gSystem->Load("libXMLIO");
    gSystem->Load("libPhysics");
    gSystem->Load("libXMLParser");
    gSystem->Load("libProof");
    gSystem->Load("libMinuit");
    gSystem->Load("libSTEERBase");
    gSystem->Load("libSTEER");
    gSystem->Load("libCDB");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libRAWDatarec");
    gSystem->Load("libESD");
    gSystem->Load("libAOD");
    gSystem->Load("libOADB");
    gSystem->Load("libANALYSIS");
    gSystem->Load("libANALYSISalice");
    gSystem->Load("libGui");
    gSystem->Load("libEVGEN");
    gSystem->Load("libCDB");
    gSystem->Load("libRAWDatabase");
    gSystem->Load("libSTEER");
    gSystem->Load("libTPCbase");
    gSystem->Load("libTOFbase");
    gSystem->Load("libTOFrec");
    gSystem->Load("libTRDbase");
    gSystem->Load("libVZERObase");
    gSystem->Load("libVZEROrec");
    gSystem->Load("libT0base");
    gSystem->Load("libT0rec");
    gSystem->Load("libCORRFW");
    gSystem->Load("libTENDER");
    gSystem->Load("libTENDERSupplies");
    
    gSystem->Load("libEMCALbase.so");
    gSystem->Load("libEMCALUtils.so");
    gSystem->Load("libEMCALrec.so");
    gSystem->Load("libPWGCaloTrackCorrBase.so");
    gSystem->Load("libPWGCFCorrelationsDPhi.so");
    gSystem->Load("libPWGCFCorrelationsBase.so");
    gSystem->Load("libPWGTools.so");
    
    gSystem->Load("libfastjet");
    gSystem->Load("libsiscone");
    gSystem->Load("libsiscone_spherical");
    gSystem->Load("libfastjetplugins");
    gSystem->Load("libfastjetcontribfragile");
    
    gSystem->Load("libEMCALUtils");
    gSystem->Load("libPWGPPEMCAL");
}





