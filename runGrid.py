import os
import numpy as np
from ROOT import *

def runGrid(cwd,dataCard,TaskName,rInit,rMin,rMax,dryRun): 
    quantiles =[0.025,0.16,0.5,0.84,0.975]
    setPam    ="--setPhysicsModelParameters r=%s --setPhysicsModelParameterRanges r=%s,%s"%(rInit,rMin,rMax)
    batchmode = "--job-mode lxbatch --task-name %s_Obs --sub-opts='-q 8nh'"%TaskName
    nToy = 5000
    cmd = "python %s/combineTool.py -M HybridNew %s -n %s_Obs --testStat=LHC --frequentist -T %s --fork 10 --plot cls_%s.pdf %s %s"%(cwd,dataCard,TaskName,nToy,TaskName,setPam,batchmode)
    print cmd
    if not dryRun:
        os.system(cmd)
    for q in quantiles:
        if q==0.025:    nToy = 10000
        if q==0.16:     nToy = 8000
        if q==0.5:      nToy = 5000
        if q==0.84:     nToy = 5000
        if q==0.975:    nToy = 5000
        batchmode = "--job-mode lxbatch --task-name %s_%s --sub-opts='-q 8nh'"%(TaskName,q)
        cmd = "python %s/combineTool.py -M HybridNew %s --testStat=LHC --frequentist -T %s --expectedFromGrid=%s --fork 10 --plot cls_%s.pdf %s %s"%(cwd,dataCard,nToy,q,TaskName,setPam,batchmode)
        print cmd
        if not dryRun:
            os.system(cmd)

def GetAsymResult(cwd,i,ST):
    AsymDir = "%s/AsymptoticLimits/AsymLimit_mult%s"%(cwd,i)
    if os.path.exists(AsymDir):
        AsymRoots = os.listdir(AsymDir)
        for rootFile in AsymRoots:
            if ( "%s"%ST in rootFile ) and (".root" in rootFile):
                print rootFile
                f = TFile("%s/%s"%(AsymDir,rootFile))
                t = f.Get("limit")
                limits = []
                obs    = 0
                for i in range(0,int(t.GetEntries())):
                    t.GetEntry(i)
                    limits.append(t.limit)
                    if (t.quantileExpected==-1): obs = t.limit
                #print "Found these limits from %s "%rootFile,limits
                return (obs,min(limits)*2,max(limits)*2)
    else:
        "Cannot find AsymptoticLimit directory, it should be %s"%AsymDir
               
                
        
multi = [6]
STmin,STmax = [3000,7000]
STstep = 500
dataCards = []
cwd = os.getcwd()

print cwd
if not os.path.exists("FullCLsLimits"):
    os.system("mkdir FullCLsLimits")
for i in multi:
    workdir = "FullCLsLimits/FullCLsLimit_mult%s"%i
    if not os.path.exists(workdir): 
        os.system("mkdir %s"%workdir)
    os.chdir(workdir)
    for ST in np.arange(STmin,STmax+STstep,STstep):
        print "============================================="
        Obs,rMin,rMax = GetAsymResult(cwd,i,ST)
        STdir = "%s/%s/ST_%s"%(cwd,workdir,ST)
        if not os.path.exists(STdir): 
            os.system("mkdir %s"%STdir)
        os.chdir("%s/%s/ST_%s"%(cwd,workdir,ST))
        dataCardpath = "%s/DataCards/CardFiles_Mul%i/realistic-counting-experiment_ST%s_BHMI.txt"%(cwd,i,ST)
        TaskName     = "N%i_%s"%(i,ST)
        dataCards.append(dataCardpath)
        print i, ST, dataCardpath
        runGrid(cwd,dataCardpath,TaskName,Obs,rMin,rMax,False)
        print "============================================="
