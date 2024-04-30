#condor_prio -p <priority> <job-id>
import os
id1=2256143
id2=2256255

for id in range(id1,id2+1):
    print id
    command="condor_prio -p -1 "+str(id)
    print command
    os.system(command)
    #break
