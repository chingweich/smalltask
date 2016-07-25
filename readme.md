
'''
small0706Base:  draw limit 2D, 
								 input: $1=input directory, $2=outputname, $3=1 if one needs to fix resolved scale
small0706Compare: draw limit compare 2D, 
										  input: $1=input directory[](array), $2=outputname, $3=1 if one needs to fix resolved scale, 
														$4= 0 for expected limt Xsec=1
																1 for observed limt Xsec=1
																2 for expected limt Xsec=input root file (defined in function)
																3 for observed limt Xsec=input root file (defined in function)
small0706Compare:  draw limit 1D, efficiency 1D,
											input:TH2D
readTxt: draw efficiency 2D
TH2DComparer: compare efficiency maximum 2D
excludeLimit: get excludeLimit tgragh
drawExcludeLimit: draw excludeLimit
drawExcludeLimitWith2D : not used
'''