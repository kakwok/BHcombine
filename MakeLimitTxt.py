import os
import glob
from ROOT import *
quantiles =[0.025,0.16,0.5,0.84,0.975,"Obs"]

#multi_dirs = glob.glob("./FullCLsLimits")
multi_dirs = os.listdir("./FullCLsLimits")
print multi_dirs
for i_dir in multi_dirs:
    N = i_dir.split("/")[-1].split("_")[1].strip("mult")
    limits_txt  = open("MIlimit_N%s.txt"%N,"w")
    limits_txt.write("N ST Obs -2sig -1sig exp +1sig +2sig\n")
    ST_dirs     = os.listdir("FullCLsLimits/%s"%i_dir)
    for ST_dir in ST_dirs:
        ST = ST_dir.split("_")[1]
        limits = {}
        for q in quantiles:
            key =""
            root = glob.glob("FullCLsLimits/%s/%s/*%s*.root"%(i_dir,ST_dir,q))
            if len(root)==1: 
                f = TFile(root[0])
                t = f.Get("limit")
                t.GetEntry(0)
                if q == 0.025  : key = "-2sig"
                if q == 0.16   : key = "-1sig"
                if q == 0.5    : key = "exp"
                if q == 0.84   : key = "+1sig"
                if q == 0.975  : key = "+2sig"
                if q == "Obs"  : key = "Obs"
                limits[key]="%.4f"%t.limit 
        print "%s %s %s %s %s %s %s %s "%(N,ST,limits["Obs"],limits["-2sig"],limits['-1sig'],limits['exp'],limits['+1sig'],limits['+2sig'])
        limits_txt.write("%s %s %s %s %s %s %s %s\n"%(N,ST,limits["Obs"],limits["-2sig"],limits['-1sig'],limits['exp'],limits['+1sig'],limits['+2sig']))
