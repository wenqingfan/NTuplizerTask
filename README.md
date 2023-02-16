# NTuplizerTask
Example codes to test code before running on ALICE train system (Kudo to Preeti Dhankher who prepared this example)

**RunTaskNTJ.C**: This is the main file which pulls the committed task and relevant code on the github and submits the job.
#3-8 mentions the jobs mode of running and the output directory
#61-67 mentions the grid software version settings. e.g Aliroot version, you need to change this whenever we will be pushing code to github. 
#72-77 is related to data that you want to run on. It has the file AddGoodRuns which contains the list of goodruns of the dataset. Then the path of the dataset on the grid.
#161 mentions the argument settings of the task. 

**AddGoodRuns.C**: This file contains the good run list of the dataset. You can add here both data and MC runlist.

**fileAOD.txt**: This file contains the path of the AOD file present locally for the local test. You need to download a AliAOD.root file from the grid at this path to test your code locally on your lxplus account or system. 
