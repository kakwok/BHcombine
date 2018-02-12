import os
import numpy as np

def runAsym(dataCard,TaskName,rInit,rMin,rMax,dryRun): 
    #cmd = "python combineTool.py -M Asymptotic %s --setPhysicsModelParameters r=%s --setPhysicsModelParameterRanges r=%s,%s"%(dataCard,rInit,rMin,rMax)
    cmd = "combine -M Asymptotic %s -n %s --saveWorkspace --setPhysicsModelParameters r=%s --setPhysicsModelParameterRanges r=%s,%s"%(dataCard,TaskName,rInit,rMin,rMax)
    print cmd
    if not dryRun:
        os.system(cmd)


multi = [6]
STmin,STmax = [3000,7000]
STstep = 500
dataCards = []
cwd = os.getcwd()

print cwd
if not os.path.exists("AsymptoticLimits"):
    os.system("mkdir AsymptoticLimits")
for i in multi:
    workdir = "AsymptoticLimits/AsymLimit_mult%s"%i
    if not os.path.exists(workdir): 
        os.system("mkdir %s"%workdir)
    os.chdir(workdir)
    for ST in np.arange(STmin,STmax+STstep,STstep):
        dataCardpath = "%s/DataCards/CardFiles_Mul%i/realistic-counting-experiment_ST%s_BHMI.txt"%(cwd,i,ST)
        TaskName     = "N%i_%s"%(i,ST)
        dataCards.append(dataCardpath)
        print i, ST, dataCardpath
        runAsym(dataCardpath,TaskName,0.1,0,500,False)
        
