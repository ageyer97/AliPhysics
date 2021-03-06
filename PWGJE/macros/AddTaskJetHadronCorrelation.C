AliAnalysisTaskJetHadronCorrelation *AddTaskJetHadronCorrelation(Char_t *jf="ANTIKT",Float_t radius=0.4,UInt_t filter=256,Int_t backM=0,Float_t tPtcut=0.15,Int_t skipCone=0,Bool_t IsMC=true,Float_t JetEScale=1.,Float_t TrackEScale=1.)
{

   // Creates a JetQA task, configures it and adds it to the analysis manager.
   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
      ::Error("AddTaskJetHadronCorrelation", "No analysis manager to connect to.");
      return NULL;
   }

   // Check the analysis type using the event handlers connected to the analysis manager.
   //==============================================================================
   if (!mgr->GetInputEventHandler()) {
      ::Error("AddTaskJetHadronCorrelation", "This task requires an input event handler");
      return NULL;
   }

   // Create the task and configure it.
   //===========================================================================

   AliAnalysisTaskJetHadronCorrelation *jethadron = new AliAnalysisTaskJetHadronCorrelation("TaskJetHadronCorrelation");
   jethadron->SetDebugLevel(3);
	 jethadron->SetAlgorithm(jf);
	 jethadron->SetRadius(radius);
	 jethadron->SetFilterMask(filter);
	 jethadron->SetBackSubMode(backM);
	 jethadron->SetTrackPtCut(tPtcut);
	 jethadron->SetSkipCone(skipCone);
	 jethadron->SetMC(IsMC);
	 jethadron->SetJetEScale(JetEScale);
	 jethadron->SetTrackEScale(TrackEScale);
	 mgr->AddTask(jethadron); 

	 TString cAdd = "";
	 cAdd += Form("%02d_"           ,(int)((radius+0.01)*10.));
	 cAdd += Form("B%d"             ,(int)backM);
	 cAdd += Form("_Filter%05d"     ,filter);
	 cAdd += Form("_Cut%05d"        ,(int)(1000.*tPtcut));
	 cAdd += Form("_Skip%02d"       ,skipCone);
	 cAdd += Form("_JetEScale%03d"  ,(int)(JetEScale*100.));
	 cAdd += Form("_TrackEScale%03d",(int)(TrackEScale*100.));
	 TString Branch;
	 if(IsMC)Branch = Form("MC_clustersAOD_%s%s",jf,cAdd.Data());
	 else    Branch = Form("Data_clustersAOD_%s%s",jf,cAdd.Data());

   AliAnalysisDataContainer *cout_JHC = mgr->CreateContainer(Form("JHC_%s%s",jf,cAdd.Data()), TList::Class(),AliAnalysisManager::kOutputContainer,Form("%s:PWGJE_JHC_%s",AliAnalysisManager::GetCommonFileName(),Branch.Data()));

   // Create ONLY the output containers for the data produced by the task.
   // Get and connect other common input/output containers via the manager as below
   //==============================================================================

   mgr->ConnectInput (jethadron,0, mgr->GetCommonInputContainer());  
   mgr->ConnectOutput(jethadron,0, mgr->GetCommonOutputContainer());
   mgr->ConnectOutput(jethadron,1, cout_JHC);


   return jethadron;
}
