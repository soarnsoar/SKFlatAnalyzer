#/data6/Users/jhchoi/python_tool/ExportShellCondorSetup_snu.py
#   parser.add_option("-c","--command",   dest="command", help="command to run")
#   parser.add_option("-d","--workdir",   dest="workdir", help="workarea")
#   parser.add_option("-n","--jobname",   dest="jobname", help="jobname")
#   parser.add_option("-m","--ncpu",   dest="ncpu", help="number of multicores",default=1)
#   parser.add_option("-s","--submit",   dest="submit",action="store_true", help="submit",default=False)
#   parser.add_option("-r","--memory",   dest="memory", help="memory")
ExportShellCondorSetup_snu.py -c "cd $PWD&&hadd -j 10 -f combine.root *.root" -d "WORKDIR_HADD" -n "hadd" -m 10 -r "10000" -s
