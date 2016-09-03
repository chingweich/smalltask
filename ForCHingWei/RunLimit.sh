which=$1 ## name of the directory where .root files are saved
whichmode=$2 ## mode with which you want to run the code: cms: atlas: comb


root -l -b -q plot_Asymptotic_altascombine.C\(\"$which\",\"$whichmode\"\)